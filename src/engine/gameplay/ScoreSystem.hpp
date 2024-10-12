#pragma once
#include <iostream>

class ScoreSystem {
public:
    int score = 0;

    void addPoints(int points) {
        score += points;
        std::cout << "Score: " << score << std::endl;
    }
};
