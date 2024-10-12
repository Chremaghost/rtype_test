/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

#ifndef RTYPE
    #define RTYPE
    #include <boost/asio.hpp>
    #include <iostream>
    #include <cstring>
    #include <string>
    #include <array>
    #include <ctime>
    #include "../../Game_Play/space_ship_move.hpp"
    #include "../../Game_Play/launch_bombs.hpp"

class server {
    private:
    int sock;
    Bombs bomb;
    Space_Ship ships;

    public:
    server();
    ~server();
    void create_server(char **argv);
    std::string make_daytime_string(void);
    void game_requests(std::string commands);
};

#endif
