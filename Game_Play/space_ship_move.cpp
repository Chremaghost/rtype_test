/*
** EPITECH PROJECT, 2024
** space_ship_move.cpp
** File description:
** space_ship_move.cpp
*/

#include "space_ship_move.hpp"

Space_Ship::Space_Ship() {
    x_ship = 100;
    y_ship = 540;
    high_score = 0;
    speed_ship = 200;
}

Space_Ship::~Space_Ship() {

}

void Space_Ship::move_left(float time) {
    x_ship -= speed_ship * time;
}

void Space_Ship::move_right(float time) {
    x_ship += speed_ship * time;
}

void Space_Ship::move_up(float time) {
    y_ship -= speed_ship * time;
}

void Space_Ship::move_down(float time) {
    y_ship += speed_ship * time;
}

void Space_Ship::write_file_score()
{
    std::ofstream file("./Game_Play/high_score.txt");
    if (file.is_open()) {
        file << high_score;
    } else {
        std::cerr << "Erreur opening" << std::endl;
        std::exit (84);
    }
    file.close();
}

std::string Space_Ship::read_file_score()
{
    std::string line;
    std::ifstream file("./Game_Play/high_score.txt");
    if (file.is_open()) {
        while (std::getline(file, line)) {
            high_score = std::stoi(line);
        }
    } else {
        std::cerr << "Erreur opening" << std::endl;
        std::exit (84);
    }
    file.close();
    std::string str = std::to_string(high_score);
    return (str);
}

bool Space_Ship::destroy_ship(float ship_pos_x, float ship_pos_y, float ship_width, float ship_height, 
    float opponent_pos_x, float opponent_pos_y,  float opponent_width, float opponent_height) {
    if ((ship_pos_x < opponent_pos_x + opponent_width && opponent_pos_x < ship_pos_x + ship_width) 
        && (ship_pos_y < opponent_pos_y + opponent_width && opponent_pos_y < ship_pos_y + ship_width)) {
        return true;
    }
    return false;
}