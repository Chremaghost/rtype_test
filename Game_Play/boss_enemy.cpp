/*
** EPITECH PROJECT, 2024
** boss_enemy.cpp
** File description:
** boss_enemy.cpp
*/

#include "boss_enemy.hpp"

Boss_enemy::Boss_enemy() {
    pv = 100000;
}

Boss_enemy::~Boss_enemy() {

}

std::string Boss_enemy::decrease_pv(bool check) {
    std::string str = "Big boss enemy defeated!";
    if (pv == 0) {
        return (str);
    }
    if (check) {
        pv -= 5;
    }
    return ("");
}

bool Boss_enemy::destroy_boss(float boss_pos_x, float boss_pos_y, 
        float boss_width, float boss_height, float opponent_pos_x, 
        float opponent_pos_y, float opponent_width, float opponent_height) {

        if ((boss_pos_x < opponent_pos_x + opponent_width && opponent_pos_x < boss_pos_x + boss_width) 
        && (boss_pos_y < opponent_pos_y + opponent_width && opponent_pos_y < boss_pos_y + boss_width)) {
        return true;
    }
    return false;

}   