/*
    Property of [Dhanish aka dan]
    [header file for networking methods. link the binary with `danLib.lib`]
    [
        provides networking methods for developers, it's basically a wrapper
        for win32 winsock2 library and linux's socket library.

        part of dan's malware devlopment kit.
    ]
    [Version: 1.0]
    [Author: Dhanish]
    [Contact: vibingfrog7@gmail.com]
    [License: Proprietary]
    [Platform: Windows, Linux]
    [Dependencies: None]
    [written @ 12:13 26 march 2024]
*/

# pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdint.h>
#include <string>
#include <vector>

namespace NETTYPE
{
    enum IPTYPE
    {
        IPV4,
        IPV6
    };

    enum SOCKTYPE
    {
        TCP,
        UDP
    };
};

void initNetworking();

struct node createNode(std::string ip, std::string port, NETTYPE::IPTYPE iptype, NETTYPE::SOCKTYPE socktype, uint32_t interval, uint32_t hostresolvetries);

HANDLE listenOnNode(struct node *node, std::vector<struct node *> *nodes, int maxcon, void (*callback)(struct node *node));

void connectToNode(struct node *node);

void recvFromNode(struct node *node, uint8_t *buffer, const uint32_t size);

void sendToNode(struct node *node, const uint8_t* buffer, const uint32_t size);