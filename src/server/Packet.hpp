/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

#ifndef PACKET_HPP
#define PACKET_HPP

#include <string>
#include <pthread.h>
#include <sys/socket.h>

class Packet {
private:
    std::string command;
    int argument;

public:
    Packet() : command(""), argument(0) {}
    Packet(const std::string& cmd, int arg) : command(cmd), argument(arg) {}

    std::string getCommand() const { return command; }
    int getArgument() const { return argument; }
    void setCommand(const std::string& cmd) { command = cmd; }
    void setArgument(int arg) { argument = arg; }

    std::string serialize() const;

    void deserialize(const std::string& data);

    static void* sendPacket(void* arg);
    static void* receivePacket(void* arg);
};

#endif // PACKET_HPP
