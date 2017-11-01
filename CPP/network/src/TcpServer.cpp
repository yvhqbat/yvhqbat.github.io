/** @file    TcpServer.cpp
 *  @note
 *  @brief   CTcpServer类的实现
 *
 *  @author  yvhqbat
 *  @date    2017/11/01
 *
 *  @note    实现功能
 *  @warning ...
 */

#include <chrono>
#include <memory>
#include <cstdio>
#include <errno.h>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>

#include "TcpServer.h"
using namespace std;


/** @fn      CTcpServer::CTcpServer(int nPort)
 *  @brief   构造函数
 *  @param   nPort   [in]   服务器端口号
 */
CTcpServer::CTcpServer(int nPort)
    : m_nPort(nPort)
    , m_nListenFd(0)
    , m_listClients()
    , m_nShutdownFlag(Shutdown::ON)
    , m_atomicIntCount(0)
{
}

/** @fn      CTcpServer::~CTcpServer()
 *  @brief   析构函数
 */
CTcpServer::~CTcpServer()
{
    /* 关闭socket */
    CloseServer();
}

/** @fn      int CTcpServer::StartServer()
 *  @brief   启动服务器
 *  @return  返回错误码
 */
int CTcpServer::StartServer()
{
    int nRet = 0;  ///< 错误码
    /* 绑定端口 */
    nRet = Bind();
    if (0 != nRet)
    {
        cout<<"bind to server port falied!"<<endl;
        return nRet;
    }

    /* 开始监听 */
    nRet = Listen();
    if (0 != nRet)
    {
        cout<<"listen to server port falied!"<<endl;
        return nRet;
    }

    /* 开始处理连接循环 */
    Loop();
    return 0;
}

/** @fn      int CTcpServer::CloseServer()
 *  @brief   关闭服务器
 *  @return  返回错误码
 */
int CTcpServer::CloseServer()
{
    /* 设置状态 */
    m_nShutdownFlag = Shutdown::OFF;

    /* 关闭监听端口 */
    if(m_nListenFd != 0)
    {
        close(m_nListenFd);
        m_nListenFd = 0;
    }
    return 0;
}

/** @fn      int CTcpServer::Bind()
 *  @brief   绑定一个端口
 *  @return  返回错误码
 */
