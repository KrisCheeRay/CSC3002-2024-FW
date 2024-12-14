#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>

class MainMenu {
public:
    MainMenu(sf::RenderWindow& window);

    void handleEvent(sf::Event& event, bool& gameStarted, bool& gamePaused);
    bool isBackButtonClicked(const sf::Vector2f& mousePos) const;
    void render(bool gameStarted, bool gamePaused, bool renderHPMP = false);

private:
    sf::RenderWindow& window;

    sf::Font font;

    sf::Text startButton;
    sf::Text exitButton;
    sf::Text backButton;
    sf::Text pauseExitButton;
    sf::Text Member;
    sf::Text GameName;

    sf::RectangleShape pauseOverlay;

    sf::Texture mainMenuBackgroundTexture;
    sf::Sprite mainMenuBackgroundSprite;

    void setupButtons();
    void setupPauseOverlay();
    void setupBackground();
    void handleMouseMovement(sf::Event& event, bool gameStarted, bool gamePaused);
    void handleMouseClick(sf::Event& event, bool& gameStarted, bool& gamePaused);
};

#endif // MAIN_MENU_H


