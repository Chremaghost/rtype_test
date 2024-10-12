# src/engine/CMakeLists.txt

# Ajouter les fichiers source du moteur de jeu
set(SOURCE_FILES
    ECS/Entity.cpp
    ECS/Component.cpp
    ECS/TransformComponent.cpp
    ECS/PhysicsComponent.cpp
    ECS/InputComponent.cpp
    rendering/RenderComponent.cpp
    rendering/RenderSystem.cpp
    physics/PhysicsSystem.cpp
    input/InputSystem.cpp
)

# Créer une bibliothèque statique pour le moteur
add_library(engine STATIC ${SOURCE_FILES})

# Inclure les répertoires d'en-têtes
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
