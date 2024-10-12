/*
** EPITECH PROJECT, 2024
** boss_enemy.hpp
** File description:
** boss_enemy.hpp
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

class Boss_enemy {
    public:
    Boss_enemy();
    ~Boss_enemy();

    std::string decrease_pv(bool check);
    bool destroy_boss(float boss_pos_x, float boss_pos_y, 
        float boss_width, float boss_height, float opponent_pos_x, 
        float opponent_pos_y, float opponent_width, float opponent_height);
    int pv;
};