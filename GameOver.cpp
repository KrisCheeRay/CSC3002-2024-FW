#include "GameOver.h"
#include <stdexcept>
#include   <iostream>
using namespace std;

GameOver::GameOver(sf::RenderWindow& window)
    : window(window), isVictory(false), isStoryPage(true)
{
    if (!font.loadFromFile("Resources\\Image\\Font\\font.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    setupBackground();
    setupUI();
    setupVictoryUI();
    setupStoryUI();
}

void GameOver::setupUI()
{
    gameOverText.setFont(font);
    gameOverText.setString("Wasted!");
    gameOverText.setOutlineThickness(2.0f);
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(window.getSize().x / 2 - gameOverText.getGlobalBounds().width / 2, window.getSize().y / 4);

    restartButton.setFont(font);
    restartButton.setString("Restart");
    restartButton.setCharacterSize(40);
    restartButton.setOutlineThickness(1.0f);
    restartButton.setFillColor(sf::Color::White);
    restartButton.setPosition(window.getSize().x / 2 - restartButton.getGlobalBounds().width / 2, window.getSize().y / 2 - 100);

    exitButton.setFont(font);
    exitButton.setString("Exit");
    exitButton.setOutlineThickness(1.0f);
    exitButton.setCharacterSize(40);
    exitButton.setFillColor(sf::Color::White);
    exitButton.setPosition(window.getSize().x / 2 - exitButton.getGlobalBounds().width / 2, window.getSize().y / 2 + 100);
}

void GameOver::setupBackground()
{
    if (!backgroundTexture.loadFromFile("Resources\\Image\\Background\\game_over_background.png"))
    {
        throw std::runtime_error("Failed to load game over background texture");
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );
}

void GameOver::setupVictoryUI()
{
    if (!victoryTexture.loadFromFile("Resources\\Image\\Background\\Victory.png"))
    {
        throw std::runtime_error("Failed to load victory background texture");
    }
    victorySprite.setTexture(victoryTexture);
    victorySprite.setScale(
        static_cast<float>(window.getSize().x) / victoryTexture.getSize().x,
        static_cast<float>(window.getSize().y) / victoryTexture.getSize().y
    );

    victoryText.setFont(font);
    victoryText.setString("Victory!!!");
    victoryText.setOutlineThickness(2.0f);
    victoryText.setCharacterSize(50);
    victoryText.setFillColor(sf::Color::Red);
    victoryText.setPosition(
        window.getSize().x / 2 - victoryText.getGlobalBounds().width / 2,
        window.getSize().y / 4
    );

    designerText.setFont(font);
    designerText.setString("Designers: CR  MYT  ZZH  LYN  XQL");
    designerText.setOutlineThickness(2.0f);
    designerText.setCharacterSize(40);
    designerText.setFillColor(sf::Color::White);
    designerText.setPosition(
        window.getSize().x / 2 - designerText.getGlobalBounds().width / 2,
        window.getSize().y - 100
    );
}

void GameOver::setupStoryUI()

{

    if (!font2.loadFromFile("Resources\\Image\\Font\\28177148754.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    storyText.setFont(font2);
    storyText.setString("The winds had whispered the hero¡¯s name, \nAnd the mountains had sung of their trials.\nFrom the first spark of destiny, \nForged in blood and flame, \nTo the final clash that shook the heavens, \nThe hero¡¯s path had been a tapestry\nWoven by the hands of the gods themselves.\n\nThe journey had not been one of mere conquest, \nBut of transformation¡ª\nOf understanding the very heart of the world, \nAnd of shaping the soul that carried it.\n\nV?in?m?inen had taught the hero to listen, \nTo the world¡¯s silent music, \nTo hear the song of nature, of magic, \nAnd of technology, each note playing\nIn harmony and discord.\n\nIlmarinen had forged the path of creation, \nShowing that true mastery\nWas not in finding, but in building\nWith one¡¯s own hands, shaping destiny\nWith every stroke of the hammer.\n\nAnd Lemmink?inen had reminded the hero\nOf their strength, their fire, \nUrging them to embrace the storm and the fight, \nFor it was in the battle that a hero was truly made.\n\nNow, at the final crossroads, the hero stood\nBefore the seed of THE ONE¡ª\nThe root of all things, the spark of creation itself.\nThe world before them was not just land and sky, \nNor time and space.It was a canvas, \nVast and unyielding, waiting\nTo be painted with the hero¡¯s will.\n\nThey had walked through the fire of trials, ");
    storyText.setCharacterSize(20);
    storyText.setFillColor(sf::Color(205, 192, 176));
    storyText.setOutlineThickness(2.f);
    storyText.setPosition(window.getSize().x / 4 - storyText.getGlobalBounds().width / 2, 30);

    storyText2.setFont(font2);
    storyText2.setString("Learned from the voices of those who had come before,\nAnd now they knew what must be done.\nThe seed was not to be grasped with the hands,\nBut with the heart¡ªits truth, its light,\nLay not in finding, but in becoming.\nThe hero was no longer the seeker, but the creator.\n\nAnd so, with quiet resolve, they knelt\nTo plant the seed of THE ONE,\nNot in soil, but in the depths of their soul.\nFrom this seed, a new world would sprout¡ª\nOne of balance, of wisdom, of strength.\nThe elements of nature would bow before it,\nMagic would bend to its will,\nAnd the tools of technology would forge its future.\n\nThe hero¡¯s name would echo in the hearts\nOf those who came after,\nTheir story immortalized not in the words\nOf the gods, but in the very fabric\nOf the world itself.\n\nFor the world is never truly complete\nUntil it is shaped by the hands\nOf those bold enough to wield it.\n\nAnd as the hero stood in the shadow\nOf the rising dawn, they understood:\nThe true power was not in the victory,\nBut in the journey itself.\nThe legacy of THE ONE would never fade,\nFor it was written in the stars, in the earth,\nAnd in the hearts of those who dared to dream.\n\nThe song of the world played on, ever changing,\nEver true¡ªechoing through the ages,\nAs the hero¡¯s story became the story of all.");
    storyText2.setFillColor(sf::Color(205, 192, 176));
    storyText2.setOutlineThickness(2.f);
    storyText2.setPosition(window.getSize().x / 4 - storyText2.getGlobalBounds().width / 2 + 800, 30);
    storyText2.setCharacterSize(20);

    guideText.setFont(font);
    guideText.setString("Press    any    key    \nor    click    to     continue...");
    guideText.setCharacterSize(20);
    guideText.setFillColor(sf::Color::Red);
    guideText.setOutlineThickness(2.0f);
    guideText.setPosition(
        window.getSize().x / 2 - guideText.getGlobalBounds().width / 2+620,
        600);
}

void GameOver::showVictory()
{
    isVictory = true;
    isStoryPage = true;
}

void GameOver::handleEvent(sf::Event& event, bool& gameRestarted, bool& gameClosed)
{
    if (isStoryPage)
    {
        //std::cout << "Handling Story Page Event. Event Type: " << event.type << std::endl;
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
        {
            isStoryPage = false;
            std::cout << "Story Page Exited on KeyPress or Click." << std::endl;
        }
        return;
    }

    if (event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (restartButton.getGlobalBounds().contains(mousePos))
        {
            restartButton.setFillColor(sf::Color::Yellow);
        }
        else
        {
            restartButton.setFillColor(sf::Color::White);
        }

        if (exitButton.getGlobalBounds().contains(mousePos))
        {
            exitButton.setFillColor(sf::Color::Yellow);
        }
        else
        {
            exitButton.setFillColor(sf::Color::White);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (restartButton.getGlobalBounds().contains(mousePos))
        {
            gameRestarted = true;
        }

        if (exitButton.getGlobalBounds().contains(mousePos))
        {
            gameClosed = true;
        }
    }
}

void GameOver::render()
{
    if (isVictory&&isStoryPage) {
        window.draw(victorySprite);
        window.draw(guideText);

        window.draw(storyText);
        window.draw(storyText2);
    }
    else if (isVictory) {
        window.draw(victorySprite);
        window.draw(victoryText);
        window.draw(exitButton);
        window.draw(designerText);
    }
    else {
        window.draw(backgroundSprite);
        window.draw(gameOverText);
        window.draw(restartButton);
        window.draw(exitButton);
    }
}

bool GameOver::isStoryPageActive() const
{
    return isStoryPage;
}

void GameOver::setStoryPageActive(bool active)
{
    isStoryPage = active;
}
