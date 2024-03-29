#include "../include/danlib.hpp"

int main()
{
	initNetworking();

	node serverNode;

	serverNode = createNode("0.tcp.in.ngrok.io", "15449", NETTYPE::IPTYPE::IPV4, NETTYPE::SOCKTYPE::TCP);

	connectToNode(&serverNode);

	char buffer[] = "Hii from dann lib ";
	char rbuffer[128];

	sendToNode(&serverNode, (const uint8_t *)buffer, sizeof(buffer));
	recvFromNode(&serverNode, (uint8_t *)rbuffer, sizeof(rbuffer));

	consolelog(rbuffer, CONSOLELOG::INFOLOG);

	return 0;
}