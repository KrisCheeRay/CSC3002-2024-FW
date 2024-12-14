#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameOver
{
public:
    GameOver(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, bool& gameRestarted, bool& gameClosed);
    void render();
    void showVictory();
    bool isStoryPageActive() const;
    void setStoryPageActive(bool active);

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Font font2;
    sf::Text gameOverText;
    sf::Text victoryText;
    sf::Text restartButton;
    sf::Text exitButton;
    sf::Text designerText;
    sf::Text storyText;
    sf::Text storyText2;

    sf::Text guideText;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;
    sf::Sprite victorySprite;
    sf::Texture victoryTexture;

    bool isVictory;
    bool isStoryPage;

    void setupUI();
    void setupVictoryUI();
    void setupStoryUI();
    void setupBackground();
};

#endif // GAMEOVER_H