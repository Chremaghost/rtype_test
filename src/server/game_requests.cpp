/*
** EPITECH PROJECT, 2024
** RTYPE
** File description:
** RTYPE
*/

#include "create_server.hpp"

void server::game_requests(std::string commands)
{
    if (commands == "des") {
        bomb.destroy_bombs(15);
    } else if (commands == "launch") {
        bomb.launch_bombs(2);
    } else if (commands == "mvl") {
        ships.move_left(2);
    } else if (commands == "mvr") {
        ships.move_right(2);
    } else if (commands == "mvu") {
        ships.move_up(2);
    } else if (commands == "mvd") {
        ships.move_down(2);
    }
}
