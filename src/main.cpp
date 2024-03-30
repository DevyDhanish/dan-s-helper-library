#include "../include/danlib.hpp"
#include <vector>

void onClientConnect(struct node *clientNode)
{
	char ip[255];
	memset(ip, '\0', sizeof(ip));
	recvFromNode(clientNode, (uint8_t *)ip, sizeof(ip));
	consolelog(ip, CONSOLELOG::INFOLOG);
}

int main()
{
	initNetworking();

	node serverNode;

	serverNode = createNode("localhost", "4444", NETTYPE::IPTYPE::IPV4, NETTYPE::SOCKTYPE::TCP, 5, 5);

	std::vector<struct node *> nodes;

	//HANDLE threadId = listenOnNode(&serverNode, &nodes, 10, &onClientConnect);

	consolelog(serverNode.ip, CONSOLELOG::INFOLOG);

	std::string input;
	while(1)
	{
		// wast time
		std::cout << "> ";
		std::getline(std::cin, input);
		consolelog(input, CONSOLELOG::DEBUGLOG);
	}

	return 0;
}