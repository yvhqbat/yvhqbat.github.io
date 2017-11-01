#include "TcpServer.h"

int main()
{
    CTcpServer server(8001);
    server.StartServer();
    server.CloseServer();

    return 0;
}
