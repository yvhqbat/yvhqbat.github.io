/** @file    TcpServer.cpp
 *  @note
 *  @brief   CTcpClient类的实现
 *
 *  @author  yvhqbat
 *  @date    2017/11/01
 *
 *  @note    实现功能
 *  @warning ...
 */
#include <cstdio>
#include <string>
#include <cstdlib>
#include <sstream>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "TcpClient.h"

using namespace std;

/** @fn     CTcpClient::CTcpClient(const std::string& strIP, int nPort)
 *  @brief  CTcpClient类的构造函数,初始化服务器地址
 *  @param  strIP   [in]   服务器的IP地址
 *  @param  nPort   [in]   服务器的端口号
 *  @return
 */
CTcpClient::CTcpClient(const std::string& strIP, int nPort)
    : m_strIP(strIP)
    , m_nPort(nPort)
	, m_nSocketFd(0)
{
}

/** @fn      int CTcpClient::StartClient()
 *  @brief   启动客户端
 *  @return  返回错误码
 */
int CTcpClient::StartClient()
{
    Connect();
    Run();
    return 0;
}

/** @fn      int CTcpClient::Connect()
 *  @brief   连接到服务器
 *  @return  返回错误码
 */
int CTcpClient::Connect()
{
    if((m_nSocketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cout << "creat socket error: "
                  << strerror(errno) << std::ends << errno << std::endl;
        return -1;
    }
    struct sockaddr_in stSockaddrServer;  ///< 服务器地址
    memset(&stSockaddrServer, 0, sizeof(stSockaddrServer));
    stSockaddrServer.sin_family = AF_INET;
    stSockaddrServer.sin_port   = htons(m_nPort);
    if(inet_pton(AF_INET, m_strIP.c_str(), &stSockaddrServer.sin_addr)<=0)
    {
        std::cout << "inet_pton error for " << m_strIP << std::endl;
        return -1;
    }
    if(connect(m_nSocketFd, (struct sockaddr*)&stSockaddrServer, sizeof(stSockaddrServer))<0)
    {
        std::cout << "connect error: "
             << strerror(errno) << std::ends << errno << std::endl;
        return -1;
    }
    std::cout << "connect successfully!" << std::endl;
    return 0;
}

/** @fn      int CTcpClient::Run()
 *  @brief   客户端运行过程
 *  @return  返回错误码
 */
int CTcpClient::Run()
{
    std::string line;
    while(cin>>line)
    {
        send(m_nSocketFd, line.c_str(), line.size()+1, 0);

        /*char pBuffer[1024];
        int n = recv(m_nSocketFd, pBuffer, 1024, 0);
        cout<<pBuffer<<endl;*/
    }

    return 0;
}

/** @fn     void CTcpClient::Close()
 *  @brief  关闭客户端的连接
 */
void CTcpClient::CloseClient()
{
    if(m_nSocketFd != 0)
    {
        close(m_nSocketFd);
        m_nSocketFd = 0;
    }
}

/** @fn      bool CTcpClient::IsClose()
 *  @brief   判断是否关闭
 *  @return  返回值
 */
bool CTcpClient::IsClose()
{
    return m_nSocketFd == 0;
}
