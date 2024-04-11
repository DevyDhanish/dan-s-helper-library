#include "include/danlib.hpp"
#include <vector>
#include <fstream>

void onDataRecv(char *buffer, uint32_t size)
{
	consolelog(buffer, CONSOLELOG::DEBUGLOG);
}

int main()
{
	initNetworking();

	node serverNode;

	serverNode = createNode("0.tcp.in.ngrok.io", "18592", NETTYPE::IPTYPE::IPV4, NETTYPE::SOCKTYPE::TCP, 5, 5);

	connectToNode(&serverNode);

    //WSACleanup();
    //closesocket(serverNode.socket);

	while(1) {}

	return 0;
}