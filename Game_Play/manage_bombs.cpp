/*
** EPITECH PROJECT, 2024
** launch_bombs.cpp
** File description:
** launch_bombs.cpp
*/

#include "manage_bombs.hpp"

Manage_bombs::Manage_bombs() {
    x_bombs = 100;
    y_bombs = 540;
    speed_bombs = 500;
}

Manage_bombs::~Manage_bombs() {
    
}

void Manage_bombs::launch_bombs(float time) {
    x_bombs = time * speed_bombs;
}

bool Manage_bombs::destroy_bombs(int window_tall) {

    if (x_bombs > window_tall) {
        return true;
    }
    return false;
}

bool Manage_bombs::destroy_opponent(float bomb_pos_x, float bomb_pos_y, float bomb_width, float bomb_height, 
    float opponent_pos_x, float opponent_pos_y,  float opponent_width, float opponent_height) {
    if ((bomb_pos_x < opponent_pos_x + opponent_width && opponent_pos_x < bomb_pos_x + bomb_width) 
        && (bomb_pos_y < opponent_pos_y + opponent_width && opponent_pos_y < bomb_pos_y + bomb_width)) {
        return true;
    }
    return false;
}