#ifndef NPC_H
#define NPC_H
#include "Entity.h"
#include<string>
#include "GameScene.h"





class GameScene;


class Npc :
    public Entity
{
    protected:
        bool isInteracting;

        int tileWidth;
        int tileHeight;
        int spriteWide;
        int spriteHeight;
        float scale;

        GameScene* gameScene;

        sf::Text npcText;
        sf::RectangleShape TextRect;
        sf::RectangleShape BackgroundRect;
        sf::Font font;
        std::string text;
        sf::Text keyHint;

        sf::Vector2f relatedPos;

        void initVaribles(int tileWidth, int tileHeight, int spriteWide, int spriteHeight, std::string text);
        void InitSpriteRect(sf::Vector2f position);
        void InitSprite(std::string texturePath);
        void InitText();
        void updateAnimation();
        void updateInteracting();
        void updateNpcTextRectUserInput();
        void renderNpcText(sf::RenderTarget& target);
        void updatePosition();
    

        public:
            Npc(int tileWidth, int tileHeight,int spriteWide,int spriteHeight,std::string texturePath, sf::Vector2f position,std::string text);
            ~Npc();
            void update(const float& dt=0);
            void render(sf::RenderTarget& target);
            sf::RectangleShape getSpriteRect();
            void interactingWithCharacter();
            void endInteraction();
            void setGameScene(GameScene* gameScene);

};
#endif 



