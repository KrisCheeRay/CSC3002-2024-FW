#ifndef LEVEL_BG_MANAGER_H
#define LEVEL_BG_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class LevelBGManager {
public:
    LevelBGManager(sf::RenderWindow& window);

    void startLoadingScreen();
    void startProgressBarOnly();
    void update(float deltaTime);
    void render();

    void setStoryTexts(const std::vector<std::string>& texts);
    void showNextStory();
    void clearStoryAndLoading();

    int getCurrentLevel() const;
    bool isLoading() const;
    void onPlayerDeath();

private:
    sf::RenderWindow& window;
    int currentLevel;
    bool loading;
    float loadingProgress;
    bool showProgressOnly;

    sf::Font font;
    sf::Text loadingText;
    sf::RectangleShape loadingBar;

    sf::Text storyTitle;
    sf::Text storyText;
    std::vector<std::string> storyTexts;
    int currentStoryIndex;

    void updateLoading(float deltaTime);
    bool isResetRequired;
};
#endif // LEVEL_BG_MANAGER_H
