/** @file    TcpClient.h
 *  @note
 *  @brief   CTcpClient类的声明
 *
 *  @author  yvhqbat
 *  @date    2017/11/01
 *
 *  @note    实现功能
 *  @warning ...
 */

#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/** @class   CTcpClient
 *  @brief   客户端socket的创建与连接
 */
class CTcpClient
{
public:
    /* 构造函数 */
    CTcpClient(const std::string &strIP, int nPort);

    /* 启动客户端 */
    int StartClient();

    /* 关闭客户端的连接 */
    void CloseClient();

    /* 判断客户端是否关闭 */
    bool IsClose();

private:
    /* 连接到服务器 */
    int Connect();

    /* 客户端运行过程 */
    int Run();

private:
    std::string      m_strIP;         ///< 服务器的IP地址
    int              m_nPort;         ///< 服务器的端口号
    int              m_nSocketFd;     ///< 连接的socket
};
#endif  //TCP_CLIENT_H
