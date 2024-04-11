#include "include/danlib.hpp"
#include <vector>
#include <iostream>
#include <fstream>

void onDataRecv(char *buffer, uint32_t size)
{
    // std::vector<std::string> cmdData = splitIntoVector((const char *)buffer, ';', size);

    // for(const std::string &word : cmdData)
    // {
    //     consolelog(word, CONSOLELOG::DEBUGLOG);
    // }

    // if(cmdData[0] == "cncRemote")
    // {
    //     consolelog("Viper's Remote has been Connected", CONSOLELOG::DEBUGLOG);
    // }

    std::ofstream outFile("recv.png", std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to create output file." << std::endl; // Clean up allocated memory before exiting
    }
    outFile.write(buffer, size);
    outFile.close();

    // Remember to free the allocated memory
}

void onClientConnect(node *clientNode)
{
    consolelog("Client connected", CONSOLELOG::DEBUGLOG);

    recvFromNode(clientNode, &onDataRecv);
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