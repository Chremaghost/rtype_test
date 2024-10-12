/*
** EPITECH PROJECT, 2024
** make_ennemies_appear.cpp
** File description:
** make_ennemies_appear.cpp
*/

#include "ennemies.hpp"

Opponent::Opponent() {
    pv = 100;
    x_ennemie = 1930;
    y_ennemie = rand() % 590;
    ennemie_speed = 300;
}

Opponent::~Opponent() {

}

void Opponent::enemy_move_left(float time) {
    x_ennemie -= ennemie_speed * time;
}

void Opponent::enemy_move_right(float time) {
    x_ennemie += ennemie_speed * time;
}

void Opponent::enemy_move_up(float time) {
    y_ennemie -= ennemie_speed * time;
}

void Opponent::enemy_move_down(float time) {
    y_ennemie += ennemie_speed * time;
}

void Opponent::destroy_ennemies(bool check) {
    if (check == true) {
        pv -= 10;
    }
}
