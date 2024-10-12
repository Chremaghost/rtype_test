cmake_minimum_required(VERSION 3.15)
project(RType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLIENT_BINARY "rtype-client")
set(SERVER_BINARY "rtype-server")

# Intégration de CPM
include(cmake/CPM.cmake)

# Ajout de dépendances avec CPM
CPMAddPackage(
    NAME Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.83.0
)

CPMAddPackage(
    NAME SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG master
)

# Vérifiez que les dépendances sont trouvées
find_package(Boost REQUIRED COMPONENTS asio system filesystem thread)
find_package(SFML REQUIRED COMPONENTS graphics window system audio)

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

# Création de l'exécutable client
add_executable(${CLIENT_BINARY} ${CLIENT_SOURCES})

# Lien des bibliothèques pour le client
target_link_libraries(${CLIENT_BINARY}
    PRIVATE
    Threads::Threads
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
    Boost::asio
    Boost::system
    Boost::filesystem
    Boost::thread
)

# Création de l'exécutable serveur
add_executable(${SERVER_BINARY} ${SERVER_SOURCES})

# Lien des bibliothèques pour le serveur
target_link_libraries(${SERVER_BINARY}
    PRIVATE
    Threads::Threads
    sfml-graphics
    sfml-window
    sfml-system
    Boost::asio
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
if (WIN32)
    # Spécificités Windows (par exemple, pour le système de fichiers)
    add_custom_command(TARGET ${CLIENT_BINARY} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${CLIENT_BINARY}>/assets
    )
elseif (UNIX)
    # Spécificités Linux
    add_custom_command(TARGET ${CLIENT_BINARY} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${CLIENT_BINARY}>/assets
    )
endif()
