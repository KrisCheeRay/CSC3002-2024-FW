#include "AudioManager.h"
#include <stdexcept>

AudioManager::AudioManager() : isPaused(false), currentMusic(nullptr) {
    loadAudio();
}

void AudioManager::loadAudio() {
    if (!mainMenuMusic.openFromFile("Resources\\Audio\\a_hisa - Cold Mist.ogg")) {
        throw std::runtime_error("Failed to load main menu music");
    }
    mainMenuMusic.setLoop(true);
    mainMenuMusic.setVolume(50);

    if (!gameplayMusic.openFromFile("Resources\\Audio\\Evan Call - Zoltraak.ogg")) {
        throw std::runtime_error("Failed to load gameplay music");
    }
    gameplayMusic.setLoop(true);
    gameplayMusic.setVolume(50);

    if (!introMusic.openFromFile("Resources\\Audio\\background_music.ogg")) {
        throw std::runtime_error("Failed to load intro music");
    }
    introMusic.setLoop(true);
    introMusic.setVolume(50);

    if (!gameOverMusic.openFromFile("Resources\\Audio\\Harris Cole - Game over!.ogg")) {
        throw std::runtime_error("Failed to load game over music");
    }
    gameOverMusic.setLoop(true);
    gameOverMusic.setVolume(50);

    if (!victoryMusic.openFromFile("Resources\\Audio\\Phoenix.ogg")) {
        throw std::runtime_error("Failed to load victory music");
    }
    victoryMusic.setLoop(true);
    victoryMusic.setVolume(50);
}

void AudioManager::playMusic(const std::string& musicType) {
    stopBackgroundMusic();

    if (musicType == "mainMenu") {
        currentMusic = &mainMenuMusic;
    }
    else if (musicType == "gameplay") {
        currentMusic = &gameplayMusic;
    }
    else if (musicType == "intro") {
        currentMusic = &introMusic;
    }
    else if (musicType == "gameOver") {
        currentMusic = &gameOverMusic;
    }
    else if (musicType == "victory") {
        currentMusic = &victoryMusic;
    }
    else {
        currentMusic = nullptr;
    }

    if (currentMusic) {
        currentMusic->play();
        isPaused = false;
    }
}

void AudioManager::pauseBackgroundMusic() {
    if (currentMusic && currentMusic->getStatus() == sf::Music::Playing) {
        currentMusic->pause();
        isPaused = true;
    }
}

void AudioManager::resumeBackgroundMusic() {
    if (currentMusic && isPaused && currentMusic->getStatus() == sf::Music::Paused) {
        currentMusic->play();
        isPaused = false;
    }
}

void AudioManager::stopBackgroundMusic() {
    if (currentMusic && currentMusic->getStatus() != sf::Music::Stopped) {
        currentMusic->stop();
    }
    currentMusic = nullptr;
    isPaused = false;
}

bool AudioManager::isMusicPaused() const {
    return isPaused;
}







