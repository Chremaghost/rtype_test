/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

#include "Packet.hpp"

int main(int argc, char const *argv[]) {
    if (argc > 1 && std::string(argv[1]) == "server") {
        runServer();
    } else {
        runClient(); 
    }
    
    return 0;
}
