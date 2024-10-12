/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

// Packet.hpp
#ifndef PACKET_HPP
#define PACKET_HPP

#include <vector>
#include <string>

class Packet {
public:
    Packet(const std::string& command);
    std::vector<char> serialize() const;
    static Packet deserialize(const std::vector<char>& data);

    std::string getCommand() const;
    
private:
    std::string command;
};

#endif // PACKET_HPP
