#pragma once
#include "Component.hpp"

class TransformComponent : public Component {
public:
    float x, y;

    TransformComponent(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
};
