/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

// Server.hpp
#ifndef SERVER_HPP
#define SERVER_HPP

#include <netinet/in.h>
#include "Packet.hpp"

class UDPServer {
public:
    UDPServer(int port);
    ~UDPServer();
    void run();
    void stop();

private:
    int serverSocket;
    sockaddr_in serverAddr;
    bool isRunning;

    void handleClient(sockaddr_in& clientAddr, socklen_t clientLen, const Packet& packet);
    void sendResponse(sockaddr_in& clientAddr, socklen_t clientLen, const Packet& packet);
};

#endif // SERVER_HPP
