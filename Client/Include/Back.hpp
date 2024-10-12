/*
** EPITECH PROJECT, 2024
** ncurses.hpp
** File description:
** ncurses.hpp
*/

#pragma once
    #include <iostream>
    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <vector>
    #include <string>
    #include <cstdlib>
    #include <ctime>
    #include <random>
    #include "../../Game_Play/manage_bombs.hpp"
    #include "../../Game_Play/space_ship_move.hpp"
    #include "../../Game_Play/ennemies.hpp"
    #include "../../Game_Play/boss_enemy.hpp"


struct Ship {
    sf::Sprite sprite;
    float speed;
};
class Bombshells {
public:
    sf::Sprite sprite_b;
    Manage_bombs bomb;
    Bombshells(const sf::Texture& texture, float x, float y) {

        sprite_b.setTexture(texture);
        sprite_b.setPosition(x, y);
    }
    ~Bombshells() {}
    void launch_bombs(float time);
};

class Enemy {
public:
    sf::Sprite sprite;
    Opponent enem;

    Enemy(const sf::Texture& texture)
    {
        sprite.setTexture(texture);
        sprite.setPosition(200, 700);
    }

    ~Enemy() {}

    void make_appear_and_move_opponent(float time);
};