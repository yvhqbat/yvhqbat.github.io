#include "TcpClient.h"

int main()
{
    CTcpClient client("127.0.0.1",8001);
    client.StartClient();
    client.CloseClient();

    return 0;    
}
