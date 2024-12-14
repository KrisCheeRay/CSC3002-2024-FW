
#pragma once
#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

std::vector<sf::Texture> loadTextures(const std::string& folderPath, int frameCount);

class Explosion {
public:
    Explosion(const std::vector<sf::Texture>& textures, sf::Vector2f position, float frameTime = 0.0167f)
        : textures(textures), frameTime(frameTime), currentFrame(4), isFinished(false) {
        sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
        sprite.setPosition(position);
        sprite.setScale(2.0f, 2.0f); // 将精灵的大小调整为原来的2倍
        clock.restart();
    }

    void update() {
        if (clock.getElapsedTime().asSeconds() >= frameTime) {
            if (currentFrame < textures.size()) {
                sprite.setTexture(textures[currentFrame]);
                clock.restart();
                currentFrame++;

            }
            else {
                isFinished = true;
            }
        }
    }

    void render(sf::RenderWindow& window) {
        if (!isFinished) {
            window.draw(sprite);
        }
    }

    bool isFinished;

private:
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;
    sf::Clock clock;
    float frameTime;
    std::size_t currentFrame;
};

#endif // EXPLOSION_H
