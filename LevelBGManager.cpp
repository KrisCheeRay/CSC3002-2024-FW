//#include "LevelBGManager.h"
//#include <stdexcept>
//#include <iostream>
//
//LevelBGManager::LevelBGManager(sf::RenderWindow& window)
//    : window(window), currentLevel(1), loading(false), loadingProgress(0.f)
//{
//    // Load the font for displaying loading text
//    if (!font.loadFromFile("Resources\\Image\\Font\\font.ttf")) {
//        throw std::runtime_error("Failed to load font");
//    }
//
//    // Set up the loading text properties
//    loadingText.setFont(font);
//    loadingText.setCharacterSize(30);
//    loadingText.setFillColor(sf::Color::White);
//    loadingText.setString("Loading...");
//    loadingText.setPosition(10.f, window.getSize().y - 80.f);
//
//    // Set up the loading bar properties
//    loadingBar.setFillColor(sf::Color::White);
//    loadingBar.setSize(sf::Vector2f(0.f, 20.f)); // Start with width 0
//    loadingBar.setPosition(10.f, window.getSize().y - 40.f);
//
//    // Load the first level background initially
//    loadLevel(currentLevel);
//}
//
//void LevelBGManager::loadLevel(int level) {
//    currentLevel = level;
//
//    // Load background texture based on level
//    std::string fileName = "Resources\\Image\\Background\\Level_" + std::to_string(level) + ".png";
//    if (!backgroundTexture.loadFromFile(fileName)) {
//        throw std::runtime_error("Failed to load background texture: " + fileName);
//    }
//
//    // Debugging output to verify correct texture loading
//    std::cout << "Loaded background texture: " << fileName << std::endl;
//    std::cout << "Texture size: " << backgroundTexture.getSize().x << "x" << backgroundTexture.getSize().y << std::endl;
//
//    // Set up the background sprite and adjust its size to fit the window
//    backgroundSprite.setTexture(backgroundTexture);
//
//    // Calculate and set the correct scaling factor to fill the entire window
//    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
//    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
//    backgroundSprite.setScale(scaleX, scaleY);
//}
//
//void LevelBGManager::startLoadingScreen() {
//    // Set loading state to true and reset progress
//    loading = true;
//    loadingProgress = 0.f;
//}
//
//void LevelBGManager::update(float deltaTime) {
//    if (loading) {
//        updateLoading(deltaTime);
//    }
//}
//
//void LevelBGManager::updateLoading(float deltaTime) {
//    // Simulate loading progress increment
//    loadingProgress += 20.f * deltaTime;
//    if (loadingProgress >= 100.f) {
//        loadingProgress = 100.f;
//        loading = false;
//        loadLevel(currentLevel + 1);
//        std::cout << "Loading complete. Entering level " << currentLevel << std::endl;
//    }
//
//    // Update loading bar to reflect current progress
//    float maxBarWidth = window.getSize().x - 20.f;
//    loadingBar.setSize(sf::Vector2f((loadingProgress / 100.f) * maxBarWidth, 20.f));
//}
//
//void LevelBGManager::render() {
//    // Always render the current level background first
//    window.draw(backgroundSprite);
//
//    if (loading) {
//        // Render the loading screen over the current background
//        window.draw(loadingText);
//        window.draw(loadingBar);
//    }
//}
//
//int LevelBGManager::getCurrentLevel() const {
//    return currentLevel;
//}
//
//bool LevelBGManager::isLoading() const {
//    return loading;
//}
//
//
//
//
//
#include "LevelBGManager.h"
#include <stdexcept>
#include <iostream>



#include "LevelBGManager.h"
#include <stdexcept>
#include <iostream>

