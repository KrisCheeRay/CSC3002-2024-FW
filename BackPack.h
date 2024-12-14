#ifndef BACKPACK_H
#define BACKPACK_H

#include <SFML/Graphics.hpp>
#include <vector>

class Backpack
{
public:
    Backpack(sf::RenderWindow& window);
    void handleEvent(sf::Event& event);
    void render();

private:
    sf::RenderWindow& window;
    std::vector<sf::RectangleShape> slots;
    int selectedSlotIndex; // Index of the currently selected slot, -1 if none

    void setupSlots();
    void handleMouseClick(sf::Vector2f mousePos);
};
#endif // BACKPACK_H