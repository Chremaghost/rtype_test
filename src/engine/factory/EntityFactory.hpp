#pragma once
#include "../ECS/Entity.hpp"
#include "../ECS/TransformComponent.hpp"
#include "../rendering/RenderComponent.hpp"
#include "../ECS/PhysicsComponent.hpp"
#include "../ECS/InputComponent.hpp"
#include "../physics/CollisionComponent.hpp"
#include "../ECS/HealthComponent.hpp"
#include <SFML/Graphics.hpp>

class EntityFactory {
public:
    static std::shared_ptr<Entity> createPlayer(const sf::Texture& texture) {
        auto player = std::make_shared<Entity>();
        player->addComponent(std::make_shared<TransformComponent>(100.0f, 100.0f));
        player->addComponent(std::make_shared<RenderComponent>(texture));
        player->addComponent(std::make_shared<PhysicsComponent>());
        player->addComponent(std::make_shared<InputComponent>());
        player->addComponent(std::make_shared<CollisionComponent>(50.0f, 50.0f)); // Taille du joueur
	player->addComponent(std::make_shared<HealthComponent>(100));
        return player;
    }

    static std::shared_ptr<Entity> createEnemy(const sf::Texture& texture, float x, float y) {
        auto enemy = std::make_shared<Entity>();
        enemy->addComponent(std::make_shared<TransformComponent>(x, y));
        enemy->addComponent(std::make_shared<RenderComponent>(texture));
        enemy->addComponent(std::make_shared<PhysicsComponent>());
        enemy->addComponent(std::make_shared<CollisionComponent>(50.0f, 50.0f)); // Taille de l'ennemi
	enemy->addComponent(std::make_shared<HealthComponent>(30));
        return enemy;
    }
    
    static std::shared_ptr<Entity> createMissile(const sf::Texture& texture, float x, float y) {
        auto missile = std::make_shared<Entity>();
        missile->addComponent(std::make_shared<TransformComponent>(x, y));
        missile->addComponent(std::make_shared<RenderComponent>(texture));
        missile->addComponent(std::make_shared<PhysicsComponent>(300.0f, 0.0f)); // Vitesse élevée
        missile->addComponent(std::make_shared<CollisionComponent>(10.0f, 10.0f)); // Taille du missile
        return missile;
    }
};
