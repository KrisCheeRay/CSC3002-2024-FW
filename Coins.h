#ifndef COINS_H
#define COINS_H

#include <SFML/Graphics.hpp>
#include <vector>

class Coins {
public:

    Coins(sf::RenderWindow& window);
    void render();
    void addCoins(int amount);
    bool spendCoins(int amount);
    int getCoins() const;
    bool canAfford(int amount) const;
    void updateAnimation(float deltaTime);
    void reset();

private:

    sf::RenderWindow& window;
    int coins;
    sf::Font font;
    sf::Text coinsText;
    std::vector<sf::Texture> coinTextures;
    sf::Sprite coinSprite;
    int currentFrame;
    float frameTimeAccumulator;
    float frameInterval;
    void updateText();
};

#endif // COINS_H





