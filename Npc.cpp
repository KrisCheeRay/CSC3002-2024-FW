#include "Npc.h"
#include <iostream>

void Npc::initVaribles(int spriteWide, int spriteHeight, int tileWidth,int tileHeight,std::string text)
{
	gravity = 9.8f;
	
	isInteracting = false;

	this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    this->spriteWide = spriteWide;
    this->spriteHeight = spriteHeight;

	this->text = text;
	scale = float(spriteWide) / float(tileWidth);

}

void Npc::InitSpriteRect(sf::Vector2f position)
{
	relatedPos= position;
	spriteRect.setSize(
		sf::Vector2f(
			static_cast<float>(spriteWide),
			static_cast<float>(spriteHeight)
		)
	);

	spriteRect.setFillColor(sf::Color::Transparent);
	spriteRect.setOutlineThickness(1.f);
	spriteRect.setOutlineColor(sf::Color::Red);
	spriteRect.setOrigin(spriteRect.getGlobalBounds().width / 2.f, spriteRect.getGlobalBounds().height / 2.f);
	spriteRect.setPosition(position);
}

void Npc::InitSprite(std::string texturePath)
{
	if (!spriteTexture.loadFromFile(texturePath)) {
		throw("ERROR::NPC::FAILED TO LOAD TEXTURE");
	}
	intRect = sf::IntRect(0, 0, tileWidth, tileHeight);
	sprite.setTextureRect(intRect);
	sprite.setTexture(spriteTexture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
	sprite.setPosition(spriteRect.getPosition());
	sprite.setScale(scale, scale);
}

void Npc::InitText()
{
	BackgroundRect.setSize(sf::Vector2f(400, 600));
	BackgroundRect.setPosition(sf::Vector2f(100, 20));
	BackgroundRect.setFillColor(sf::Color(56, 39, 30, 200));
	BackgroundRect.setOutlineThickness(4.0f);
	BackgroundRect.setOutlineColor(sf::Color::Black);

	TextRect.setSize(sf::Vector2f(380, 580));
	TextRect.setPosition(110, 30);
	TextRect.setFillColor(sf::Color(128, 107, 80, 230));
	TextRect.setOutlineThickness(2.0f);
	TextRect.setOutlineColor(sf::Color::Black);



	if (!font.loadFromFile("Resources\\Image\\Font\\28177148754.ttf")) {
		throw("ERROR::NPC::FAILED TO LOAD FONT");
	}
	npcText.setCharacterSize(14);
    npcText.setFont(font);
    npcText.setFillColor(sf::Color(222, 211, 183));
	npcText.setOutlineThickness(1);
    npcText.setOutlineColor(sf::Color::Black);
    npcText.setString(text);
    npcText.setPosition(TextRect.getPosition().x + 10, TextRect.getPosition().y + 10);



	keyHint.setFont(font);
	keyHint.setString("Press 'B' to exit");
	keyHint.setCharacterSize(14);
	keyHint.setFillColor(sf::Color::White);
	keyHint.setPosition(240, 580);
}

void Npc::updateAnimation()
{
	//std::cout << "updateAnimation 1111" << std::endl;

	float totalTime = animationClock.getElapsedTime().asSeconds();
	float switchTime = 0.1f;

	int width = this->spriteTexture.getSize().x;
	if (totalTime >= switchTime) {
		if (intRect.left == width - tileWidth) {
				intRect.left = 0;
		}
		else {
			intRect.left += tileWidth;
		}
		sprite.setTextureRect(intRect);
        animationClock.restart();
	}
}

void Npc::updateInteracting()
{
	if (isInteracting) {
		//std::cout << text << std::endl;
		updateNpcTextRectUserInput();
	}
}

void Npc::updateNpcTextRectUserInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		isInteracting = false;
	}
}

void Npc::renderNpcText(sf::RenderTarget& target)
{
	target.draw(BackgroundRect);
    target.draw(TextRect);
    target.draw(npcText);
    target.draw(keyHint);
}

void Npc::updatePosition()
{
	spriteRect.setPosition(this->gameScene->getMapPos()+sf::Vector2f(relatedPos));
    sprite.setPosition(spriteRect.getPosition());
}


Npc::Npc(int tileWidth, int tileHeight, int spriteWide, int spriteHeight, std::string texturePath, sf::Vector2f position, std::string text)
{
    initVaribles(spriteWide, spriteHeight, tileWidth, tileHeight,text);
	InitSpriteRect(position);
	InitSprite(texturePath);
	InitText();
}

Npc::~Npc()
{
}

void Npc::update(const float& dt)
{
    updatePosition();
    updateAnimation();
    updateInteracting();

}

void Npc::render(sf::RenderTarget& target)
{
    target.draw(sprite);
	//target.draw(spriteRect);
	if (isInteracting) {
		renderNpcText(target);
	}
}

sf::RectangleShape Npc::getSpriteRect()
{
	//std::cout << this->spriteHeight << std::endl;
	return this->spriteRect;
}

void Npc::interactingWithCharacter()
{
	std::cout << "interactingWithCharacter" << std::endl;
	this->isInteracting = true;
}

void Npc::endInteraction()
{
    this->isInteracting = false;
}

void Npc::setGameScene(GameScene* gameScene)
{
	this->gameScene = gameScene;
}
