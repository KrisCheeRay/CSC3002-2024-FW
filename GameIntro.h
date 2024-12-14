#ifndef GAMEINTRO_H
#define GAMEINTRO_H

#include <SFML/Graphics.hpp>
#include "vector"

class GameIntro
{
public:

    GameIntro(sf::RenderWindow& window);
    void handleEvent(sf::Event& event, bool& gameStarted);
    void render();
    bool isFinished() const;
    void update();
private:
    enum class Page
    {
        BACKGROUND_INFO,
        GAMEPLAY_INFO
    };

    sf::RenderWindow& window;
    bool finished;
    Page currentPage;


    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Font font2;


    sf::Text introText;
    sf::Text backgroundInfoText;
    sf::Text backgroundInfoText2;

    sf::Text continueText;
    sf::Text startText;
    sf::Text aText, dText, spaceText, escText, enterText, magicBallText, controlText;
    sf::Text sellerNPCText, eText, bText, yText;
    sf::Text deBuffText, deBuff1, deBuff2, deBuff3, deBuff4;


    sf::Sprite aSprite, dSprite,enterSprite, magicBallSprite,
        sellerSprite,npcSprite,
        deBuff1Sprite, deBuff2Sprite, deBuff3Sprite, deBuff4Sprite;



    std::vector<sf::Texture> walkTextures, enterTextures, magicBallTextures;


    sf::Texture sellerTexture, npcTexture,deBuff1Texture, deBuff2Texture, deBuff3Texture, deBuff4Texture;


    int walk,enter, magicBall, seller, npc;



    sf::IntRect intRect1, intRect2;

    sf::Clock animationClock;
};

#endif // GAMEINTRO_H
