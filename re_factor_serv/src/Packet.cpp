/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

// Packet.cpp
#include "Packet.hpp"
#include <cstring>

Packet::Packet(const std::string& command) : command(command) {}

std::vector<char> Packet::serialize() const {
    std::vector<char> buffer(command.size() + 1);
    std::strcpy(buffer.data(), command.c_str());
    return buffer;
}

Packet Packet::deserialize(const std::vector<char>& data) {
    std::string command(data.data());
    return Packet(command);
}

std::string Packet::getCommand() const {
    return command;
}
