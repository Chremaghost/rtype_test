#pragma once
#include "../ECS/Component.hpp"

class CollisionComponent : public Component {
public:
    float width, height;

    CollisionComponent(float w, float h) : width(w), height(h) {}
};
