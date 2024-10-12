#pragma once
#include "Component.hpp"

class HealthComponent : public Component {
public:
    int health;

    HealthComponent(int hp) : health(hp) {}

    bool isDead() const {
        return health <= 0;
    }
};
