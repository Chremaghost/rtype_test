#pragma once
#include <vector>
#include <memory>

template<typename T>
class ObjectPool {
public:
    // Récupérer un objet du pool
    std::shared_ptr<T> getObject() {
        if (!pool.empty()) {
            std::shared_ptr<T> obj = pool.back();
            pool.pop_back();
            return obj;
        }
        return std::make_shared<T>();  // Créer un nouvel objet si le pool est vide
    }

    // Remettre un objet dans le pool pour le réutiliser
    void returnObject(std::shared_ptr<T> obj) {
        pool.push_back(obj);
    }

private:
    std::vector<std::shared_ptr<T>> pool;  // Pool d'objets réutilisables
};
