# Redis源码阅读-文件事件处理器

## 连接应答处理器
> 连接应答处理器：networking.c/acceptTcpHandler函数是redis的连接应答处理器，用于对连接服务器监听套接字的客户端进行应答，具体实现是sys/socket.h/accept函数的包装。

accept fd --> createClient(fd) --> 加入到server.clients队列中,
```
/* Anti-warning macro... */
/* 宏: 显式指明参数V没有被使用 */
#define REDIS_NOTUSED(V) ((void) V)
```

```
/*
 * 创建一个 TCP 连接处理器
 */
void acceptTcpHandler(int fd) {
    int cport, cfd, max = MAX_ACCEPTS_PER_CALL;
    char cip[REDIS_IP_STR_LEN];

    while(max--) {
        // accept 客户端连接, 并保存客户端的 fd, IP, PORT,
        cfd = anetTcpAccept(server.neterr, fd, cip, sizeof(cip), &cport);
        if (cfd == ANET_ERR) {
            redisLog(REDIS_WARNING, "Accepting client connection: %s", server.neterr);
            return;
        }
        redisLog(REDIS_VERBOSE,"Accepted %s:%d", cip, cport);
        // 为客户端创建客户端状态（redisClient）
        acceptCommonHandler(cfd,0);
    }
}
```

```
/*
 * TCP 连接 accept 处理器
 */
#define MAX_ACCEPTS_PER_CALL 1000
static void acceptCommonHandler(int fd, int flags) {

    // 创建客户端,保存到服务端 listAddNodeTail(server.clients,c)
    redisClient *c;
    if ((c = createClient(fd)) == NULL) {
        redisLog(REDIS_WARNING,
            "Error registering fd event for the new client: %s (fd=%d)",
            strerror(errno),fd);
        close(fd);
        return;
    }

    /* If maxclient directive is set and this is one client more... close the
     * connection. Note that we create the client instead to check before
     * for this condition, since now the socket is already set in non-blocking
     * mode and we can send an error for free using the Kernel I/O */
    // 如果新添加的客户端令服务器的最大客户端数量达到了
    // 那么向新客户端写入错误信息，并关闭新客户端
    // 先创建客户端，再进行数量检查是为了方便地进行错误信息写入
    if (listLength(server.clients) > server.maxclients) {
        char *err = "-ERR max number of clients reached\r\n";

        /* That's a best effort error message, don't check write errors */
        if (write(c->fd,err,strlen(err)) == -1) {
            /* Nothing to do, Just to avoid the warning... */
        }
        // 更新拒绝连接数
        server.stat_rejected_conn++;
        freeClient(c);
        return;
    }

    // 更新连接次数
    server.stat_numconnections++;

    // 设置 FLAG
    c->flags |= flags;
}
```

