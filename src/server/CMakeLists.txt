# src/server/CMakeLists.txt

# Ajouter les fichiers source du serveur
set(SERVER_SOURCE_FILES
    ServerNetworkManager.cpp
    # Ajoutez d'autres fichiers sources ici si nécessaire
)

# Ajouter les fichiers sources du serveur à l'exécutable
target_sources(rtype_server PRIVATE ${SERVER_SOURCE_FILES})

# Inclure les répertoires d'en-têtes
target_include_directories(rtype_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
