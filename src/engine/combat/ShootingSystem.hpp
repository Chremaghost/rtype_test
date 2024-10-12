#pragma once
#include "../ECS/Entity.hpp"
#include "../ECS/InputComponent.hpp"
#include "../ECS/TransformComponent.hpp"
#include "../factory/EntityFactory.hpp"
#include "../utils/ObjectPool.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class ShootingSystem {
    ObjectPool<Entity> missilePool;

public:
    void update(std::vector<std::shared_ptr<Entity>>& entities, const sf::Texture& missileTexture, std::vector<std::shared_ptr<Entity>>& missiles) {
        for (auto& entity : entities) {
            auto input = entity->getComponent<InputComponent>();
            auto transform = entity->getComponent<TransformComponent>();

	    if (input && transform && input->isKeyPressed(sf::Keyboard::Key::Space)) {
                // Utiliser le pool pour récupérer un missile
                auto missile = missilePool.getObject();
                missile->addComponent(std::make_shared<TransformComponent>(transform->x, transform->y));
                missile->addComponent(std::make_shared<RenderComponent>(missileTexture));
                missiles.push_back(missile);
            }
        }
    }

    void returnMissile(std::shared_ptr<Entity> missile) {
        missilePool.returnObject(missile);  // Remettre le missile dans le pool
    }
};
