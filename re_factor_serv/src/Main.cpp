/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

// Main.cpp
#include "server/Server.hpp"
#include "client/Client.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./program <server|client> <port>" << std::endl;
        return 84;
    }

    std::string mode = argv[1];
    int port = std::stoi(argv[2]);

    if (mode == "server") {
        UDPServer server(port);
        server.run();
    } else if (mode == "client") {
        UDPClient client("127.0.0.1", port);
        std::string command;

        while (true) {
            std::cout << "Enter command (des, launch, mvl, mvr, mvu, mvd): ";
            std::cin >> command;

            client.sendCommand(command);
            std::string response = client.receiveResponse();
            std::cout << "Server response: " << response << std::endl;
        }
    } else {
        std::cerr << "Unknown mode: " << mode << std::endl;
        return 84;
    }

    return 0;
}
