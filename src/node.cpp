#include "../include/networking/node.hpp"
#include "../include/debug/debug.hpp"
#include <WS2tcpip.h>
#include <stdio.h>
#include <synchapi.h>
#include <string>

struct node createNodeV4(const char* ipv4, const char *port, unsigned short family, unsigned short sockType, unsigned short protocol)
{
	node out;
	RtlZeroMemory(&out, sizeof(out));

	uint16_t portNumber = std::stoi(port);
    if (portNumber <= 0 || portNumber > 65535) {
		consolelog<std::string>("Invalid port number user", CONSOLELOG::ERRORLOG);
		exit(0);
	}

	addrinfo* serverAddr;
	addrinfo hints;

	hints.ai_family = family;
	hints.ai_socktype = sockType;
	hints.ai_protocol = protocol;
	hints.ai_addrlen = 0;
	hints.ai_canonname = 0;
	hints.ai_addr = 0;
	hints.ai_next = 0;

	//const char *port_number = std::to_string(port).c_str();
	consolelog(ipv4, CONSOLELOG::DEBUGLOG);
	consolelog(port, CONSOLELOG::DEBUGLOG);
	
	bool hostresolved = false;

	while(!hostresolved)
	{
		int result = getaddrinfo(ipv4, port, &hints, &serverAddr);

		if(result != 11001)	// host not found, keep trying
		{
			hostresolved = true;
		}

		consolelog("Host not found trying again", CONSOLELOG::ERRORLOG);
		Sleep(5000);
	}

	// if ()
	// {
	// 	char msg[128];
	// 	sprintf_s(msg, "%s : %d", "Failed to resolve host name error code : ", WSAGetLastError());
	// 	consolelog<std::string>(msg, CONSOLELOG::LOGTYPE::ERRORLOG);
	// 	exit(0);
	// }
	
	char buffer[16];

	inet_ntop(AF_INET, serverAddr->ai_addr, buffer, sizeof(buffer));
	buffer[15] = '\0';

	consolelog<std::string>(buffer, CONSOLELOG::LOGTYPE::INFOLOG);

	strcpy(out.ipv4, buffer);
	out.socketAddr = (sockaddr_in *)serverAddr->ai_addr;
	out.size = serverAddr->ai_addrlen;
	//out.port = port;

	return out;
}