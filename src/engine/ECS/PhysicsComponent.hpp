#pragma once
#include "Component.hpp"

class PhysicsComponent : public Component {
public:
    float velocityX, velocityY;
    float accelerationX, accelerationY;

    PhysicsComponent(float vX = 0.0f, float vY = 0.0f, float aX = 0.0f, float aY = 0.0f)
        : velocityX(vX), velocityY(vY), accelerationX(aX), accelerationY(aY) {}
};