int CTcpServer::Bind()
{
    /* 创建socket */
    if((m_nListenFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        return -1;
    }

    /* 设置SO_REUSEADDR 通用套接字选项 */
    int nOptval = 1;
    if (0 != setsockopt(m_nListenFd, SOL_SOCKET, SO_REUSEADDR, (const char*)&nOptval, sizeof(int)))
    {
        std::cout<<"setsockopt SO_REUSEADDR failed!"<<std::endl;
    }


    /* 初始化服务器地址 */
    struct sockaddr_in m_stSockaddrServer;
    memset(&m_stSockaddrServer, 0, sizeof(m_stSockaddrServer));
    m_stSockaddrServer.sin_family      = AF_INET;
    m_stSockaddrServer.sin_addr.s_addr = htonl(INADDR_ANY);
    m_stSockaddrServer.sin_port        = htons(m_nPort);

    /* 绑定端口 */
    if(bind(m_nListenFd, (struct sockaddr*)&m_stSockaddrServer, sizeof(m_stSockaddrServer)) == -1)
    {
        return -1;
    }
    return 0;
}

/** @fn      int ITcpServer::Listen()
 *  @brief   监听一个socket.
 *  @return  返回错误码
 */
int CTcpServer::Listen()
{
    if(listen(m_nListenFd, 10) == -1)
    {
        return -1;
    }
    return 0;
}

/** @fn      int CTcpServer::Loop()
 *  @brief   不断接收客户端的连接并在工作线程中对其进行处理
 *  @return  返回错误码
 */
void CTcpServer::Loop()
{
    //TODO: select
    fd_set rset, exset, allset;
    FD_ZERO(&allset);
    FD_SET(m_nListenFd, &allset);
    FD_SET(STDIN_FILENO, &allset);  //< 标准输入
    int maxfd = m_nListenFd;
    int nReady = 0;

    /* 初始化客户端地址结构体 */
    struct sockaddr_in stSockaddrClient;
    memset(&stSockaddrClient, 0, sizeof(stSockaddrClient));
    socklen_t nSocklen  = sizeof(stSockaddrClient);  //如果不初始化,在第一次获取客户端IP时IP为0.
    char      szIP[100] = {0};
    int       nSocket   = 0;

    struct timeval stTimer;
    stTimer.tv_sec=2;
    stTimer.tv_usec=0;
    int nCount = 0;

    /* 接收客户端连接 */
    while(m_nShutdownFlag == Shutdown::ON)
    {
        //std::cout<<"round "<<nCount++<<std::endl;
        rset = allset;
        exset = allset;
        nReady = select(maxfd+1, &rset, NULL, &exset, &stTimer);

        if(FD_ISSET(m_nListenFd, &rset))
        {
            if((nSocket = accept(m_nListenFd, (struct sockaddr*)&stSockaddrClient, &nSocklen))==-1)
            {
                cout<<"accept error"<<endl;
                continue;
            }
            std::string strIP = inet_ntop(AF_INET, &stSockaddrClient.sin_addr, szIP, sizeof(szIP));
            cout<<"connect from client: "<<strIP<<endl;

            //先处理单个客户端的
            CClient *pcClient = new CClient(nSocket, strIP);
            /* 保存到服务器中 */
            m_listClients.push_back(pcClient);

            FD_SET(nSocket, &allset);
            if(nSocket>maxfd)
            {
                maxfd=nSocket;
            }
            if(--nReady<0)
            {
                continue;
            }
            /* 为客户端创建状态,并处理连接 */
            //AcceptRequest(nSocket, strIP);
        }

        for(auto ite = m_listClients.begin();ite!=m_listClients.end();++ite)
        {
            if(FD_ISSET((*ite)->m_nConnectFd, &rset))
            {
                //(*ite)->ProcessRequest();
                char pBuffer[1024];
                int n = recv((*ite)->m_nConnectFd, pBuffer, 1024, 0);
                if(n <=0)
                {
                    cout<<"client closed."<<endl;
                    close((*ite)->m_nConnectFd);
                    FD_CLR((*ite)->m_nConnectFd, &allset);
                    (*ite)->m_nConnectFd = 0;
                }else
                {
                    pBuffer[n]='\0';
                    std::cout<<pBuffer<<std::endl;
                    //send((*ite)->m_nConnectFd, pBuffer, n+1 , 0);
                }
            }
            if(--nReady<=0)
            {
                break;
            }
       }

      // STDIN_FILENO
      if(FD_ISSET(STDIN_FILENO, &rset))
      {
          char pBuffer[1024];
          int n = read(STDIN_FILENO, pBuffer, 1024);
          pBuffer[5]='\0';
          std::string str = pBuffer;
          std::cout<<"read message: "<<pBuffer<<std::endl;
          if(str ==  "close")
          {
             std::cout<<"read close"<<std::endl;
             m_nShutdownFlag = Shutdown::OFF;

          }else
          {
             std::cout<<"not equal"<<std::endl;
          }
      }

   }
   std::cout<<"closing the server. bye bye!"<<std::endl;
}

/** @fn      int CTcpServer::AcceptRequest(int nSocket, const std::string &strIP)
 *  @brief   在服务器接收到客户端连接后, 处理连接
 *  @param   nSocket   [in]   与客户端的连接socket
 *  @param   s=trIP     [in]   客户端的IP
 *  @return  返回错误码
 */
void CTcpServer::AcceptRequest(int nSocket, const std::string &strIP)
{
    //先处理单个客户端的
    CClient *pcClient = new CClient(nSocket, strIP);
    /* 保存到服务器中 */
    m_listClients.push_back(pcClient);
    //pcClient->ProcessRequest();
}
