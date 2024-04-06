#include "include/danlib.hpp"
#include <vector>
#include <iostream>

void onClientConnect(node *clientNode)
{
    while(1)
    {
        const char buffer[1024] = "sup my niggas msgbox; niggas are you ok; alsdkjf\n";
        sendToNode(clientNode, (uint8_t *) buffer, sizeof(buffer));
        Sleep(3000);
    }
}

int main()
{
    initNetworking();

    node serverNode;

    serverNode = createNode("localhost", "4444", NETTYPE::IPTYPE::IPV4, NETTYPE::SOCKTYPE::TCP, 5, 5);

    std::vector<node *> clients;
    HANDLE thread = listenOnNode(&serverNode, &clients, 10, &onClientConnect);

    while(1){};

    return 0;
}