LevelBGManager::LevelBGManager(sf::RenderWindow& window)
    : window(window), currentLevel(1), loading(false), loadingProgress(0.f), showProgressOnly(false), currentStoryIndex(0), isResetRequired(false)
{

    if (!font.loadFromFile("Resources\\Image\\Font\\28177148754.ttf")) {
        throw std::runtime_error("Failed to load font");
    }


    loadingText.setFont(font);
    loadingText.setCharacterSize(30);
    loadingText.setFillColor(sf::Color::White);
    loadingText.setString("Loading...");
    loadingText.setPosition(10.f, window.getSize().y - 80.f);


    loadingBar.setFillColor(sf::Color::White);
    loadingBar.setSize(sf::Vector2f(0.f, 20.f));
    loadingBar.setPosition(10.f, window.getSize().y - 40.f);


    storyTitle.setFont(font);
    storyTitle.setFillColor(sf::Color(222, 211, 183));
    storyTitle.setOutlineColor(sf::Color::Black);
    storyTitle.setOutlineThickness(4.f);
    storyTitle.setCharacterSize(50);
    storyTitle.setString("THE ONE");
    storyTitle.setPosition(window.getSize().x / 2.f, 50.f);
    storyTitle.setOrigin(storyTitle.getLocalBounds().width / 2.f, storyTitle.getLocalBounds().height / 2.f);


    storyText.setFont(font);
    storyText.setCharacterSize(40);
    storyText.setFillColor(sf::Color(222, 211, 183));
    storyText.setOutlineColor(sf::Color::Black);
    storyText.setOutlineThickness(6.f);
    storyText.setString("");
    storyText.setPosition(window.getSize().x / 2.f, 400.f);


    storyTexts = {
        "                                        Vainamoinen\n\n                                           Level 2\n\n\n\n\"All ye who enter through this gate, Abandon hope, resign to fate.\"",
         "                Vainamoinen\n\n                  Boss Level\n\n\n\n\"Art is an explosion, fierce and bright, \nA fleeting spark that shatters the night.\"",
         "                                        Ilmarinen\n\n                                           Level 1\n\n\n\n\"A hero must not flee the fray, For courage lights the darkest way\"",
         "                                Ilmarinen\n\n                                   Level 2\n\n\n\n\"Years hence, the hero shall recall, That fateful eve, \nthe emerald scroll's call.\"",
         "                   Ilmarinenn\n\n                   Boss Level\n\n\n\n\"For every golden star, a mystery lies, \nA riddle cloaked beneath the skies.\n\nAnd for each silver moon that gleams, \nA shadow empties all our dreams.\"",
         "               Lemminkainen\n\n                   Level 1\n\n\n\n\"No matter where the truth may rise, \nNo matter what its form or guise,\n\nOnly you, the teacher, show the way, \nThe keeper of truth's light each day.\"",
         "                            Lemminkainen\n\n                               Level 2\n\n\n\n\"All elements of the Sky's Egg, Shall one day return,\n to the source they beg.\"",
         "                  Lemminkainen\n\n                    Boss Level\n\n\n\n\"The first of singers and of mages, \nWielding song through ancient ages.\n\nThey are the flames that sing of life, \nA hymn to quell the world's great strife.\""
    };
}

void LevelBGManager::startLoadingScreen() {
    if (isResetRequired) {
        currentStoryIndex = 0;
        isResetRequired = false;
    }

    loading = true;
    loadingProgress = 0.f;
    showProgressOnly = false;

    if (currentStoryIndex < static_cast<int>(storyTexts.size())) {
        storyText.setString(storyTexts[currentStoryIndex]);
    }
}

void LevelBGManager::startProgressBarOnly() {
    loading = true;
    loadingProgress = 0.f;
    showProgressOnly = true;

    if (currentStoryIndex < static_cast<int>(storyTexts.size())) {
        storyText.setString(storyTexts[currentStoryIndex]);
    }
}

void LevelBGManager::update(float deltaTime) {
    if (loading) {
        updateLoading(deltaTime);
    }
}

void LevelBGManager::updateLoading(float deltaTime) {
    loadingProgress += 20.f * deltaTime;
    if (loadingProgress >= 100.f) {
        loadingProgress = 100.f;
        loading = false;
        clearStoryAndLoading();

        if (currentStoryIndex < static_cast<int>(storyTexts.size()) - 1) {
            currentStoryIndex++;
        }
    }

    float maxBarWidth = window.getSize().x - 20.f;
    loadingBar.setSize(sf::Vector2f((loadingProgress / 100.f) * maxBarWidth, 20.f));
}

void LevelBGManager::render() {
    if (loading) {
        window.draw(loadingText);
        window.draw(loadingBar);
    }

    if (!storyText.getString().isEmpty()) {
        window.draw(storyTitle);

        sf::FloatRect textRect = storyText.getLocalBounds();
        storyText.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        storyText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
        window.draw(storyText);
    }
}

void LevelBGManager::setStoryTexts(const std::vector<std::string>& texts) {
    storyTexts = texts;
    currentStoryIndex = 0;
}

void LevelBGManager::showNextStory() {
    if (currentStoryIndex < static_cast<int>(storyTexts.size())) {
        storyText.setString(storyTexts[currentStoryIndex]);
    }
}

void LevelBGManager::clearStoryAndLoading() {
    storyText.setString("");
    loading = false;
    loadingProgress = 0.f;
}

int LevelBGManager::getCurrentLevel() const {
    return currentLevel;
}

bool LevelBGManager::isLoading() const {
    return loading;
}

void LevelBGManager::onPlayerDeath() {
    isResetRequired = true;
}