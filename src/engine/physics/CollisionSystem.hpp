#pragma once
#include "../ECS/Entity.hpp"
#include "../ECS/TransformComponent.hpp"
#include "CollisionComponent.hpp"
#include "../ECS/HealthComponent.hpp"
#include "../sound/SoundSystem.hpp"
#include "../gameplay/ScoreSystem.hpp"
#include <vector>
#include <iostream>

class CollisionSystem {
public:
    void update(
        std::shared_ptr<Entity>& player,
        std::vector<std::shared_ptr<Entity>>& enemies,
        std::vector<std::shared_ptr<Entity>>& missiles,
        SoundSystem& soundSystem,
        ScoreSystem& scoreSystem
    ) {
        auto playerTransform = player->getComponent<TransformComponent>();
        auto playerCollision = player->getComponent<CollisionComponent>();
        auto playerHealth = player->getComponent<HealthComponent>();

        // Vérification des collisions entre le joueur et les ennemis
        for (size_t i = 0; i < enemies.size(); ++i) {
            auto enemy = enemies[i];
            auto enemyTransform = enemy->getComponent<TransformComponent>();
            auto enemyCollision = enemy->getComponent<CollisionComponent>();
            auto enemyHealth = enemy->getComponent<HealthComponent>();
            if (!enemyTransform || !enemyCollision || !enemyHealth) continue;
            // Collision joueur-ennemi
            if (isColliding(*playerTransform, *playerCollision, *enemyTransform, *enemyCollision)) {
                if (playerHealth) {
                    playerHealth->health -= 10;  // Réduire les points de vie du joueur
                    if (playerHealth->isDead()) {
                        std::cout << "Game Over: Player has died." << std::endl;
                        // Ajoutez une logique de fin de partie ici
                    }
                }
                enemies.erase(enemies.begin() + i);  // Supprimer l'ennemi après collision
                break;  // Sortir de la boucle, car une collision a eu lieu
            }
        }

        // Vérification des collisions entre les missiles et les ennemis
        for (size_t i = 0; i < enemies.size(); ++i) {
            auto enemy = enemies[i];
            auto transformA = enemy->getComponent<TransformComponent>();
            auto collisionA = enemy->getComponent<CollisionComponent>();
            auto healthA = enemy->getComponent<HealthComponent>();

            if (!transformA || !collisionA || !healthA) continue;

            for (size_t j = 0; j < missiles.size(); ++j) {
                auto missile = missiles[j];
                auto transformB = missile->getComponent<TransformComponent>();
                auto collisionB = missile->getComponent<CollisionComponent>();

                if (!transformB || !collisionB) continue;

                // Collision missile-ennemi
                if (isColliding(*transformA, *collisionA, *transformB, *collisionB)) {
                    std::cout << "Enemy hit by missile!" << std::endl;
                    healthA->health -= 10;

                    // Si l'ennemi est détruit
                    if (healthA->isDead()) {
                        scoreSystem.addPoints(100);  // Ajouter des points au score
                        soundSystem.playSound("explosion");  // Jouer le son d'explosion
                        enemies.erase(enemies.begin() + i);  // Supprimer l'ennemi
                    }

                    missiles.erase(missiles.begin() + j);  // Supprimer le missile
                    break;
                }
            }
        }
    }

private:
    bool isColliding(const TransformComponent& tA, const CollisionComponent& cA, const TransformComponent& tB, const CollisionComponent& cB) {
        return tA.x < tB.x + cB.width &&
               tA.x + cA.width > tB.x &&
               tA.y < tB.y + cB.height &&
               tA.y + cA.height > tB.y;
    }
};
