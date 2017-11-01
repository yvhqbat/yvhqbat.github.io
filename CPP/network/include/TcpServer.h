/** @file    TcpServer.h
 *  @note
 *  @brief   CTcpServer类的声明
 *
 *  @author  yvhqbat
 *  @date    2017/11/01
 *
 *  @note    实现功能
 *  @warning ...
 */
#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <list>
#include <thread>
#include <atomic>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <iostream>
using namespace std;

class CClient
{
public:
    CClient(int nConnectFd, std::string strIP)
        : m_nConnectFd(nConnectFd)
        , m_strIP(strIP)
    {
    }

    void ProcessRequest()
    {
        char pBuffer[1024];
        int n = recv(m_nConnectFd, pBuffer, 1024, 0);
        if(n <=0)
        {
            cout<<"client closed."<<endl;
            close(m_nConnectFd);
            m_nConnectFd = 0;
        }else
        {
            pBuffer[n]=0;
            send(m_nConnectFd, pBuffer, n+1 , 0);
        }
    }

public:
    int          m_nConnectFd;
    std::string  m_strIP;
};


/** @class  CTcpServer
 *  @brief  服务器端socket的创建,监听和接收客户端的连接.
 */
class CTcpServer
{
private:
        /** @enum   EShutdown
         *  @brief  服务器运行标识
         */
        enum Shutdown : int
        {
            OFF = 0,  ///< 关闭
            ON  = 1   ///< 未关闭
        };

public:
    /* 构造函数 */
    CTcpServer(int nPort);

    /* 析构函数 */
    ~CTcpServer();

    /* 启动服务器 */
    int StartServer();

    /* 关闭服务器 */
    int CloseServer();

private:

    /* 绑定一个端口 */
    int Bind();

    /* 监听一个socket */
    int Listen();

    /* 不断接收客户端的连接并在工作线程中对其进行处理 */
    void Loop();

    /* 在服务器接收到客户端连接后, 处理连接 */
    void AcceptRequest(int nSocket, const std::string &strIP);

private:
    int                          m_nPort;                ///< TCP 监听端口
    int                          m_nListenFd;            ///< 服务器绑定和监听的套接字
    std::list<CClient*>          m_listClients;          ///< 保存所有客户端状态结构的容器
    int                          m_nShutdownFlag;        ///< 关闭服务器的标识, EShutdown::ON/OFF
    std::atomic<int>             m_atomicIntCount;       ///< 统计连接的客户端数量
};
#endif  //TCP_SERVER_H
