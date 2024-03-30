/*
   Property of [Dhanish aka dan]
   [header file for node methods. link the binary with `.lib`]
   [written @ 22:51 22 march 2024]
*/

#pragma once

#include <winsock2.h>
#include <string>

struct node
{
	std::string hostname;			// this is the ip getaddrinfo will give us
	unsigned short port;	// this port will only be filled with usefull info. if this node represents a server. clients will have this values as 0
	unsigned long size;
	std::string ip;			// this is the actual victims ip we got after the connect as made

#ifdef _WIN32
	sockaddr_in *socketAddr;
	SOCKET socket;
#endif
};

void fillUpNode(struct node *node, addrinfo *result, uint16_t port, std::string hostname);