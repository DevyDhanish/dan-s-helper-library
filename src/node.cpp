#include "../include/networking/node.hpp"
#include "../include/debug/debug.hpp"
#include <WS2tcpip.h>
#include <stdio.h>
#include <synchapi.h>
#include <string>

void fillUpNode(struct node *node, addrinfo *result, uint16_t port, std::string hostname)
{
	node->socketAddr = (sockaddr_in *) result->ai_addr;
	node->size = result->ai_addrlen;
	node->socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	node->port = port;
	node->hostname = hostname;
}