#ifndef HP_MP_H
#define HP_MP_H

#include <SFML/Graphics.hpp>

class HP_MP
{
public:
    HP_MP(sf::RenderWindow& window);
    void update(float hpRatio, float mpRatio);
    void render();

    // HP functions
    void reduceHP(float amount);
    void reduceHPOverTime(float amount, float duration);
    void increaseHP(float amount);

    // MP functions
    void reduceMP(float amount);
    void increaseMP(float amount);

    // Pause and Resume functions for continuous effects
    void pauseEffects();
    void resumeEffects();

    // Getters
    float getHPRatio() const;
    float getMPRatio() const;

    // Reset function
    void reset();

    // Update effects function
    void updateEffects();
private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text hpText;
    sf::Text mpText;
    sf::RectangleShape hpBar;
    sf::RectangleShape mpBar;
    float maxBarWidth;

    float currentHPRatio;
    float currentMPRatio;


    bool isReducingHPOverTime;
    float hpReductionAmount;
    float hpReductionDuration;
    sf::Clock hpReductionClock;

    void setupBars();
};

#endif // HP_MP_H





