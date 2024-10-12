#pragma once
#include "../ECS/Component.hpp"
#include <SFML/Graphics.hpp>

class RenderComponent : public Component {
public:
    RenderComponent(const sf::Texture& texture) : sprite(texture) {
    }
    void setPosition(float x, float y) {
        sprite.setPosition(sf::Vector2f(x, y));
    }

    const sf::Sprite& getSprite() const {
        return sprite;
    }

    sf::Sprite sprite;
};
