#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../ECS/HealthComponent.hpp"
#include "../ECS/Entity.hpp"

class GameOverSystem {
public:
    bool isGameOver = false;

    // Vérifie si la partie est terminée
    void checkGameOver(std::shared_ptr<Entity>& player) {
        auto health = player->getComponent<HealthComponent>();
        if (health && health->isDead()) {
            isGameOver = true;
            std::cout << "Game Over: Player has died." << std::endl;
        }
    }

    // Affiche un écran de fin de partie
    void displayGameOver(sf::RenderWindow& window) {
        if (isGameOver) {
            sf::Font font;
            if (!font.loadFromFile("assets/fonts/game_font.ttf")) {
                std::cerr << "Erreur lors du chargement de la police." << std::endl;
            }

            sf::Text gameOverText("GAME OVER", font, 50);
            gameOverText.setFillColor(sf::Color::Red);
            gameOverText.setPosition(200, 250);  // Positionner le texte au centre de l'écran

            window.clear();
            window.draw(gameOverText);
            window.display();
        }
    }
};
