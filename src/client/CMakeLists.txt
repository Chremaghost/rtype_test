# src/client/CMakeLists.txt

# Ajouter les fichiers source du client
set(CLIENT_SOURCE_FILES
    ClientNetworkManager.cpp
    # Ajoutez d'autres fichiers sources ici si nécessaire
)

# Ajouter les fichiers sources du client à l'exécutable
target_sources(rtype_client PRIVATE ${CLIENT_SOURCE_FILES})

# Inclure les répertoires d'en-têtes
target_include_directories(rtype_client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
