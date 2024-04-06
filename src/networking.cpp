#include "../include/networking/networking.hpp"
#include "../include/networking/node.hpp"
#include "../include/debug/debug.hpp"
#include "../include/danlib.hpp"
#include <string>
#include <minwindef.h>
#include <winsock2.h>
#include <synchapi.h>
#include <vector>

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

    const char *iptouse = ip.c_str();
    const char *porttouse = port.c_str();

    while(hostresolvetries)
    {
        int result = getaddrinfo(iptouse, porttouse, &hints, &serverAddr);
        result = WSAGetLastError();

        if(result == 11001){    // host not found try again
            consolelog("Host not found trying again", CONSOLELOG::INFOLOG);

            hostresolvetries--;
        }

        if(result == 0)
        {
            hostresolvetries = 0;
            break;
        }

        Sleep(interval * 1000);
    }

    if(serverAddr == NULL)
    {
        consolelog("DNS was resolved but no sockaddr was found", CONSOLELOG::ERRORLOG);
        exit(0);
    }

    result.port = portNumber;
    result.socket = socket(serverAddr->ai_family, serverAddr->ai_socktype, serverAddr->ai_protocol);
    setsockopt(result.socket, SOL_SOCKET, SO_REUSEADDR | SO_EXCLUSIVEADDRUSE, (const char *)1, sizeof(int));
    result.ip = ip;
    if(result.socket == INVALID_SOCKET)
    {
        consolelog("Invalid socket created", CONSOLELOG::ERRORLOG);
        exit(0);
    }

    fillUpNode(&result, serverAddr, portNumber, ip);

    return result;
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

struct __RD_ARGS
{
    char *buffer;
    uint32_t size;
    struct node *node;
    void (*callback)(char *buffer, uint32_t size);
};

static void __recv__data(struct __RD_ARGS *args)
{
    int result = 0;
    while(result != SOCKET_ERROR)
    {
        result = recv(args->node->socket, args->buffer, args->size, 0);

        if(result == 0)
        {
            break;
        }
        else
        {
            args->callback(args->buffer, args->size);
            memset(args->buffer, '\0', args->size);
        }
    }
}

HANDLE recvFromNode(struct node *node, void (*callback)(char *buffer, uint32_t size))
{
    char *buff = new char[DEFAULT_DATA_LEN];
    memset(buff, '\0', DEFAULT_DATA_LEN);

    struct __RD_ARGS *args = new __RD_ARGS;
    args->buffer = buff;
    args->node = node;
    args->size  = DEFAULT_DATA_LEN;
    args->callback = callback;

    DWORD threadid;
    HANDLE thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&__recv__data, args, 0, &threadid);

    return thread;
}

struct __L_A_A_ARGS
{
    struct node *node;
    std::vector<struct node *> *nodes; 
    int maxcon;
    void (*callback)(struct node *node);
};

static void __listen__and__accecpt(struct __L_A_A_ARGS *args)
{   
    consolelog("Created listening thread", CONSOLELOG::DEBUGLOG);

    if(args->node->socket == INVALID_SOCKET)
    {
        consolelog("node's socket is invalid", CONSOLELOG::ERRORLOG);
        exit(0);
    }
    
    int result  = listen(args->node->socket, 1);

    if(result == SOCKET_ERROR)
    {
        consolelog("Listen() return error code ", CONSOLELOG::ERRORLOG);
        consolelog(WSAGetLastError(), CONSOLELOG::ERRORLOG);
    }

    sockaddr_in *clietSockAdrr = new sockaddr_in;
    int Csize = sizeof(sockaddr_in);

    while(args->nodes->size() < args->maxcon)
    {
        SOCKET clientSocket = accept(args->node->socket, (sockaddr *)clietSockAdrr, &Csize);
        //consolelog("I'm working", CONSOLELOG::DEBUGLOG);
        if(clientSocket != INVALID_SOCKET)
        {
            struct node *clientNode =  new struct node;
            clientNode->socket = clientSocket;
            clientNode->socketAddr = clietSockAdrr;
            clientNode->size = Csize;
            int size = sizeof(clientNode->socketAddr);
            args->nodes->push_back(clientNode);
            args->callback(clientNode);
        }
    }
}

HANDLE listenOnNode(struct node *node, std::vector<struct node *> *nodes, int maxcon, void (*callback)(struct node *node))
{
    struct __L_A_A_ARGS *args = new __L_A_A_ARGS;
    args->maxcon = maxcon;
    args->node = node;
    args->nodes = nodes;
    args->callback = callback;

    int result = bind(node->socket, (sockaddr *)node->socketAddr, sizeof(*node->socketAddr));

	if(result == SOCKET_ERROR)
	{
		consolelog("bind() failed", CONSOLELOG::ERRORLOG);
		consolelog(WSAGetLastError(), CONSOLELOG::ERRORLOG);
		exit(0);
	}

    DWORD threadid = 0;
    HANDLE thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) __listen__and__accecpt, args, 0, &threadid);

    return thread;
}