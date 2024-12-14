#include "Coins.h"
#include <stdexcept>
#include <iostream>
#include <SFML/Graphics.hpp>

Coins::Coins(sf::RenderWindow& window)
    : window(window), coins(0), currentFrame(0), frameTimeAccumulator(0.f), frameInterval(0.1f) // frameInterval is 0.1 seconds
{
    // Load the font for displaying coin count
    if (!font.loadFromFile("Resources\\Image\\Font\\font.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    // Set up the coins text
    coinsText.setFont(font);
    coinsText.setOutlineThickness(2.0f);
    coinsText.setCharacterSize(24);
    coinsText.setFillColor(sf::Color::Yellow);
    coinsText.setPosition(1420.f, 100.f);

    updateText();

    // Load all the coin textures for the animation
    for (int i = 1; i <= 10; ++i) {
        sf::Texture texture;
        std::string fileName = "Resources\\Image\\Coins\\Gold_" + std::to_string(i) + ".png";
        if (!texture.loadFromFile(fileName)) {
            throw std::runtime_error("Failed to load coin texture: " + fileName);
        }
        coinTextures.push_back(texture);
    }

    // Set up the initial coin sprite with the first frame
    if (!coinTextures.empty()) {
        coinSprite.setTexture(coinTextures[0]);
        coinSprite.setScale(0.05f, 0.05f);
    }
    coinSprite.setPosition(1350.f, 80.f);
}

void Coins::render() {
    // Draw the current frame of the coin sprite and the coin count text
    window.draw(coinSprite);
    window.draw(coinsText);
}

void Coins::addCoins(int amount) {
    if (amount > 0) {
        coins += amount;
        updateText();
    }
}

bool Coins::spendCoins(int amount) {
    if (amount > 0 && coins >= amount) {
        coins -= amount;
        updateText();
        return true;
    }
    return false;
}

int Coins::getCoins() const {
    return coins;
}

bool Coins::canAfford(int amount) const {
    return coins >= amount;
}

void Coins::updateText() {
    // Update the text to display the current number of coins
    coinsText.setString("Coins: " + std::to_string(coins));
}

void Coins::updateAnimation(float deltaTime) {
    // Update the frame time accumulator
    frameTimeAccumulator += deltaTime;

    // If enough time has passed, move to the next frame
    if (frameTimeAccumulator >= frameInterval) {
        frameTimeAccumulator -= frameInterval;
        currentFrame = (currentFrame + 1) % coinTextures.size();

        // Update the sprite to use the new frame
        if (!coinTextures.empty()) {
            coinSprite.setTexture(coinTextures[currentFrame]);
            coinSprite.setScale(0.1f, 0.1f);
        }
    }
}

void Coins::reset() {
    coins = 0;
    updateText();
}