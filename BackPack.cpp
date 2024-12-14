#include "Backpack.h"

Backpack::Backpack(sf::RenderWindow& window) : window(window), selectedSlotIndex(-1)
{
    setupSlots();
}

void Backpack::setupSlots()
{
    int numSlots = 10;
    float slotWidth = 60.0f;
    float slotHeight = 60.0f;
    float spacing = 10.0f;
    float startX = (window.getSize().x - (numSlots * (slotWidth + spacing) - spacing)) / 2.0f;
    float startY = window.getSize().y - slotHeight - 20.0f;
    for (int i = 0; i < numSlots; ++i)
    {
        sf::RectangleShape slot;
        slot.setSize(sf::Vector2f(slotWidth, slotHeight));
        slot.setFillColor(sf::Color(128, 128, 128, 150));
        slot.setOutlineThickness(2.0f);
        slot.setOutlineColor(sf::Color::White);
        slot.setPosition(startX + i * (slotWidth + spacing), startY);

        slots.push_back(slot);
    }
}

void Backpack::handleEvent(sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        handleMouseClick(mousePos);
    }
}

void Backpack::handleMouseClick(sf::Vector2f mousePos)
{
    for (size_t i = 0; i < slots.size(); ++i)
    {
        if (slots[i].getGlobalBounds().contains(mousePos))
        {
            if (selectedSlotIndex != -1)
            {
                // Reset the previously selected slot color
                slots[selectedSlotIndex].setFillColor(sf::Color(128, 128, 128, 150));
            }

            // Set the new selected slot color
            selectedSlotIndex = static_cast<int>(i);
            slots[selectedSlotIndex].setFillColor(sf::Color(192, 192, 192, 200)); // Lighter gray with transparency
            break;
        }
    }
}

void Backpack::render()
{
    for (const auto& slot : slots)
    {
        window.draw(slot);
    }
}
