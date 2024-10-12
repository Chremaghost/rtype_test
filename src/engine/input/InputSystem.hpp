#pragma once
#include "../ECS/Entity.hpp"
#include "../ECS/InputComponent.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <vector>

class InputSystem {
public:
    void update(std::vector<std::shared_ptr<Entity>>& entities) {
        for (auto& entity : entities) {
            auto input = entity->getComponent<InputComponent>();
            if (input) {
		input->setKeyPressed(sf::Keyboard::Key::Up, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up));
                input->setKeyPressed(sf::Keyboard::Key::Down, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down));
                input->setKeyPressed(sf::Keyboard::Key::Left, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left));
                input->setKeyPressed(sf::Keyboard::Key::Right, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right));
                input->setKeyPressed(sf::Keyboard::Key::Space, sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space));
            }
        }
    }
};
