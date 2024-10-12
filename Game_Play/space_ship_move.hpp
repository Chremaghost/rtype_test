/*
** EPITECH PROJECT, 2024
** space_ship_move.hpp
** File description:
** space_ship_move.hpp
*/

#pragma once

#include <dlfcn.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include "../Client/Include/Back.hpp"

class Space_Ship {
    public:
    Space_Ship();
    ~Space_Ship();
    void move_left(float time);
    void move_right(float time);
    void move_up(float time);
    void move_down(float time);
    void write_file_score();
    std::string read_file_score();
    bool destroy_ship(float ship_pos_x, float ship_pos_y, float ship_width, float ship_height, 
        float opponent_pos_x, float opponent_pos_y,  float opponent_width, float opponent_height);
    float x_ship;
    float y_ship;
    float speed_ship;
    int high_score;
};