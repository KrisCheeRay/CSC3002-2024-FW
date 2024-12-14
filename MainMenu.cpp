#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& window) : window(window)
{
    if (!font.loadFromFile("Resources\\Image\\Font\\font.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    setupButtons();
    setupPauseOverlay();
    setupBackground();
}

void MainMenu::setupButtons()
{
    //GameName
    GameName.setFont(font);
    GameName.setString("THE ONE");
    GameName.setCharacterSize(90);
    GameName.setOutlineThickness(4.0f);
    GameName.setOutlineColor(sf::Color(56, 39, 30));
    GameName.setFillColor(sf::Color(205, 192, 176));
    GameName.setPosition(window.getSize().x / 2 - startButton.getGlobalBounds().width / 2-190, window.getSize().y / 3-150 );

    Member.setFont(font);
    Member.setString("  @RichardM\n   @Dylan\n@Zhang Zhiheng\n   @Bruce\n @Liu YanNan");
    Member.setCharacterSize(60);
    Member.setOutlineThickness(4.0f);
    Member.setOutlineColor(sf::Color(56, 39, 30));
    Member.setFillColor(sf::Color(205, 192, 176));
    Member.setPosition(window.getSize().x / 2 - startButton.getGlobalBounds().width / 2 - 240, window.getSize().y / 2 + 130);


    // Start Button
    startButton.setFont(font);
    startButton.setString("Start");
    startButton.setCharacterSize(50);
    startButton.setOutlineThickness(1.0f);
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition(window.getSize().x / 2 - startButton.getGlobalBounds().width / 2, window.getSize().y / 3+50);

    // Exit Button
    exitButton.setFont(font);
    exitButton.setString("Exit");
    exitButton.setCharacterSize(50);
    exitButton.setOutlineThickness(1.0f);
    exitButton.setFillColor(sf::Color::White);
    exitButton.setPosition(window.getSize().x / 2 - exitButton.getGlobalBounds().width / 2, window.getSize().y / 2+50);

    // Back Button (Pause Menu)
    backButton.setFont(font);
    backButton.setString("Back");
    backButton.setCharacterSize(50);
    backButton.setOutlineThickness(1.0f);
    backButton.setFillColor(sf::Color::White);
    backButton.setPosition(window.getSize().x / 2 - backButton.getGlobalBounds().width / 2, window.getSize().y / 2 - 70);

    // Pause Exit Button (Pause Menu)
    pauseExitButton.setFont(font);
    pauseExitButton.setString("Exit");
    pauseExitButton.setCharacterSize(50);
    pauseExitButton.setOutlineThickness(1.0f);
    pauseExitButton.setFillColor(sf::Color::White);
    pauseExitButton.setPosition(window.getSize().x / 2 - pauseExitButton.getGlobalBounds().width / 2, window.getSize().y / 2 + 20);
}

void MainMenu::setupPauseOverlay()
{
    float maxWidth = std::max(backButton.getGlobalBounds().width, pauseExitButton.getGlobalBounds().width) + 50.f;
    pauseOverlay.setSize(sf::Vector2f(maxWidth, window.getSize().y));
    pauseOverlay.setFillColor(sf::Color(255, 255, 255, 150)); // Semi-transparent white
    pauseOverlay.setPosition(window.getSize().x / 2 - pauseOverlay.getSize().x / 2, 0);
}

void MainMenu::setupBackground()
{
    if (!mainMenuBackgroundTexture.loadFromFile("Resources\\Image\\Background\\main_menu_background.png"))
    {
        throw std::runtime_error("Failed to load main menu background texture");
    }
    mainMenuBackgroundSprite.setTexture(mainMenuBackgroundTexture);
    mainMenuBackgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / mainMenuBackgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / mainMenuBackgroundTexture.getSize().y
    );
}

void MainMenu::handleEvent(sf::Event& event, bool& gameStarted, bool& gamePaused)
{
    if (event.type == sf::Event::Closed)
    {
        window.close();
    }

    if (event.type == sf::Event::MouseMoved)
    {
        handleMouseMovement(event, gameStarted, gamePaused);
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        handleMouseClick(event, gameStarted, gamePaused);
    }

    if (gameStarted && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        std::cout << "escape" <<std::endl;
        gamePaused = !gamePaused;
    }
}

bool MainMenu::isBackButtonClicked(const sf::Vector2f& mousePos) const
{
    return backButton.getGlobalBounds().contains(mousePos);
}

void MainMenu::handleMouseMovement(sf::Event& event, bool gameStarted, bool gamePaused)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (!gameStarted)
    {
        // Start Button
        if (startButton.getGlobalBounds().contains(mousePos))
        {
            startButton.setFillColor(sf::Color::Yellow);
        }
        else
        {
            startButton.setFillColor(sf::Color::White);
        }

        // Exit Button
        if (exitButton.getGlobalBounds().contains(mousePos))
        {
            exitButton.setFillColor(sf::Color::Yellow);
        }
        else
        {
            exitButton.setFillColor(sf::Color::White);
        }
    }
    else if (gamePaused)
    {
        // Back Button
        if (backButton.getGlobalBounds().contains(mousePos))
        {
            backButton.setFillColor(sf::Color::Yellow);
        }
        else
        {
            backButton.setFillColor(sf::Color::White);
        }

        // Pause Exit Button
        if (pauseExitButton.getGlobalBounds().contains(mousePos))
        {
            pauseExitButton.setFillColor(sf::Color::Yellow);
        }
        else
        {
            pauseExitButton.setFillColor(sf::Color::White);
        }
    }
}

void MainMenu::handleMouseClick(sf::Event& event, bool& gameStarted, bool& gamePaused)
{
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (!gameStarted)
    {
        // Check if Start button is pressed
        if (startButton.getGlobalBounds().contains(mousePos))
        {
            gameStarted = true;
        }

        // Check if Exit button is pressed
        if (exitButton.getGlobalBounds().contains(mousePos))
        {
            window.close();
        }
    }
    else if (gamePaused)
    {
        // Check if Back button is pressed
        if (backButton.getGlobalBounds().contains(mousePos))
        {
            gamePaused = false;
        }

        // Check if Pause Exit button is pressed
        if (pauseExitButton.getGlobalBounds().contains(mousePos))
        {
            window.close();
        }
    }
}

void MainMenu::render(bool gameStarted, bool gamePaused, bool renderHPMP)
{
    if (!gameStarted && !gamePaused)
    {
        window.draw(mainMenuBackgroundSprite); // Draw the main menu background
        window.draw(GameName);
        window.draw(startButton);
        window.draw(exitButton);
        window.draw(Member);
    }
    else if (gamePaused)
    {
        window.draw(pauseOverlay);  // Draw the semi-transparent overlay on top
        window.draw(backButton);
        window.draw(pauseExitButton);
    }
}
