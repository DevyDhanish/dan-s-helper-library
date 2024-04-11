#include "../include/networking/node.hpp"
#include "../include/debug/debug.hpp"

void fillUpNode(struct node *node, addrinfo *result, uint16_t port, std::string hostname)
{
	node->socketAddr = (sockaddr_in *) result->ai_addr;
	node->size = result->ai_addrlen;
	node->port = port;
	node->hostname = hostname;
}