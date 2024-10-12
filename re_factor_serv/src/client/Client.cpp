/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

#include "Client.hpp"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>  // Include this header for inet_pton

UDPClient::UDPClient(const std::string& serverIP, int port) {
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        perror("Cannot create socket");
        exit(84);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);

    // Convert IP address from string to network byte order
    if (inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        exit(84);
    }
}

void UDPClient::sendCommand(const std::string& command) {
    Packet packet(command);
    std::vector<char> buffer = packet.serialize();
    sendto(clientSocket, buffer.data(), buffer.size(), 0, (const struct sockaddr*)&serverAddr, sizeof(serverAddr));
}

std::string UDPClient::receiveResponse() {
    char buffer[1024];
    int n = recvfrom(clientSocket, buffer, 1024, 0, NULL, NULL);
    if (n < 0) {
        perror("Receive failed");
        exit(84);
    }

    std::vector<char> data(buffer, buffer + n);
    Packet packet = Packet::deserialize(data);
    return packet.getCommand();
}
