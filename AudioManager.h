#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SFML/Audio.hpp>

class AudioManager {
private:
    sf::Music mainMenuMusic;
    sf::Music gameplayMusic;
    sf::Music introMusic;
    sf::Music gameOverMusic;
    sf::Music victoryMusic;
    sf::Music* currentMusic;
    bool isPaused;

public:
    AudioManager();

    void loadAudio();
    void playMusic(const std::string& musicType);
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();
    void stopBackgroundMusic();
    bool isMusicPaused() const;
};

#endif 