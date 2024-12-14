#include "Seller.h"
#include <iostream>
#include <chrono>

Seller::Seller(int tileWidth, int tileHeight, int spriteWide, int spriteHeight, std::string texturePath, sf::Vector2f position, sf::RenderTarget* Shoptarget):
	Npc(tileWidth, tileHeight, spriteWide, spriteHeight, texturePath, position,"")
{
	isOpenBox= false;
	currentAnimation = SellerAnimation::IDLE;
	intRect.top = tileHeight;
	sprite.setTextureRect(intRect);
	IDLEframeNum = 6;
    TalkingframeNum = 10;
    Flipping_CoinframeNum = 10;
    OpeningBOXframeNum = 6;
	isCollisionWithCharacter = false;
	isOpeningBox = false;
	cnt = 0;
	selectedItemIndex = -1;
	this->Shoptarget = Shoptarget;
	buyTimes = 1;
	initializeShop();
}

Seller::~Seller()
{
}

void Seller::startCollision()
{
	isCollisionWithCharacter = true;
	cnt = 1;

	if (!(isOpenBox || isOpeningBox)) {
		this->isOpeningBox = true;
		intRect.left = 0;
		this->currentAnimation = SellerAnimation::OpeningBOX;
		OpeningBOXframeNum = 8;
	}
	else {
        this->currentAnimation= SellerAnimation::Opening_IDLE;
	}
}

void Seller::endCollision()
{
	isCollisionWithCharacter = false;
	isOpenBox = false;
	if (cnt > 0) {
        cnt--;
		std::cout << "cnt:" << cnt << std::endl;
		switchIdleAnimation();
		std::cout << "currentAnimation:" << static_cast<int>(currentAnimation) << std::endl;
	}
}

void Seller::update()
{
	updatePosition();
	updateAnimation();
	updateInteracting();

}

void Seller::render(sf::RenderTarget& target)
{
    target.draw(sprite);
	//target.draw(spriteRect);
	if (isInteracting) {
		renderShop();
	}
}

void Seller::setCharacter(Charachter* character)
{
    this->character = character;
}

void Seller::setWand(Wand* wand)
{
	this->wand = wand;
}

void Seller::updateAnimation() {
	//std::cout << "Seller updateAnimation" << std::endl;
	float totalTime = animationClock.getElapsedTime().asSeconds();
	float switchTime = 0.1f;
	if (totalTime >= switchTime) {
		//std::cout << "currentAnimation:" << static_cast<int>(currentAnimation) << std::endl;
		//std::cout<<"isOpenBox"<<isOpenBox<<std::endl;
		//std::cout << "isOpeningBox:" << isOpeningBox << std::endl;
		if (((this->isOpeningBox && OpeningBOXframeNum > 0) || isOpenBox)) {
			//std::cout << "attackFrameCnt:" << attackFrameCnt << std::endl;
			//std::cout << "sss " << (this->isOpeningBox && OpeningBOXframeNum > 0 )<<std::endl;
			if (this->isOpeningBox && OpeningBOXframeNum > 0) {
				currentAnimation = SellerAnimation::OpeningBOX;
				OpeningBOXframeNum--;
				//std::cout << "OpeningBOXframeNum:" << OpeningBOXframeNum << std::endl;
				if (OpeningBOXframeNum == 0) {
					this->isOpeningBox = false;
					this->isOpenBox = true;
				}
			}
			else if (isOpenBox) {
				//std::cout << "isOpenBox" << std::endl;
				currentAnimation = SellerAnimation::Opening_IDLE;
			}
		}
		int top = 0;
		int left = 0;
		int width = 0;
		switch (currentAnimation) {
			case SellerAnimation::IDLE:
				top = tileHeight;
				left = 0;
                width = tileWidth*5;
				IDLEframeNum--;
                if (IDLEframeNum == 0) {
					switchIdleAnimation();
				}
				break;
            case SellerAnimation::Talking:
				top = tileHeight * 0;
				left = 0;
				width = tileWidth * 9;
				TalkingframeNum--;
				if (TalkingframeNum == 0) {
					switchIdleAnimation();
				}
				break;
            case SellerAnimation::Flipping_Coin:
				top = tileHeight * 2;
				left = 0;
				width = tileWidth * 9;
				Flipping_CoinframeNum--;
				if (Flipping_CoinframeNum == 0) {
					switchIdleAnimation();
				}
				break;
			case SellerAnimation::OpeningBOX:
                top = tileHeight * 3;
                left = 0;
				width = tileWidth * 7;
				break;
            case SellerAnimation::Opening_IDLE:
                top = tileHeight * 4;
                left = 0;
                width = tileWidth * 5;
                break;
			default:
                throw std::runtime_error("Invalid animation index");
		}
		//std::cout << "currentAnimation:" << static_cast<int>(currentAnimation) << std::endl;
		intRect.top = top;
		if (intRect.left >= width) {
			if (currentAnimation == SellerAnimation::OpeningBOX) {
				intRect.left = width;
			}
			else {
				intRect.left = left;
			}
		}
		else {
            intRect.left += tileWidth;
		}
		sprite.setTextureRect(intRect);
		animationClock.restart();
	}
	
	
}

