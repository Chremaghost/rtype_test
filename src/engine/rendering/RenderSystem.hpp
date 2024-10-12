#pragma once
#include "../ECS/Entity.hpp"
#include "../ECS/TransformComponent.hpp"
#include "RenderComponent.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>  // Pour le débogage

class RenderSystem {
public:
    void render(sf::RenderWindow& window, std::vector<std::shared_ptr<Entity>>& entities);
};
