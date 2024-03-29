#include "../include/networking/networking.hpp"
#include "../include/networking/node.hpp"
#include "../include/debug/debug.hpp"
#include <string>
#include <minwindef.h>
#include <winsock2.h>
#include <synchapi.h>

void initNetworking()
{
    WSADATA wsaData;

    char r = WSAStartup(MAKEWORD(2,2), &wsaData);

    if((int) r != 0)
    {
        consolelog<std::string>("Failed to initialize wsa", CONSOLELOG::LOGTYPE::ERRORLOG);
    }

    if(LOBYTE(wsaData.wHighVersion) != 2 && HIBYTE(wsaData.wVersion) != 2)
    {
        consolelog<std::string>("System does not have a compatiable winsock library", CONSOLELOG::LOGTYPE::ERRORLOG);
    }
    else
    {
        consolelog<std::string>("Found compatiable winsock library", CONSOLELOG::LOGTYPE::INFOLOG);
    }

    consolelog<std::string>("Initialization of wsa successfull", CONSOLELOG::LOGTYPE::INFOLOG);
}

struct node createNode(std::string ip, std::string port, NETTYPE::IPTYPE iptype, NETTYPE::SOCKTYPE socktype, uint32_t interval, uint32_t hostresolvetries)
{

    uint16_t portNumber = std::stoi(port);
    if (portNumber <= 0 || portNumber > 65535) {
		consolelog<std::string>("Invalid port number user", CONSOLELOG::ERRORLOG);
		exit(0);
	}
    struct node result{};

    uint16_t family = AF_INET;
    uint16_t sockType = SOCK_STREAM;
    uint16_t protocol = IPPROTO_TCP;

    switch(iptype)
    {
    case NETTYPE::IPTYPE::IPV4:
    {
        family = AF_INET;
        break;
    }
    case NETTYPE::IPTYPE::IPV6:
    {
        family = AF_INET6;
        break;
    }
    default:
    {
        consolelog("Invalid ip type given it's either IPV4 OR IPV6", CONSOLELOG::ERRORLOG);
    }
    }

    switch (socktype)
    {
    case NETTYPE::SOCKTYPE::TCP:
        sockType = SOCK_STREAM;
        protocol = IPPROTO_TCP;
        break;
    case NETTYPE::SOCKTYPE::UDP:
        sockType = SOCK_DGRAM;
        protocol = IPPROTO_UDP;
        break;
    default:
        break;
    }

    addrinfo* serverAddr;
	addrinfo hints;
    RtlZeroMemory(&hints, sizeof(hints));

	hints.ai_family = family;
	hints.ai_socktype = sockType;
	hints.ai_protocol = protocol;
	hints.ai_addrlen = 0;
	hints.ai_canonname = 0;
	hints.ai_addr = 0;
	hints.ai_next = 0;

    while(hostresolvetries)
    {
        int result = getaddrinfo(ip.c_str(), port.c_str(), &hints, &serverAddr);

        if(result != 11001)
        {
            hostresolvetries = 0;
            break;
        }

        consolelog("Host not found trying again tries remaning : " + std::string(hostresolvetries, 1), CONSOLELOG::INFOLOG);

        hostresolvetries--;
        Sleep(interval);
    }


    fillUpNode(&result, serverAddr, portNumber, ip);
}

void connectToNode(struct node *node)
{
    if(connect(node->socket, (sockaddr *)node->socketAddr, node->size))
    {
        consolelog("Failed to connect to node", CONSOLELOG::ERRORLOG);
        consolelog(WSAGetLastError(), CONSOLELOG::ERRORLOG);
    }
    else
    {
        consolelog("Connection successfull to node", CONSOLELOG::INFOLOG);
    }
}

void sendToNode(struct node *node, const uint8_t *buffer, const uint32_t size)
{
    send(node->socket, (const char *)buffer, size, 0);
}

void recvFromNode(struct node *node, uint8_t *buffer, const uint32_t size)
{
    recv(node->socket, (char *)buffer, size, 0);
}