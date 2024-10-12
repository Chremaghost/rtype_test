#pragma once
#include "../ECS/Entity.hpp"
#include "../ECS/PhysicsComponent.hpp"
#include "../ECS/TransformComponent.hpp"
#include <vector>

class PhysicsSystem {
public:
    void update(float deltaTime, std::vector<std::shared_ptr<Entity>>& entities) {
        for (auto& entity : entities) {
            auto physics = entity->getComponent<PhysicsComponent>();
            auto transform = entity->getComponent<TransformComponent>();
            if (physics && transform) {
                // Appliquer l'accélération à la vitesse
                physics->velocityX += physics->accelerationX * deltaTime;
                physics->velocityY += physics->accelerationY * deltaTime;

                // Appliquer la vitesse à la position
                transform->x += physics->velocityX * deltaTime;
                transform->y += physics->velocityY * deltaTime;
            }
        }
    }
};