```
/*
 * 创建一个新客户端, 并添加到服务器链表中. listAddNodeTail(server.clients,c)
 */
redisClient *createClient(int fd) {

    // 分配空间
    redisClient *c = zmalloc(sizeof(redisClient));

    /* passing -1 as fd it is possible to create a non connected client.
     * This is useful since all the Redis commands needs to be executed
     * in the context of a client. When commands are executed in other
     * contexts (for instance a Lua script) we need a non connected client. */
    // 当 fd 不为 -1 时，创建带网络连接的客户端
    // 如果 fd 为 -1 ，那么创建无网络连接的伪客户端
    // 因为 Redis 的命令必须在客户端的上下文中使用，所以在执行 Lua 环境中的命令时
    // 需要用到这种伪终端
    if (fd != -1) {
        // 非阻塞
        anetNonBlock(NULL,fd);
        // 禁用 Nagle 算法
        anetEnableTcpNoDelay(NULL,fd);
        // 设置 keep alive
        if (server.tcpkeepalive)
            anetKeepAlive(NULL,fd,server.tcpkeepalive);
        // 绑定读事件到事件 loop （开始接收命令请求）
        if (aeCreateFileEvent(server.el,fd,AE_READABLE,
            readQueryFromClient, c) == AE_ERR)
        {
            close(fd);
            zfree(c);
            return NULL;
        }
    }

    // 初始化各个属性

    // 默认数据库
    selectDb(c,0);
    // 套接字
    c->fd = fd;
    // 名字
    c->name = NULL;
    // 回复缓冲区的偏移量
    c->bufpos = 0;
    // 查询缓冲区
    c->querybuf = sdsempty();
    // 查询缓冲区峰值
    c->querybuf_peak = 0;
    // 命令请求的类型
    c->reqtype = 0;
    // 命令参数数量
    c->argc = 0;
    // 命令参数
    c->argv = NULL;
    // 当前执行的命令和最近一次执行的命令
    c->cmd = c->lastcmd = NULL;
    // 查询缓冲区中未读入的命令内容数量
    c->multibulklen = 0;
    // 读入的参数的长度
    c->bulklen = -1;
    // 已发送字节数
    c->sentlen = 0;
    // 状态 FLAG
    c->flags = 0;
    // 创建时间和最后一次互动时间
    c->ctime = c->lastinteraction = server.unixtime;
    // 认证状态
    c->authenticated = 0;
    // 复制状态
    c->replstate = REDIS_REPL_NONE;
    // 复制偏移量
    c->reploff = 0;
    // 通过 ACK 命令接收到的偏移量
    c->repl_ack_off = 0;
    // 通过 AKC 命令接收到偏移量的时间
    c->repl_ack_time = 0;
    // 客户端为从服务器时使用，记录了从服务器所使用的端口号
    c->slave_listening_port = 0;
    // 回复链表
    c->reply = listCreate();
    // 回复链表的字节量
    c->reply_bytes = 0;
    // 回复缓冲区大小达到软限制的时间
    c->obuf_soft_limit_reached_time = 0;
    // 回复链表的释放和复制函数
    listSetFreeMethod(c->reply,decrRefCountVoid);
    listSetDupMethod(c->reply,dupClientReplyValue);
    // 阻塞类型
    c->btype = REDIS_BLOCKED_NONE;
    // 阻塞超时
    c->bpop.timeout = 0;
    // 造成客户端阻塞的列表键
    c->bpop.keys = dictCreate(&setDictType,NULL);
    // 在解除阻塞时将元素推入到 target 指定的键中
    // BRPOPLPUSH 命令时使用
    c->bpop.target = NULL;
    c->bpop.numreplicas = 0;
    c->bpop.reploffset = 0;
    c->woff = 0;
    // 进行事务时监视的键
    c->watched_keys = listCreate();
    // 订阅的频道和模式
    c->pubsub_channels = dictCreate(&setDictType,NULL);
    c->pubsub_patterns = listCreate();
    c->peerid = NULL;
    listSetFreeMethod(c->pubsub_patterns,decrRefCountVoid);
    listSetMatchMethod(c->pubsub_patterns,listMatchObjects);
    // 如果不是伪客户端，那么添加到服务器的客户端链表中
    if (fd != -1) listAddNodeTail(server.clients,c);
    // 初始化客户端的事务状态
    initClientMultiState(c);

    // 返回客户端
    return c;
}
```


## 命令请求处理器
> 命令请求处理器：networking.c/readQueryFromClient函数是redis的命令请求处理器，负责从套接字中读如客户端发送的命令请求内容，具体实现是unistd.h/read函数的包装。


