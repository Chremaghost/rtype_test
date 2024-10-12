/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

#include "Packet.hpp"
#include <iostream>
#include <cstring>   
#include <unistd.h>  
#include <arpa/inet.h>

std::string Packet::serialize() const {
    size_t cmd_len = command.size();
    std::string serialized;
    
    serialized.append(reinterpret_cast<const char*>(&cmd_len), sizeof(cmd_len));
    serialized.append(command);
    
    serialized.append(reinterpret_cast<const char*>(&argument), sizeof(argument));
    
    return serialized;
}

void Packet::deserialize(const std::string& data) {
    size_t cmd_len;
    
    memcpy(&cmd_len, data.data(), sizeof(cmd_len));

    command = std::string(data.data() + sizeof(cmd_len), cmd_len);

    memcpy(&argument, data.data() + sizeof(cmd_len) + cmd_len, sizeof(argument));
}

void* Packet::sendPacket(void* arg) {
    int socket_fd = *(int*)arg;
    Packet packet("launch", 10);  
    std::string serialized_packet = packet.serialize(); 

    send(socket_fd, serialized_packet.c_str(), serialized_packet.size(), 0);
    std::cout << "Packet sent: " << packet.getCommand() << " with argument " << packet.getArgument() << std::endl;
    return nullptr;
}

void* Packet::receivePacket(void* arg) {
    int socket_fd = *(int*)arg;
    char buffer[512] = {0};  
    read(socket_fd, buffer, sizeof(buffer)); 

    Packet packet;
    packet.deserialize(std::string(buffer, sizeof(buffer)));
    std::cout << "Received command: " << packet.getCommand() << ", Argument: " << packet.getArgument() << std::endl;
    return nullptr;
}

void runServer() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    listen(server_fd, 3);

    std::cout << "Server is waiting for connections..." << std::endl;

    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    pthread_t send_thread, receive_thread;
    
    pthread_create(&send_thread, nullptr, Packet::sendPacket, &new_socket);
    pthread_create(&receive_thread, nullptr, Packet::receivePacket, &new_socket);

    pthread_join(send_thread, nullptr);
    pthread_join(receive_thread, nullptr);

    close(new_socket);
    close(server_fd);
}

void runClient() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    pthread_t send_thread, receive_thread;

    pthread_create(&send_thread, nullptr, Packet::sendPacket, &sock);
    pthread_create(&receive_thread, nullptr, Packet::receivePacket, &sock);

    pthread_join(send_thread, nullptr);
    pthread_join(receive_thread, nullptr);

    close(sock);
}
