#pragma once
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <iostream>
#include <vector>

class SoundSystem {
public:
    void loadSounds() {
        if (!missileBuffer.loadFromFile("assets/sounds/missile_shoot.wav")) {
            std::cerr << "Erreur lors du chargement de missile_shoot.wav" << std::endl;
        }
        buffers["missile_shoot"] = missileBuffer;

        if (!explosionBuffer.loadFromFile("assets/sounds/explosion.wav")) {
            std::cerr << "Erreur lors du chargement de explosion.wav" << std::endl;
        }
        buffers["explosion"] = explosionBuffer;

        // Charger et jouer la musique de fond
        if (!backgroundMusic.openFromFile("assets/sounds/background_music.ogg")) {
            std::cerr << "Erreur lors du chargement de background_music.ogg" << std::endl;
        } else {
            backgroundMusic.setLoop(true);  // Boucle en continu
            backgroundMusic.play();
        }
    }

    void playSound(const std::string& soundName) {
        if (buffers.find(soundName) != buffers.end()) {
            sf::Sound sound;
            sound.setBuffer(buffers[soundName]);
            sound.play();
            activeSounds.push_back(sound);  // Garder une référence pour les sons actifs
        } else {
            std::cerr << "Son introuvable : " << soundName << std::endl;
        }
    }

    void update() {
        activeSounds.erase(std::remove_if(activeSounds.begin(), activeSounds.end(),
            [](const sf::Sound& sound) {
		return sound.getStatus() == sf::Sound::Status::Stopped; 
            }), activeSounds.end());
    }

private:
    std::map<std::string, sf::SoundBuffer> buffers;
    std::vector<sf::Sound> activeSounds;  // Liste des sons actuellement en cours de lecture

    sf::SoundBuffer missileBuffer;
    sf::SoundBuffer explosionBuffer;
    sf::Music backgroundMusic;
};