void Seller::switchIdleAnimation()
{
	std::mt19937 generator(std::random_device{}());

	std::uniform_int_distribution<int> distribution(0, 2);

	int randomAnimation = distribution(generator);
	switch (randomAnimation) {
		case 0:
			currentAnimation = SellerAnimation::IDLE;
			IDLEframeNum = 12;
            break;
        case 1:
            currentAnimation = SellerAnimation::Talking;
            TalkingframeNum = 20;
            break;
		case 2:
			currentAnimation = SellerAnimation::Flipping_Coin;
            Flipping_CoinframeNum = 20;
            break;
		default:
			throw std::runtime_error("Invalid animation index");
	}
}

void Seller::initializeShop()
{
	shopWindow.setSize(sf::Vector2f(400, 600));
    shopWindow.setPosition(sf::Vector2f(1000, 20));
    shopWindow.setFillColor(sf::Color(56, 39, 30, 200));
    shopWindow.setOutlineThickness(4.0f);
    shopWindow.setOutlineColor(sf::Color::Black);

	descriptionBox.setSize(sf::Vector2f(380, 150));
    descriptionBox.setPosition(1010,414);
    descriptionBox.setFillColor(sf::Color(128, 107, 80, 230));
    descriptionBox.setOutlineThickness(2.0f);
    descriptionBox.setOutlineColor(sf::Color::Black);

	selectionBox.setSize(sf::Vector2f(370, 80));
	selectionBox.setFillColor(sf::Color(0, 0, 0, 0));
	selectionBox.setOutlineColor(sf::Color(205, 192, 176));
    selectionBox.setOutlineThickness(2.0f);


	itemTextures.resize(4);
    itemTextures[0].loadFromFile("Resources/Image/Icon/aeromancer-skill-icons-pixel-art/PNG/Icon44.png");
    itemTextures[1].loadFromFile("Resources/Image/Icon/aeromancer-skill-icons-pixel-art/PNG/Icon37.png");
    itemTextures[2].loadFromFile("Resources/Image/Icon/aeromancer-skill-icons-pixel-art/PNG/Icon42.png");
    itemTextures[3].loadFromFile("Resources/Image/Icon/aeromancer-skill-icons-pixel-art/PNG/Icon21.png");


    itemSprites.resize(4);
	for (int i = 0; i < 4; i++) {
        	itemSprites[i].setTexture(itemTextures[i]);
			itemSprites[i].setScale(64.0f / itemTextures[i].getSize().x, 64.0f / itemTextures[i].getSize().y);
            itemSprites[i].setPosition(1020 , 30 + i * 100);
	}

	if (!font.loadFromFile("Resources\\Image\\Font\\28177148754.ttf")) {
		throw std::runtime_error("Failed to load font");
	}

	itemTips.resize(4);
	tipStrings= { "Press ' One ' to select", "Press ' Two ' to select", "Press ' Three ' to select", "Press ' Four ' to select" };
	itemPrices = { 10, 20, 50, 100 };
	itemPricesText.resize(4);
	for (int i = 0; i < 4; i++) {
		itemTips[i].setFont(font);
		itemTips[i].setString(tipStrings[i]);
		itemTips[i].setCharacterSize(16);
		itemTips[i].setFillColor(sf::Color::White);
		itemTips[i].setPosition(1090, 30 + i * 100);
		itemTips[i].setFillColor(sf::Color(222, 211, 183));
		itemTips[i].setOutlineColor(sf::Color::Black);
		itemTips[i].setOutlineThickness(1.0f);


		itemPricesText[i].setFont(font);
		itemPricesText[i].setString("Price  $  " + std::to_string(itemPrices[i]));
		itemPricesText[i].setCharacterSize(14);
		itemPricesText[i].setFillColor(sf::Color::White);
		itemPricesText[i].setPosition(1300, 30 + i * 100);
		itemPricesText[i].setFillColor(sf::Color(222, 211, 183));
		itemPricesText[i].setOutlineColor(sf::Color::Black);
		itemPricesText[i].setOutlineThickness(1.0f);

		}

	descriptionText.setFont(font);
	descriptionText.setCharacterSize(14);
    descriptionText.setFillColor(sf::Color(222, 211, 183));
	descriptionText.setOutlineColor(sf::Color::Black);
    descriptionText.setOutlineThickness(1.0f);
    descriptionText.setPosition(1020, 424);


	keyHint.setFont(font);
	keyHint.setString("Press 'B' to exit, 'Y' to buy");
	keyHint.setCharacterSize(14);
	keyHint.setFillColor(sf::Color::White);
	keyHint.setPosition(1110, 574);
	keyHint.setFillColor(sf::Color(222, 211, 183));
	keyHint.setOutlineColor(sf::Color::Black);
	keyHint.setOutlineThickness(1.0f);


	int selectedItemIndex = -1;
	
	itemDescriptions= {
	"Angel Dove\nwhoosh whoosh whoosh, \nwhat a close call! Where did this \ndove come from, carrying a vial of blood\n in its beak? Whoosh whoosh whoosh, with the \nday of transformation upon us, \nthere's no time for further thought...",
	"Magic Wheel\nClickety Click! \nwhy not spin the wheel for 20 dollar, \nyoung man? You will randomly update your \nfixed launch mod magic. Buying it won't make \nyou poor, not buying it won't make you rich",
	"Purifying Spring\nThe natural hot spring water infuses,\ncleansing the worldly\nagony, healing the wounds across the body. \nIt serves as a remedy in chaotic times, \nand most importantly, \na mere soak can dispel all debuffs...",
	"Virgin's Prayer\nWhat's to say? \nThe girl has prayed,\nHP gets full, \nand debuffs disappear!"
	};



}

