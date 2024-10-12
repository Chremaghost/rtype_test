/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

// Client.hpp
#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <netinet/in.h>
#include "Packet.hpp"

class UDPClient {
public:
    UDPClient(const std::string& serverIP, int port);
    void sendCommand(const std::string& command);
    std::string receiveResponse();

private:
    int clientSocket;
    sockaddr_in serverAddr;
};

#endif // CLIENT_HPP
