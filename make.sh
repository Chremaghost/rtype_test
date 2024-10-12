#!/bin/bash

echo "Building project..."

if [ -d "build" ]; then
    rm -rf build
    echo "Previous build files cleaned."
fi

mkdir -p build
cd build

# Vérifier si Conan est installé
if ! command -v conan &> /dev/null; then
    echo "Conan n'est pas installé. Veuillez l'installer avant de continuer."
    exit 1
fi

cmake .. 

conan install .. --build=missing
cmake --build . --config Release

echo "Build complete!"