读取客户端的查询缓冲区内容 --> 读入内容到查询缓存 --> `while`从查询缓存重读取内容，创建参数，(从缓冲区中删除已读取的内容,剩余的内容是未读取的,`sdsrange(c->querybuf,querylen+2,-1);`,并执行命令(对于普通命令, 是将命令加入到事务队列(c->mstate.commands)中).


```
/*
 * 读取客户端的查询缓冲区内容
 */
void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask)
```


```
// 读入内容到查询缓存
nread = read(fd, c->querybuf+qblen, readlen);
```
```
// 从查询缓存重读取内容，创建参数，并执行命令
// 函数会执行到缓存中的所有内容都被处理完为止
processInputBuffer(c);
```

```
// 执行命令，并重置客户端
if (processCommand(c) == REDIS_OK)
    resetClient(c);
```


#### 完整过程如下:

```
/*
 * 读取客户端的查询缓冲区内容
 */
void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
    redisClient *c = (redisClient*) privdata;
    int nread, readlen;
    size_t qblen;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(mask);

    // 设置服务器的当前客户端
    server.current_client = c;

    // 读入长度（默认为 16 MB）
    readlen = REDIS_IOBUF_LEN;

    /* If this is a multi bulk request, and we are processing a bulk reply
     * that is large enough, try to maximize the probability that the query
     * buffer contains exactly the SDS string representing the object, even
     * at the risk of requiring more read(2) calls. This way the function
     * processMultiBulkBuffer() can avoid copying buffers to create the
     * Redis Object representing the argument. */
    if (c->reqtype == REDIS_REQ_MULTIBULK && c->multibulklen && c->bulklen != -1
        && c->bulklen >= REDIS_MBULK_BIG_ARG)
    {
        int remaining = (unsigned)(c->bulklen+2)-sdslen(c->querybuf);

        if (remaining < readlen) readlen = remaining;
    }

    // 获取查询缓冲区当前内容的长度
    // 如果读取出现 short read ，那么可能会有内容滞留在读取缓冲区里面
    // 这些滞留内容也许不能完整构成一个符合协议的命令，
    qblen = sdslen(c->querybuf);
    // 如果有需要，更新缓冲区内容长度的峰值（peak）
    if (c->querybuf_peak < qblen) c->querybuf_peak = qblen;
    // 为查询缓冲区分配空间
    c->querybuf = sdsMakeRoomFor(c->querybuf, readlen);
    // 读入内容到查询缓存
    nread = read(fd, c->querybuf+qblen, readlen);

    // 读入出错
    if (nread == -1) {
        if (errno == EAGAIN) {
            nread = 0;
        } else {
            redisLog(REDIS_VERBOSE, "Reading from client: %s",strerror(errno));
            freeClient(c);
            return;
        }
    // 遇到 EOF
    } else if (nread == 0) {
        redisLog(REDIS_VERBOSE, "Client closed connection");
        freeClient(c);
        return;
    }

    if (nread) {
        // 根据内容，更新查询缓冲区（SDS） free 和 len 属性
        // 并将 '\0' 正确地放到内容的最后
        sdsIncrLen(c->querybuf,nread);
        // 记录服务器和客户端最后一次互动的时间
        c->lastinteraction = server.unixtime;
        // 如果客户端是 master 的话，更新它的复制偏移量
        if (c->flags & REDIS_MASTER) c->reploff += nread;
    } else {
        // 在 nread == -1 且 errno == EAGAIN 时运行
        server.current_client = NULL;
        return;
    }

    // 查询缓冲区长度超出服务器最大缓冲区长度
    // 清空缓冲区并释放客户端
    if (sdslen(c->querybuf) > server.client_max_querybuf_len) {
        sds ci = catClientInfoString(sdsempty(),c), bytes = sdsempty();

        bytes = sdscatrepr(bytes,c->querybuf,64);
        redisLog(REDIS_WARNING,"Closing client that reached max query buffer length: %s (qbuf initial bytes: %s)", ci, bytes);
        sdsfree(ci);
        sdsfree(bytes);
        freeClient(c);
        return;
    }

    // 从查询缓存重读取内容，创建参数，并执行命令
    // 函数会执行到缓存中的所有内容都被处理完为止
    processInputBuffer(c);

    server.current_client = NULL;
}
```


```
/*
 * 处理内联命令，并创建参数对象
 *
 * 内联命令的各个参数以空格分开，并以 \r\n 结尾
 * 例子：
 *
 * <arg0> <arg1> <arg...> <argN>\r\n
 *
 * 这些内容会被用于创建参数对象，
 * 比如
 *
 * argv[0] = arg0
 * argv[1] = arg1
 * argv[2] = arg2
 */
int processInlineBuffer(redisClient *c) {
    char *newline;
    int argc, j;
    sds *argv, aux;
    size_t querylen;

    /* Search for end of line */
    newline = strchr(c->querybuf,'\n');

    /* Nothing to do without a \r\n */
    // 收到的查询内容不符合协议格式，出错
    if (newline == NULL) {
        if (sdslen(c->querybuf) > REDIS_INLINE_MAX_SIZE) {
            addReplyError(c,"Protocol error: too big inline request");
            setProtocolError(c,0);
        }
        return REDIS_ERR;
    }

    /* Handle the \r\n case. */
    if (newline && newline != c->querybuf && *(newline-1) == '\r')
        newline--;

    /* Split the input buffer up to the \r\n */
    // 根据空格，分割命令的参数
    // 比如说 SET msg hello \r\n 将分割为
    // argv[0] = SET
    // argv[1] = msg
    // argv[2] = hello
    // argc = 3
    querylen = newline-(c->querybuf);
    aux = sdsnewlen(c->querybuf,querylen);
    argv = sdssplitargs(aux,&argc);
    sdsfree(aux);
    if (argv == NULL) {
        addReplyError(c,"Protocol error: unbalanced quotes in request");
        setProtocolError(c,0);
        return REDIS_ERR;
    }

    /* Newline from slaves can be used to refresh the last ACK time.
     * This is useful for a slave to ping back while loading a big
     * RDB file. */
    if (querylen == 0 && c->flags & REDIS_SLAVE)
        c->repl_ack_time = server.unixtime;

    /* Leave data after the first line of the query in the buffer */

    // 从缓冲区中删除已 argv 已读取的内容
    // 剩余的内容是未读取的
    sdsrange(c->querybuf,querylen+2,-1);

    /* Setup argv array on client structure */
    // 为客户端的参数分配空间
    if (c->argv) zfree(c->argv);
    c->argv = zmalloc(sizeof(robj*)*argc);

    /* Create redis objects for all arguments. */
    // 为每个参数创建一个字符串对象
    for (c->argc = 0, j = 0; j < argc; j++) {
        if (sdslen(argv[j])) {
            // argv[j] 已经是 SDS 了
            // 所以创建的字符串对象直接指向该 SDS
            c->argv[c->argc] = createObject(REDIS_STRING,argv[j]);
            c->argc++;
        } else {
            sdsfree(argv[j]);
        }
    }

    zfree(argv);

    return REDIS_OK;
}
```

```
// 处理客户端输入的命令内容
void processInputBuffer(redisClient *c) {

    /* Keep processing while there is something in the input buffer */
    // 尽可能地处理查询缓冲区中的内容
    // 如果读取出现 short read ，那么可能会有内容滞留在读取缓冲区里面
    // 这些滞留内容也许不能完整构成一个符合协议的命令，
    // 需要等待下次读事件的就绪
    while(sdslen(c->querybuf)) {

        /* Return if clients are paused. */
        // 如果客户端正处于暂停状态，那么直接返回
        if (!(c->flags & REDIS_SLAVE) && clientsArePaused()) return;

        /* Immediately abort if the client is in the middle of something. */
        // REDIS_BLOCKED 状态表示客户端正在被阻塞
        if (c->flags & REDIS_BLOCKED) return;

        /* REDIS_CLOSE_AFTER_REPLY closes the connection once the reply is
         * written to the client. Make sure to not let the reply grow after
         * this flag has been set (i.e. don't process more commands). */
        // 客户端已经设置了关闭 FLAG ，没有必要处理命令了
        if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;

        /* Determine request type when unknown. */
        // 判断请求的类型
        // 两种类型的区别可以在 Redis 的通讯协议上查到：
        // http://redis.readthedocs.org/en/latest/topic/protocol.html
        // 简单来说，多条查询是一般客户端发送来的，
        // 而内联查询则是 TELNET 发送来的
        if (!c->reqtype) {
            if (c->querybuf[0] == '*') {
                // 多条查询
                c->reqtype = REDIS_REQ_MULTIBULK;
            } else {
                // 内联查询
                c->reqtype = REDIS_REQ_INLINE;
            }
        }

        // 将缓冲区中的内容转换成命令，以及命令参数
        if (c->reqtype == REDIS_REQ_INLINE) {
            if (processInlineBuffer(c) != REDIS_OK) break;
        } else if (c->reqtype == REDIS_REQ_MULTIBULK) {
            if (processMultibulkBuffer(c) != REDIS_OK) break;
        } else {
            redisPanic("Unknown request type");
        }

        /* Multibulk processing could see a <= 0 length. */
        if (c->argc == 0) {
            resetClient(c);
        } else {
            /* Only reset the client when the command was executed. */
            // 执行命令，并重置客户端
            if (processCommand(c) == REDIS_OK)
                resetClient(c);
        }
    }
}
```


其他所有命令都会被入队到事务队列中
```
/* in processCommand(c) */
/* Exec the command */
    if (c->flags & REDIS_MULTI &&
        c->cmd->proc != execCommand && c->cmd->proc != discardCommand &&
        c->cmd->proc != multiCommand && c->cmd->proc != watchCommand)
    {
        // 在事务上下文中
        // 除 EXEC 、 DISCARD 、 MULTI 和 WATCH 命令之外
        // 其他所有命令都会被入队到事务队列中
        queueMultiCommand(c);
        addReply(c,shared.queued);
    } else {
        // 执行命令
        call(c,REDIS_CALL_FULL);

        c->woff = server.master_repl_offset;
        // 处理那些解除了阻塞的键
        if (listLength(server.ready_keys))
            handleClientsBlockedOnLists();
    }
```

```
queueMultiCommand(c);
```

将一个新命令添加到事务队列(c->mstate.commands)中,设置事务的命令、命令参数数量，以及命令的参数.
```
/* Add a new command into the MULTI commands queue
 *
 * 将一个新命令添加到事务队列中
 */
void queueMultiCommand(redisClient *c) {
    multiCmd *mc;
    int j;

    // 为新数组元素分配空间
    c->mstate.commands = zrealloc(c->mstate.commands,
            sizeof(multiCmd)*(c->mstate.count+1));

    // 指向新元素
    mc = c->mstate.commands+c->mstate.count;

    // 设置事务的命令、命令参数数量，以及命令的参数
    mc->cmd = c->cmd;
    mc->argc = c->argc;
    mc->argv = zmalloc(sizeof(robj*)*c->argc);
    memcpy(mc->argv,c->argv,sizeof(robj*)*c->argc);
    for (j = 0; j < c->argc; j++)
        incrRefCount(mc->argv[j]);

    // 事务命令数量计数器增一
    c->mstate.count++;
}
```

## 命令回复处理器
> 命令回复处理器：networking.c/sendReplyToClient函数是redis的命令回复处理器，负责将服务器执行命令后得到的命令回复通过套接字返回给客户端，具体实现 是unistd.h/write函数的包装。
