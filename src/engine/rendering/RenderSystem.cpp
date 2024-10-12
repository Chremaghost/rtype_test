// RenderSystem.cpp
#include "RenderSystem.hpp"

void RenderSystem::render(sf::RenderWindow& window, std::vector<std::shared_ptr<Entity>>& entities) {
    for (const auto& entity : entities) {
        auto render = entity->getComponent<RenderComponent>();
        auto transform = entity->getComponent<TransformComponent>();

        if (render && transform) {
            render->setPosition(transform->x, transform->y);
            window.draw(render->getSprite());
        } else {
            if (!render) {
                std::cerr << "RenderComponent not found for entity." << std::endl;
            }
            if (!transform) {
	      std::cerr << "TransformComponent not found for entity." << std::endl;
            }
        }
    }
}
