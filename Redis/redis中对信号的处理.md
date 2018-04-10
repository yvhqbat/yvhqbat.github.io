

```

void initServer(void) {
    // 忽视信号: SIGHUP, SIGPIPE 
    signal(SIGHUP, SIG_IGN);
    signal(SIGPIPE, SIG_IGN);
    
	// 设置SIGTERM, SIGINT 信号处理函数
    setupSignalHandlers();
}

// 设置信号处理函数，当SIGTERN, SIGINT时，退出程序
void setupSignalHandlers(void) {
    struct sigaction act;

    /* When the SA_SIGINFO flag is set in sa_flags then sa_sigaction is used.
     * Otherwise, sa_handler is used. */
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = sigShutdownHandler;
    sigaction(SIGTERM, &act, NULL);
    sigaction(SIGINT, &act, NULL);

#ifdef HAVE_BACKTRACE
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_NODEFER | SA_RESETHAND | SA_SIGINFO;
    act.sa_sigaction = sigsegvHandler;
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGBUS, &act, NULL);
    sigaction(SIGFPE, &act, NULL);
    sigaction(SIGILL, &act, NULL);
#endif
    return;
}

// 信号处理函数，ctrl+c 会产生 SIGINT信号，连续两次，会退出程序。
static void sigShutdownHandler(int sig) {
    char *msg;

    switch (sig) {
    case SIGINT:
        msg = "Received SIGINT scheduling shutdown...";
        break;
    case SIGTERM:
        msg = "Received SIGTERM scheduling shutdown...";
        break;
    default:
        msg = "Received shutdown signal, scheduling shutdown...";
    };

    /* SIGINT is often delivered via Ctrl+C in an interactive session.
     * If we receive the signal the second time, we interpret this as
     * the user really wanting to quit ASAP without waiting to persist
     * on disk. */
    if (server.shutdown_asap && sig == SIGINT) {
        redisLogFromHandler(REDIS_WARNING, "You insist... exiting now.");
        rdbRemoveTempFile(getpid());
        exit(1); /* Exit with an error since this was not a clean shutdown. */
    } else if (server.loading) {
        exit(0);
    }

    redisLogFromHandler(REDIS_WARNING, msg);
    server.shutdown_asap = 1;
}

```
