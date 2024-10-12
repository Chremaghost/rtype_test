/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

// Server.cpp
#include "Server.hpp"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

UDPServer::UDPServer(int port) {
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        perror("Cannot create socket");
        exit(84);
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // localhost
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(84);
    }

    isRunning = true;
}

UDPServer::~UDPServer() {
    stop();
}

void UDPServer::run() {
    std::cout << "Server is running on localhost..." << std::endl;

    while (isRunning) {
        char buffer[1024];
        sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);

        int n = recvfrom(serverSocket, buffer, 1024, 0, (struct sockaddr*)&clientAddr, &clientLen);
        if (n < 0) {
            perror("Receive failed");
            continue;
        }

        std::vector<char> data(buffer, buffer + n);
        Packet packet = Packet::deserialize(data);
        handleClient(clientAddr, clientLen, packet);
    }
}

void UDPServer::stop() {
    close(serverSocket);
    std::cout << "Server stopped" << std::endl;
}

void UDPServer::handleClient(sockaddr_in& clientAddr, socklen_t clientLen, const Packet& packet) {
    std::string command = packet.getCommand();
    std::cout << "Received command from client: " << command << std::endl;

    // Handle game logic based on command
    std::string response;
    if (command == "des") response = "456";
    else if (command == "launch") response = "250";
    else if (command == "mvl") response = "230";
    else if (command == "mvr") response = "210";
    else if (command == "mvu") response = "240";
    else if (command == "mvd") response = "280";
    else response = "Unknown command";

    Packet responsePacket(response);
    sendResponse(clientAddr, clientLen, responsePacket);
}

void UDPServer::sendResponse(sockaddr_in& clientAddr, socklen_t clientLen, const Packet& packet) {
    std::vector<char> buffer = packet.serialize();
    sendto(serverSocket, buffer.data(), buffer.size(), 0, (struct sockaddr*)&clientAddr, clientLen);
}
