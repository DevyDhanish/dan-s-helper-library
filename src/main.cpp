#include "../include/danlib.hpp"
#include <vector>

void onDataRecv(char *buffer, uint32_t size)
{
	std::vector<std::string> word = splitIntoVector(buffer, ';', size);
}

int main()
{
	initNetworking();

	node serverNode;

	serverNode = createNode("0.tcp.in.ngrok.io", "17790", NETTYPE::IPTYPE::IPV4, NETTYPE::SOCKTYPE::TCP, 5, 5);

	connectToNode(&serverNode);

	HANDLE recvThread = recvFromNode(&serverNode, &onDataRecv);

	while(1) {}

	return 0;
}