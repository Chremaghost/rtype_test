/*
** EPITECH PROJECT, 2024
** launch_bombs.hpp
** File description:
** launch_bombs.hpp
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
#include <ctime>

class Manage_bombs {
    public:
    Manage_bombs();
    ~Manage_bombs();
    void launch_bombs(float time);
    bool destroy_bombs(int window_tall);
    bool destroy_opponent(float bomb_pos_x, float bomb_pos_y, 
        float bomb_width, float bomb_height, float opponent_pos_x, 
        float opponent_pos_y, float opponent_width, float opponent_height);
    float x_bombs;
    float y_bombs;
    float speed_bombs;
};