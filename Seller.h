#ifndef  SELLER_H
#define  SELLER_H
#include "Npc.h"
#include "Charachter.h"
#include <random>
#include <string>
#include "Wand.hpp"
enum class SellerAnimation
{
    IDLE,
    Flipping_Coin,
    Talking,
    OpeningBOX,
    Opening_IDLE,
};
class Seller :
    public Npc
{
    private:
        bool isOpenBox;
        bool isCollisionWithCharacter;
        int IDLEframeNum;
        int Flipping_CoinframeNum;
        int TalkingframeNum;
        int OpeningBOXframeNum;
        
        int cnt;
        
        bool isOpeningBox;

        sf::RenderTarget* Shoptarget;
        
        Charachter * character;

        Wand* wand;

        //shop
        sf::Font font;
        sf::RectangleShape shopWindow;
        std::vector<sf::Texture> itemTextures;
        std::vector<sf::Sprite> itemSprites;
        std::vector<int> itemPrices;
        std::vector<sf::Text> itemPricesText;
        std::vector<sf::Text> itemTips;
        std::vector<std::string> tipStrings;
        sf::RectangleShape descriptionBox;
        sf::RectangleShape selectionBox;
        sf::Text descriptionText;
        int selectedItemIndex;
        std::vector<std::string> itemDescriptions;
        sf::Text keyHint;
        int buyTimes;

        

        SellerAnimation currentAnimation;
        void updateAnimation();
        void switchIdleAnimation();
        void initializeShop();
        void updateShopUserInput();
        void updateBuyingAffect(int index);
        void renderShop();
        void updateInteracting();

    public:
        Seller(int tileWidth, int tileHeight, int spriteWide, int spriteHeight, std::string texturePath, sf::Vector2f position, sf::RenderTarget * Shoptarget);
        ~Seller();
        void startCollision();
        void endCollision();
        void update();
        void render(sf::RenderTarget& target);
        void setCharacter(Charachter* character);
        void setWand(Wand* wand);

};
#endif // !



//"E:\\3002_Project_Game_SFML\\CppGameProject_3002\Resources\Image\NPC\seller\Gipsy spritesheet.png"