#pragma once
#include <unordered_map>
#include <string>
#include <memory>

class Component;

class Entity {
public:
    Entity() = default;
    ~Entity() = default;

    template <typename T>
    void addComponent(std::shared_ptr<T> component) {
        components[typeid(T).name()] = component;
    }

    template <typename T>
    std::shared_ptr<T> getComponent() {
        return std::static_pointer_cast<T>(components[typeid(T).name()]);
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Component>> components;
};
