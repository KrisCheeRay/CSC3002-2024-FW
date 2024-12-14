#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
enum class Direction
{
       Left,
       Right 
};  

class Entity {
    protected:

        //����ͼ��Ϣ
        sf::RectangleShape spriteRect;
        sf::Sprite sprite;
        sf::Texture spriteTexture;
        sf::IntRect intRect;

        //�˶�����
        float maxSpeed;
        sf::Vector2f velocity;
        float acceleration;
        float deceleration;
        float gravity;


        //clock
        sf::Clock animationClock;

    public:
        virtual void update(const float& dt) = 0;
        virtual void render(sf::RenderTarget & target) = 0;
        virtual ~Entity()= default;
};

#endif 