void Seller::updateShopUserInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
       selectedItemIndex = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
       selectedItemIndex = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
       selectedItemIndex = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
       selectedItemIndex = 3;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
		isInteracting = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)&&buyTimes>0) {
		updateBuyingAffect(selectedItemIndex);
        buyTimes--;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
        buyTimes = 1;
	}
}

void Seller::updateBuyingAffect(int index)
{



	// 定义一个均匀分布，范围在2到3之间
	std::uniform_int_distribution<> dis(2, 3);
	if (index >= 0 && index < 4) {
		std::string s = itemTips[index].getString();
		std::cout << "You bought item " << index + 1<<" " <<s<< " for $" << itemPrices[index] << std::endl;
		if (this->character->pay(itemPrices[index])) {
			std::cout << "You have enough money to buy this item." << std::endl;
			if (index == 0) {
				this->character->addHp(15);
			}
			else if (index == 1) {
				auto now = std::chrono::system_clock::now();

				// 将时间点转换为时间戳（自纪元以来的纳秒数）
				auto timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

				// 使用时间戳生成2到3之间的随机数
				int random_number = 1 + (timestamp % 3);
				std::cout << "Random number: " << random_number << std::endl;
				this->wand->setSingleTexture(random_number);
			}else if( index == 2){
				this->character->clearHurtType();
			}
			else if (index == 3) {
                this->character->clearHurtType();
                this->character->addHp(100);
			}
		}
		else {
            std::cout << "You don't have enough money to buy this item." << std::endl;
		}
	}
}

void Seller::renderShop()
{
	//std::cout << "Rendering shop" << std::endl;
	this->Shoptarget->draw(shopWindow);

	for (int i = 0; i < 4; i++) {
		this->Shoptarget->draw(itemSprites[i]);
        this->Shoptarget->draw(itemTips[i]);
        this->Shoptarget->draw(itemPricesText[i]);
	}

	if (selectedItemIndex >= 0 && selectedItemIndex < 4) {
		descriptionText.setString(itemDescriptions[selectedItemIndex]);
	}
	else {
		descriptionText.setString("");
	}
	this->Shoptarget->draw(descriptionBox);
    this->Shoptarget->draw(descriptionText);

    this->Shoptarget->draw(keyHint);
	
	if (selectedItemIndex >= 0 && selectedItemIndex < 4) {
		selectionBox.setPosition(1015, 25 + selectedItemIndex* 100);
		this->Shoptarget->draw(selectionBox);
	}
}

void Seller::updateInteracting()
{
	if (isInteracting) {
		//std::cout << "Interacting with Seller" << std::endl;

		updateShopUserInput();
	}
}

