# UDP-Based Server-Client Game Project

## Table of Contents

- [Introduction](#introduction)
- [Technologies Used](#technologies-used)
- [Project Overview](#project-overview)
- [Directory Structure](#directory-structure)
- [Server-Client Communication Protocol](#server-client-communication-protocol)
- [Packet Serialization and Deserialization](#packet-serialization-and-deserialization)
- [How to Build and Run](#how-to-build-and-run)
  - [Building the Program](#building-the-program)
  - [Running the Server](#running-the-server)
  - [Running the Client](#running-the-client)
  - [Commands](#commands)
- [Error Handling](#error-handling)
- [How to Test](#how-to-test)
- [Future Improvements](#future-improvements)

## Introduction

This project demonstrates a simple client-server architecture using the UDP protocol for a game-like system. Clients send commands to the server, such as moving a ship or launching/destroying bombs, and the server processes these commands, maintaining game logic and broadcasting responses to connected clients.

## Technologies Used

- **C++**: The core language for implementing the server, client, and game logic.
- **UDP Protocol**: Used for communication between the server and clients. UDP is a connectionless protocol, providing low-latency communication at the cost of guaranteed message delivery.
- **POSIX Sockets**: For establishing network communication over UDP.
- **Multithreading (POSIX threads)**: The server is multithreaded, enabling it to handle multiple client connections simultaneously.
- **Serialization/Deserialization**: Implemented to ensure the transmission of structured data (packets) between clients and the server.
- **Makefile**: To simplify the build process.

## Project Overview

The project consists of two main components: the **Server** and the **Client**.

1. **Server**: Manages all game logic and processes incoming commands from clients. It sends regular updates and responses back to the clients.
2. **Client**: Connects to the server via UDP, sends commands, and receives responses.

The communication between the client and server is done using custom packets that are serialized into binary data and deserialized upon reception.

## Directory Structure

```
├── src/
│   ├── server/
│   │   ├── Server.cpp    # Contains the server-side logic
│   │   └── Server.hpp    # Server class definition
│   ├── client/
│   │   ├── Client.cpp    # Contains the client-side logic
│   │   └── Client.hpp    # Client class definition
│   ├── Packet.cpp        # Handles serialization and deserialization of packets
│   ├── Packet.hpp        # Packet class definition
│   └── Main.cpp          # Entry point of the program (runs server or client)
├── Makefile
└── README.md
```

## Server-Client Communication Protocol

### Client Commands

- **Destroying bombs**: `des`
- **Launching bombs**: `launch`
- **Move ship left**: `mvl`
- **Move ship right**: `mvr`
- **Move ship up**: `mvu`
- **Move ship down**: `mvd`

### Server Responses

- `des` -> 456
- `launch` -> 250
- `mvl` -> 230
- `mvr` -> 210
- `mvu` -> 240
- `mvd` -> 280

All commands and responses are transmitted in binary format.

## Packet Serialization and Deserialization

To facilitate communication between the server and clients, data is transmitted in serialized packets. Each packet contains a command (e.g., "mvl") or a response code (e.g., 230). 

- **Serialization**: Converts the packet structure into a binary format to send over the network.
- **Deserialization**: Converts the received binary data back into a usable packet structure.

## How to Build and Run

### Building the Program

You can build the project using the provided Makefile.

```bash
g++ -Wall -Wextra -std=c++17 -I./src -o server src/server/Server.cpp src/client/Client.cpp src/Packet.cpp src/Main.cpp
```

This will generate the executable `server`.

### Running the Server

You can run the server by specifying the port number to listen on.

```bash
./server server 8080
```

Replace `8080` with the desired port.

### Running the Client

After the server is running, start the client by specifying the server IP address and the port number.

```bash
./server client 8080
```

Replace `127.0.0.1` with the actual server IP address (for local testing, localhost is used), and `8080` with the server's port.

### Commands

You can issue the following commands from the client:

- `des` -> Destroy bombs
- `launch` -> Launch bombs
- `mvl` -> Move ship left
- `mvr` -> Move ship right
- `mvu` -> Move ship up
- `mvd` -> Move ship down

### Example:

To launch a bomb, you can type the following in the client terminal after connecting:

```bash
launch
```

The server will respond with the appropriate code (250).

## Error Handling

- The program returns `84` in case of critical errors (e.g., socket creation failure, binding issues, or failed communication).
- Error messages are printed using `perror()` to indicate the source of failure.

## How to Test

### Testing Locally

1. Start the server:

   ```bash
   ./server server 8080
   ```

2. Open a new terminal and run the client:

   ```bash
   ./server client 8080
   ```

3. Once connected, try sending commands like `mvl` or `launch` from the client terminal. The server should process the command and return the corresponding response code.

### Multithreading and Client Crash Handling

- Start multiple clients to test the server's ability to handle multiple connections simultaneously.
- Close a client abruptly to check if the server can continue handling other clients without crashing.

## Future Improvements

- Add authentication and client management (e.g., tracking connected clients).
- Implement more complex game logic and additional commands.
- Add logging for server activities.
- Optimize packet size and transmission efficiency.


# 🎮 R-Type Client Module 🎮

Welcome to the client module of our shoot 'em up (shmup) video game, R-Type.
This project uses SFML to create an interactive and immersive experience.
This README will guide you through the code structure, functionality, and how to launch it.

📂 File Structure

1. Back.hpp - Class definitions

The Back.hpp file contains the definitions of the main classes used in the game:
💣 Bombshells

    Description: Represents a bomb that can be thrown during the game.
    Attributes :
        sf::Sprite sprite_b: The sprite of the bomb.
        Bomb bomb : Manages the trajectory of the bomb.
    Main method :
        launch_bombs(float time) : Launches and moves the bomb on the screen.

👾 Enemy

    Description: Represents enemies that appear and move during the game.
    Attributes :
        sf::Sprite sprite: The sprite of the enemy.
        Opponent enem: Manages the enemy's movements.
    Main method :
        make_appear_and_move_opponent(float time) : Makes the enemy appear and move.

2. Back.cpp - Method implementations

This file contains the implementation of the methods defined in Back.hpp :
📝 write_text

    Description: Displays text on the screen with a specific position and colour.
    Usage: write_text(window, "Your text", sf::Color::White, x, y, font);

🚀 Bombshells::launch_bombs(float time)

    Description : Launches a bomb and updates its position on the screen.

👾 Enemy::make_appear_and_move_opponent(float time)

    Description : Makes an enemy appear and move in the game.

🎮 play_game(const std::string& username)

    Description : Main function to start the game.
    Functions :
        Loads textures and initializes sprites.
        Manages the display of the different levels.
        Reacts to player actions.

3. Back_menu.cpp - Menu management

This file manages the user interface for the game's main menu. Here's what it offers:

    Intuitive navigation: Use keys such as P to access settings.
                                                      Enter to start the game.
                                                      S for sound.
                                                      E for game help.
                                                      H for home.
                                                      Placeholders to connect to the game.


🎮 Key features

    Bomb throwing: The player can throw bombs in-game to attack enemies.
    Moving enemies: Enemies automatically appear and move throughout the levels.
    User interface : Dynamic and intuitive menu for a pleasant user experience.

🚀 How to launch the game

Install SFML if necessary :

    For Linux: sudo apt-get install libsfml-dev
    For macOS via Homebrew: brew install sfml

Compile the project:

    g++ Back.cpp Back_menu.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system

Run the game :

    ./game

👥 Contributors

Developed by ❤️Babe

🛠 Technologies used

    C++ for game development.
    SFML for managing graphics, sounds, and user interactions.

Enjoy the experience and have fun! 🎉
### prebuild.sh

Le script `prebuild.sh` est exécuté en premier et s'assure que l'environnement de développement est correctement configuré. Il détecte le gestionnaire de paquets disponible sur la machine (parmi `apt-get`, `yum`, `brew`, `pacman`, etc.) et installe les dépendances nécessaires comme `g++`, `CMake`, `Conan`, et des bibliothèques graphiques et audio (OpenAL, SFML, Boost, etc.).

Ce script est essentiel pour préparer l'environnement de compilation sur différentes distributions Linux, ainsi que macOS. Si un gestionnaire de paquets compatible est détecté, il installera automatiquement les outils requis. Sinon, il affichera un message d'erreur et demandera une installation manuelle.

#### Exécution du script `prebuild.sh` :
1. **Détection du gestionnaire de paquets** : 
   Le script détecte si vous utilisez `apt-get`, `yum`, `brew`, ou un autre gestionnaire de paquets.
   
2. **Installation des dépendances** : 
   En fonction du gestionnaire détecté, il installe les paquets nécessaires pour compiler le projet (g++, CMake, Conan, SFML, Boost, etc.).

3. **Configuration de Conan** :
   Le script configure Conan, un gestionnaire de paquets pour C++, pour qu'il soit prêt à gérer les dépendances du projet.

4. **Construction initiale** :
   Le script exécute une première configuration et construction du projet avec CMake.

---

### make.sh

Le script make.sh est exécuté après prebuild.sh. Il gère la création du répertoire de build, nettoie d'éventuels fichiers de compilation précédents, et lance la compilation finale du projet.

#### Étapes du script make.sh :
1. **Nettoyage des anciens fichiers de build** :
   Le script supprime le dossier `build` s'il existe déjà, ce qui assure une construction propre à chaque exécution.

2. **Création du répertoire de build** :
   Si le dossier build n'existe pas, il est créé.

3. **Vérification de l'installation de Conan** :
   Le script vérifie que `Conan` est bien installé avant de poursuivre. Si ce n'est pas le cas, il affiche un message d'erreur et interrompt le processus.

4. **Compilation du projet** :
   - Le script lance `cmake` pour configurer la compilation à partir du fichier `CMakeLists.txt`.
   - Conan est utilisé pour installer les dépendances manquantes.
   - Enfin, `cmake` est utilisé pour compiler le projet avec la configuration `Release`.

#### Exécution de make.sh :
1. **Nettoyage** : Le script commence par nettoyer toute trace de build précédent.
2. **Préparation du build** : Il crée un nouveau dossier `build` et lance les étapes de configuration CMake.
3. **Installation des dépendances Conan** : Conan gère l'installation des bibliothèques externes (SFML, Boost).
4. **Compilation** : `cmake` compile les sources du projet avec les options définies.

---

### Méthode de Compilation

Ces deux scripts fonctionnent en tandem pour assurer une compilation propre et répétable :

1. Exécution du script 'prebuild.sh' :
   ./prebuild.sh
   Cela installe toutes les dépendances nécessaires à la compilation sur le système.

2. Exécution du script 'make.sh' :
   ./make.sh
   Après que l'environnement est configuré avec `prebuild.sh`, `make.sh` nettoie les fichiers de compilation précédents, configure Conan et CMake, puis compile le projet.

Cela permet de rendre la compilation et la gestion des dépendances automatiques, peu importe la distribution ou la configuration du système.