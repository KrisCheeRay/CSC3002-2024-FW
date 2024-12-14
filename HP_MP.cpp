#include "HP_MP.h"
#include <iostream>

HP_MP::HP_MP(sf::RenderWindow& window) : window(window), currentHPRatio(1.0f), currentMPRatio(1.0f), isReducingHPOverTime(false)
{
    setupBars();
}

void HP_MP::setupBars()
{
    maxBarWidth = window.getSize().x * 0.2f;

    hpBar.setSize(sf::Vector2f(maxBarWidth, 20));
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setOutlineColor(sf::Color::Black);
    hpBar.setOutlineThickness(4);
    hpBar.setPosition(window.getSize().x - maxBarWidth - 20, 20);

    mpBar.setSize(sf::Vector2f(maxBarWidth, 20));
    mpBar.setFillColor(sf::Color::Blue);
    mpBar.setOutlineColor(sf::Color::Black);
    mpBar.setOutlineThickness(4);
    mpBar.setPosition(window.getSize().x - maxBarWidth - 20, 50);

    if (!font.loadFromFile("Resources\\Image\\Font\\font.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }

    hpText.setFont(font);
    hpText.setString("HP");
    hpText.setCharacterSize(20);
    hpText.setOutlineThickness(2);
    hpText.setFillColor(sf::Color::Red);

    hpText.setPosition(hpBar.getPosition().x - 40, hpBar.getPosition().y);

    mpText.setFont(font);
    mpText.setString("MP");
    mpText.setCharacterSize(20);
    mpText.setOutlineThickness(2);
    mpText.setFillColor(sf::Color::Blue);
    mpText.setPosition(mpBar.getPosition().x - 40, mpBar.getPosition().y);
}

void HP_MP::update(float hpRatio, float mpRatio)
{
    currentHPRatio = hpRatio;
    currentMPRatio = mpRatio;

    hpBar.setSize(sf::Vector2f(maxBarWidth * currentHPRatio, 20));
    mpBar.setSize(sf::Vector2f(maxBarWidth * currentMPRatio, 20));
}

void HP_MP::render()
{
    window.draw(hpText);
    window.draw(hpBar);
    window.draw(mpText);
    window.draw(mpBar);
}

void HP_MP::reduceHP(float amount)
{
    std::cout << "Reducing HP by " << amount << std::endl;

    currentHPRatio -= amount;
    if (currentHPRatio < 0.0f) currentHPRatio = 0.0f;
}

void HP_MP::reduceHPOverTime(float amount, float duration)
{
    // Start reducing HP over time
    isReducingHPOverTime = true;
    hpReductionAmount = amount;
    hpReductionDuration = duration;
    hpReductionClock.restart();
    std::cout << "Started HP reduction over time: " << amount << " for " << duration << " seconds." << std::endl;
}

void HP_MP::increaseHP(float amount)
{
    std::cout << "Increasing HP by " << amount << std::endl;
    currentHPRatio += amount;
    if (currentHPRatio > 1.0f) currentHPRatio = 1.0f;
}

void HP_MP::reduceMP(float amount)
{
    currentMPRatio -= amount;
    if (currentMPRatio < 0.0f) currentMPRatio = 0.0f;
}

void HP_MP::increaseMP(float amount)
{
    currentMPRatio += amount;
    if (currentMPRatio > 1.0f) currentMPRatio = 1.0f;
}

void HP_MP::pauseEffects()
{
    isReducingHPOverTime = false;
}

void HP_MP::resumeEffects()
{
    if (hpReductionClock.getElapsedTime().asSeconds() < hpReductionDuration)
    {
        isReducingHPOverTime = true;
    }
}

void HP_MP::reset()
{
    currentHPRatio = 1.0f;
    currentMPRatio = 1.0f;
}

void HP_MP::updateEffects()
{
    if (isReducingHPOverTime)
    {
        float elapsed = hpReductionClock.getElapsedTime().asSeconds();
        if (elapsed < hpReductionDuration)
        {
            // Calculate reduction rate per frame
            float hpReductionRate = hpReductionAmount / hpReductionDuration;
            reduceHP(hpReductionRate * 0.016f); // Assuming 60 FPS, ~16ms per frame
        }
        else
        {
            isReducingHPOverTime = false; // Stop the effect after 2 seconds
            std::cout << "HP reduction over time ended." << std::endl;
        }
    }
}

float HP_MP::getHPRatio() const
{
    return currentHPRatio;
}

float HP_MP::getMPRatio() const
{
    return currentMPRatio;
}
