cmake_minimum_required(VERSION 3.15)
project(RType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIENT_BINARY "rtype-client")
set(SERVER_BINARY "rtype-server")

# Include vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Declaration des bibliothèques à lier
set(BOOST_LIBRARIES asio system filesystem thread)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")

# Fichiers source réseau
set(NETWORK_SOURCES
    src/client/ClientNetworkManager.cpp
    src/server/ServerNetworkManager.cpp
    # Autres fichiers réseau
)

# Fichiers source ECS
file(GLOB ECS_SOURCES
    src/engine/ECS/*.cpp
    src/engine/input/*.cpp
    src/engine/physics/*.cpp
    src/engine/rendering/*.cpp
    src/engine/sound/*.cpp
    src/engine/gameplay/*.cpp
    src/engine/factory/*.cpp
    src/engine/spawn/*.cpp
    src/engine/utils/*.cpp
    src/engine/combat/*.cpp
)

if(NOT ECS_SOURCES)
    message(FATAL_ERROR "Aucun fichier source trouvé dans src/engine/ECS/")
endif()

# Fichiers sources du client
set(CLIENT_SOURCES ${NETWORK_SOURCES} ${ECS_SOURCES}
    src/main_client.cpp
)

# Fichiers sources du serveur
set(SERVER_SOURCES ${NETWORK_SOURCES} ${ECS_SOURCES}
    src/main_server.cpp
)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS ${BOOST_LIBRARIES})
find_package(SFML REQUIRED COMPONENTS graphics window system audio)

# Création de l'exécutable client
add_executable(${CLIENT_BINARY} ${CLIENT_SOURCES})

# Lien des bibliothèques pour le client
target_link_libraries(${CLIENT_BINARY}
    PRIVATE
    Threads::Threads
    Boost::system
    Boost::filesystem
    Boost::asio
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Création de l'exécutable serveur
add_executable(${SERVER_BINARY} ${SERVER_SOURCES})

# Lien des bibliothèques pour le serveur
target_link_libraries(${SERVER_BINARY}
    PRIVATE
    Threads::Threads
    Boost::system
    Boost::filesystem
)

# Répertoires d'inclusion pour le client
target_include_directories(${CLIENT_BINARY} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/ECS/
)

# Répertoires d'inclusion pour le serveur
target_include_directories(${SERVER_BINARY} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/Game_Play/
)

# Gestion multiplateforme pour les commandes personnalisées
add_custom_command(TARGET ${CLIENT_BINARY} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${CLIENT_BINARY}>/assets
)
