#pragma once
#include "Component.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <map>

class InputComponent : public Component {
public:
    InputComponent() {
        keys[sf::Keyboard::Key::Up] = false;
        keys[sf::Keyboard::Key::Down] = false;
        keys[sf::Keyboard::Key::Left] = false;
        keys[sf::Keyboard::Key::Right] = false;
        keys[sf::Keyboard::Key::Space] = false;
    }
    bool isKeyPressed(sf::Keyboard::Key key) const {
        auto it = keys.find(key);
        return it != keys.end() ? it->second : false;
    }

    void setKeyPressed(sf::Keyboard::Key key, bool pressed) {
        keys[key] = pressed;
    }

private:
    std::map<sf::Keyboard::Key, bool> keys;
};
