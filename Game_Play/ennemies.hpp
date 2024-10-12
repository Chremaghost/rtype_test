/*
** EPITECH PROJECT, 2024
** make_ennemies_appear.hpp
** File description:
** make_ennemies_appear.hpp
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
#include <cstdlib>

class Opponent {
    public:
    Opponent();
    ~Opponent();

    void enemy_move_left(float time);
    void enemy_move_right(float time);
    void enemy_move_up(float time);
    void enemy_move_down(float time);
    void destroy_ennemies(bool check);
    float x_ennemie;
    float y_ennemie;
    float ennemie_speed;
    int pv;
};