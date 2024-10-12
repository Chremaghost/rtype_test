#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include "engine/ECS/Entity.hpp"
#include "engine/ECS/TransformComponent.hpp"
#include "engine/factory/EntityFactory.hpp"
#include "engine/rendering/RenderSystem.hpp"
#include "engine/physics/PhysicsSystem.hpp"
#include "engine/input/InputSystem.hpp"
#include "engine/physics/CollisionSystem.hpp"
#include "engine/combat/ShootingSystem.hpp"
#include "engine/ECS/InputComponent.hpp"
#include "engine/spawn/SpawningSystem.hpp"
#include "engine/sound/SoundSystem.hpp"
#include "engine/gameplay/GameOverSystem.hpp"
#include "engine/gameplay/ScoreSystem.hpp"

int main() {
    sf::VideoMode videoMode(800, 600);
    sf::RenderWindow window(videoMode, "R-Type Client");
    GameOverSystem gameOverSystem;

    SoundSystem soundSystem;
    soundSystem.loadSounds();  // Charger les sons

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/player.png")) {
        std::cerr << "Erreur lors du chargement de player.png" << std::endl;
        return -1;
    }

    sf::Texture missileTexture;
    if (!missileTexture.loadFromFile("assets/missile.png")) {
        std::cerr << "Erreur lors du chargement de missile.png" << std::endl;
        return -1;
    }

    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("assets/enemy.png")) {
        std::cerr << "Erreur lors du chargement de enemy.png" << std::endl;
        return -1;
    }

    auto player = EntityFactory::createPlayer(playerTexture);
    std::vector<std::shared_ptr<Entity>> enemies;

    RenderSystem renderSystem;
    PhysicsSystem physicsSystem;
    InputSystem inputSystem;
    CollisionSystem collisionSystem;
    ShootingSystem shootingSystem;
    InputComponent input;
    ScoreSystem  scoreSystem;
    SpawningSystem spawningSystem;
    float timeSinceLastSpawn = 0.0f;

    std::vector<std::shared_ptr<Entity>> entities = { player };
    std::vector<std::shared_ptr<Entity>> missiles;

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        float deltaTime = clock.restart().asSeconds();
	if (!gameOverSystem.isGameOver) {
        inputSystem.update(entities);
        physicsSystem.update(deltaTime, entities);
        physicsSystem.update(deltaTime, missiles);
        physicsSystem.update(deltaTime, enemies);
        shootingSystem.update(entities, missileTexture, missiles);
        spawningSystem.update(deltaTime, enemyTexture, enemies, timeSinceLastSpawn);
	collisionSystem.update(player, enemies, missiles, soundSystem, scoreSystem);
        for (auto& entity : entities) {
	    auto inputComp = entity->getComponent<InputComponent>();
            if (inputComp && inputComp->isKeyPressed(sf::Keyboard::Space)) {
                soundSystem.playSound("missile_shoot"); // Son de tir
            }
        }

	soundSystem.update();
	for (size_t i = 0; i < enemies.size(); ++i) {
	auto enemy = enemies[i];
        if (auto health = enemy->getComponent<HealthComponent>()) {
            health->health -= 10;
	    scoreSystem.addPoints(10);
            if (health->isDead()) {
	        enemies.erase(enemies.begin() + i);
		scoreSystem.addPoints(100);
                --i;
            }
        }
	}
        missiles.erase(std::remove_if(missiles.begin(), missiles.end(), [](std::shared_ptr<Entity> missile) {
            auto transform = missile->getComponent<TransformComponent>();
            return transform && (transform->x > 800); // Supprime les missiles hors de l'écran
        }), missiles.end());
	gameOverSystem.checkGameOver(player);
        } else {
        gameOverSystem.displayGameOver(window);
	}

        // Rendu des entités, missiles et ennemis
        window.clear();
        renderSystem.render(window, entities);
        renderSystem.render(window, missiles);
        renderSystem.render(window, enemies);
        window.display();
    }

    return 0;
}
