#pragma once
#include "../ECS/Entity.hpp"
#include "../factory/EntityFactory.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class SpawningSystem {
public:
    void update(float deltaTime, const sf::Texture& enemyTexture, std::vector<std::shared_ptr<Entity>>& enemies, float& timeSinceLastSpawn) {
        timeSinceLastSpawn += deltaTime;

        if (timeSinceLastSpawn >= spawnInterval) {
            float spawnX = 800.0f;
            float spawnY = static_cast<float>(rand() % 600);
            auto enemy = EntityFactory::createEnemy(enemyTexture, spawnX, spawnY);
            enemies.push_back(enemy);

            timeSinceLastSpawn = 0.0f;
        }

        // Déplacer les ennemis vers la gauche
        for (auto& enemy : enemies) {
            auto physics = enemy->getComponent<PhysicsComponent>();
            if (physics) {
                physics->velocityX = -100.0f; // Vitesse de l'ennemi vers la gauche
            }
        }
    }

private:
    const float spawnInterval = 2.0f; // Intervalle de temps entre chaque spawn d'ennemi
};
