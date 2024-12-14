#include "Charachter.h"
#include "Npc.h"
#include <iostream>
#include "Seller.h"
#include "algorithm"

void Charachter::initVariables(int tileSize,int spriteSize, std::vector<Npc*>& npcs, std::vector<Seller*>& sellers)
{





	direction = Direction::Right;
	animationState = CharachterAnlmationState::Idle;

	maxSpeed = 512.f;
	velocity=sf::Vector2f(0.f, 0.f);
	acceleration = 26.f;
    deceleration = 19.f;
	gravity = 9.8f;
	jumpVelocity = 500.f;
	canJump = true;
	isJumping = false;
	isAttacking = false;
	isDead = false;
	isHurt = false;
	isGameOver = true;
	canAttack = true;
	canInteractingWithNpc=false;
	comfirmInteractingWithNpc= false;
	canInteractingWithSeller = false;
    comfirmInteractingWithSeller = false;
	attackDamage = 10;
	attackFrameCnt = 5;
	dashingVelocity = 350;
	interactionTime = 1;
	deadFrameCnt = 6;
	hurtAnimationFrameCnt = 4;
	magicBallFrameCnt = 1;
	point = 0;


	Hp = 100;
	//hp_mp->reduceHP(0.6);
	Mp = 100; 
	money = 10000;
	coins->addCoins(10000);

	this->tileSize = tileSize;
	this->spriteSize = spriteSize;
	this->npcs = &npcs;
	this->sellers = &sellers;




	//test
	//hurtTypes.push_back(std::pair<HurtType, int>(HurtType::Normal,
	//	hurtTypeFrameCntMap[HurtType::Normal]));


	//hurtTypes.push_back(std::pair<HurtType, int>(HurtType::Fire,
	//	hurtTypeFrameCntMap[HurtType::Fire]));


	//hurtTypes.push_back(std::pair<HurtType, int>(HurtType::Ice, 
	//	hurtTypeFrameCntMap[HurtType::Ice]));


	//hurtTypes.push_back(std::pair<HurtType, int>(HurtType::Poison, 
	//	hurtTypeFrameCntMap[HurtType::Poison]));
}

void Charachter::InitSpriteRect()
{
	spriteRect.setSize(
		sf::Vector2f(
			static_cast<float>(60),
			static_cast<float>(spriteSize)
		)
	);
	
	spriteRect.setFillColor(sf::Color::Transparent);
	spriteRect.setOutlineThickness(1.f);
    spriteRect.setOutlineColor(sf::Color::Red);
	spriteRect.setOrigin(spriteRect.getGlobalBounds().width / 2.f, spriteRect.getGlobalBounds().height / 2.f);
	spriteRect.setPosition(800.f,500.f);
	oldPosition=spriteRect.getPosition();


}

void Charachter::InitSprite()
{
	if (!spriteTexture.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_idle_1.png")) {
		throw("ERROR::CHARACTER::FAILED TO LOAD TEXTURE");
	}
	intRect=sf::IntRect(0,0,tileSize,tileSize);
	sprite.setTextureRect(intRect);
    sprite.setTexture(spriteTexture);
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
    sprite.setPosition(spriteRect.getPosition());
	sprite.setScale(0.5f, 0.5f);
}

void Charachter::InitAnimationTexturesMap()
{

	sf::Texture texture1, texture2, texture3, texture4, texture5;
	texture1.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_idle_1.png");
	texture2.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_idle_2.png");
	texture3.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_idle_3.png");
	texture4.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_idle_4.png");
	texture5.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_idle_5.png");

	animationTexturesMap[CharachterAnlmationState::Idle] = { texture1, texture2, texture3, texture4, texture5 };



	sf::Texture texture6, texture7, texture8, texture9, texture10, texture11;
	texture6.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_walk_1.png");
	texture7.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_walk_2.png");
	texture8.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_walk_3.png");
	texture9.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_walk_4.png");
	texture10.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_walk_5.png");
	texture11.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_walk_6.png");


	animationTexturesMap[CharachterAnlmationState::Run] = { texture6,texture7,texture8,texture9,texture10,texture11 };


	sf::Texture texture12, texture13, texture14, texture15, texture16;
	texture12.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_attack_1.png");
	texture13.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_attack_2.png");
	texture14.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_attack_3.png");
	texture15.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_attack_4.png");
	texture16.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_attack_5.png");

	animationTexturesMap[CharachterAnlmationState::Attack] = {texture12, texture13,texture14,texture15,texture16 };



	animationTexturesMap[CharachterAnlmationState::Dash_Attack] = { texture12, texture13,texture14,texture15,texture16 };


	sf::Texture texture17, texture18, texture19, texture20;
	texture17.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_takehit_1.png");
	texture18.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_takehit_2.png");
	texture19.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_takehit_3.png");
	texture20.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_takehit_4.png");

	animationTexturesMap[CharachterAnlmationState::Injury] = {texture17, texture18,texture19,texture20 };



	sf::Texture texture21, texture22, texture23, texture24, texture25, texture26;
	texture21.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_die_1.png");
	texture22.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_die_2.png");
	texture23.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_die_3.png");
	texture24.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_die_4.png");
	texture25.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_die_5.png");
	texture26.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_die_6.png");

	animationTexturesMap[CharachterAnlmationState::Dead] = {texture21,texture22,texture23,texture24,texture25,texture26 };


	animationCurrentIndexMap[CharachterAnlmationState::Run] = 0;
	animationCurrentIndexMap[CharachterAnlmationState::Idle] = 0;
	animationCurrentIndexMap[CharachterAnlmationState::Attack] = 0;
	animationCurrentIndexMap[CharachterAnlmationState::Dash_Attack] = 0;
	animationCurrentIndexMap[CharachterAnlmationState::Injury] = 0;
	animationCurrentIndexMap[CharachterAnlmationState::Dead] = 0;



}

void Charachter::InitHurtFrameCntMap()
{
    this->hurtTypeFrameCntMap[HurtType::Normal]= 10;
    this->hurtTypeFrameCntMap[HurtType::Fire] = 50;
	this->hurtTypeFrameCntMap[HurtType::Ice] = 50;
	this->hurtTypeFrameCntMap[HurtType::Poison] = 50;
}

void Charachter::InitMagicBallSprite()
{
	loadMagicBallTextures();
	magicBallSprite.setTexture(magicBallTextures[0]);
	magicBallSprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);
    magicBallSprite.setPosition(sprite.getPosition()+sf::Vector2f(-50.f, -20.f));
	//magicBallSprite.setScale(0.5f, 0.5f);
}

void Charachter::userInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		animationState = CharachterAnlmationState::Run;
		direction = Direction::Left;
		changeSpriteDirection();
		updateVelocity(-1.0f, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		animationState = CharachterAnlmationState::Run;
		direction = Direction::Right;
		changeSpriteDirection();
		updateVelocity(1.0f, 0.0f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (canJump) {
			//std::cout << "jump" << std::endl;
			canJump = false;
			isJumping = true;
			updateVelocity(0.0f, -jumpVelocity);
		}
		else {
			//std::cout << "NOTjump" << std::endl;
			updateVelocity(0.0f, 0.0f);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		if (canAttack) {
			std::cout << "attack" << std::endl;
			isAttacking = true;
            attackFrameCnt = 5;
			animationCurrentIndexMap[animationState] = 0;
			animationState = CharachterAnlmationState::Attack;
		}
		else {
            std::cout << "NOTattack" << std::endl;
			animationState = CharachterAnlmationState::Idle;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (canAttack) {
			std::cout << "dash_attack" << std::endl;
			isAttacking = true;
			isDashing = true;
			attackFrameCnt = 5;
			animationCurrentIndexMap[animationState] = 0;
			animationState = CharachterAnlmationState::Dash_Attack;
		}
		else {
			std::cout << "NOTdash_attack" << std::endl;
            animationState = CharachterAnlmationState::Idle;
		}
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
		//std::cout << "CANInteracr" << canInteractingWithNpc << std::endl;
		//std::cout <<"Time" << interactionTime << std::endl;
		if (canInteractingWithNpc && interactionTime!=0) {
			std::cout << "interactNPC" << std::endl;
			comfirmInteractingWithNpc = true;
			interactionTime--;
		}
		if (canInteractingWithSeller && interactionTime != 0) {
            std::cout << "interactSeller" << std::endl;
            comfirmInteractingWithSeller = true;
            interactionTime--;
		}
	}


	if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::A) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::K)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::E)
		))
	{
		animationState = CharachterAnlmationState::Idle;
		interactionTime = 1;
		updateVelocity(0.0f, 0.0f);
	}
}

void Charachter::updateAnimation()
{
	float totalTime=animationClock.getElapsedTime().asSeconds();
	float switchTime = 0.1f;
	int animationSize;
	int animationIndex;
	if (isDead) {
		if (totalTime >= switchTime) {
			animationState = CharachterAnlmationState::Dead;
            deadFrameCnt--;
			if (deadFrameCnt == 0) {
				isGameOver= true;
			}
		}
	}
	else {
		if (isHurt) {
			if (totalTime >= switchTime) {
				animationState = CharachterAnlmationState::Injury;
				hurtAnimationFrameCnt--;
				std::cout << "hurtAnimationFrameCnt:" << hurtAnimationFrameCnt << std::endl;
				if (hurtAnimationFrameCnt <= 0) {
					isHurt = false;
					hurtAnimationFrameCnt = 4;
				}
			}
		}
		else {
			if (isAttacking && attackFrameCnt > 0 && (totalTime >= switchTime)) {
				//std::cout << "attackFrameCnt:" << attackFrameCnt << std::endl;
				animationState = CharachterAnlmationState::Attack;
				attackFrameCnt--;
				if (isAttacking && attackFrameCnt == 1) {
					hitAttack();
				}
			}
			else if (isAttacking && attackFrameCnt == 0) {
				isAttacking = false;
				isDashing = false;
			}
		}
		
	}
	animationSize = animationTexturesMap[animationState].size();
	animationIndex = animationCurrentIndexMap[animationState];

	//std::cout << "animationInedx1:" << animationIndex << std::endl;
	//std::cout << "animationIndexMAP1:" << animationCurrentIndexMap[animationState] << std::endl;
	if (totalTime >= switchTime) {
		sprite.setTexture(animationTexturesMap[animationState][animationIndex]);
		animationCurrentIndexMap[animationState] = (animationIndex + 1) % animationSize;
		//std::cout << "animationIndexMAP2:" << animationCurrentIndexMap[animationState] << std::endl;
		animationClock.restart();
	}




}

void Charachter::updateMovement(const float& dt)
{
//X direction_v
	if (velocity.x < 0) {
		if (-velocity.x >= maxSpeed) {
            velocity.x = -maxSpeed;
		}
		velocity.x += deceleration;
		if (velocity.x >= 0) {
            velocity.x = 0;
		}
	}
	else if (velocity.x > 0) {
		if (velocity.x >= maxSpeed) {
            velocity.x = maxSpeed;
		}
		velocity.x -= deceleration;
		if (velocity.x <= 0) {
			velocity.x = 0;
		}
	}
//Y direction_v



	//velocity.y += gravity;




	//后期可以加衰落伤害
	//std::cout << "Vy:" << velocity.y << std::endl;
	if (isDashing) {
		if (direction == Direction::Left) {
			velocity.x -= dashingVelocity;
		}
		else {
			velocity.x += dashingVelocity;
		}
	}

	oldPosition=spriteRect.getPosition();
	//spriteRect.move(velocity * dt);
	// 
	// 
	// 
	//std::cout << "curx1:" << spriteRect.getPosition().x << "cury:" << spriteRect.getPosition().y << std::endl;
	//std::cout << "oldx1:" << oldPosition.x << "oldy:" << oldPosition.y << std::endl;
	bool isGround = isGroundCollision();
	bool isWall = isWallCollision();
	sf::Vector2f cur_pos = spriteRect.getPosition();
	if (isWall) {
		if (velocity.x != 0) {
			velocity.x = 0;
			cur_pos.x = oldPosition.x;
		}
	}
	if (isGround) {
		canJump = true;
		isJumping = false;
		//std::cout << "ground" << std::endl;
		if (velocity.y != 0) {
			velocity.y = 0;
			cur_pos.y = oldPosition.y;
		}
	}
    //spriteRect.setPosition(cur_pos);

	//std::cout << "curx2:" << spriteRect.getPosition().x << "cury:" << spriteRect.getPosition().y << std::endl;
	//std::cout << "oldx2:" << oldPosition.x << "oldy:" << oldPosition.y << std::endl;

}

void Charachter::updateSpritePos()
{

	sprite.setPosition(spriteRect.getPosition());
}

void Charachter::updateInteractionWithNpcs()
{
	for (Npc* npc : *(this->npcs)) {
		if (isCollicionWithNpc(npc)) {
			//std::cout << comfirmInteractingWithNpc << std::endl;
            canInteractingWithSeller = false;
			if (comfirmInteractingWithNpc) {
				canInteractingWithNpc = false;
				npc->interactingWithCharacter();
				comfirmInteractingWithNpc = false;
			}
		}
	}
}

void Charachter::updateInteractionWithSellers()
{
	//std::cout << "updateInteractionWithSellers111" <<sellers->size()<<std::endl;
	for (Seller* seller :* (this->sellers)) {
		if (isCollicionWithSeller(seller)) {
			//std::cout << comfirmInteractingWithNpc << std::endl;
			canInteractingWithNpc = false;
			if (comfirmInteractingWithSeller) {
				canInteractingWithSeller = false;
				seller->interactingWithCharacter();
				comfirmInteractingWithSeller = false;
			}
		}
	}
}

void Charachter::updateHurt()
{
	if (Hp <= 0) {
		std::cout << "dead" << std::endl;
		isDead = true;
	}
	else {
		float totalTime = animationClock.getElapsedTime().asSeconds();
		float switchTime = 0.1f;
		if (totalTime >= switchTime) {

			for (std::pair<HurtType, int> & hurtType : hurtTypes) {
				if (hurtType.second > 0) {
					switch (hurtType.first)
					{
					case HurtType::Normal:
						Hp-=1;
						this->hp_mp->reduceHP(0.01f);
						break;
					case HurtType::Fire:
						Hp-=20.0/50.0;
						this->hp_mp->reduceHP(0.004f);
						break;
					case HurtType::Ice:
						if (hurtType.second == 50) {
							Hp-=10.0;
							this->hp_mp->reduceHP(0.1);
						}
						if (velocity.x > 0) {
							velocity.x=(velocity.x-45<0) ? 0 : velocity.x-45;
						}
						else {
                            velocity.x = (velocity.x + 45 > 0) ? 0 : velocity.x + 45;
						}
						
						break;
					case HurtType::Poison:
						this->hp_mp->reduceHP(float((1-0.993)*Hp)/100);
						Hp *=0.993;
						break;
					default:
						break;
					}
					hurtType.second--;
				}
			}

			//remove the hurtType from the map if the frame count is 0
			for (auto it = hurtTypes.begin(); it != hurtTypes.end();) {
				if ((*it).second == 0) {
					it = hurtTypes.erase(it);
				}
				else {
                    ++it;
				}
			}


		}
	}
}

void Charachter::updateMagicBall()
{
	if (direction == Direction::Left) {
		magicBallSprite.setPosition(sprite.getPosition() + sf::Vector2f(50.f, -20.f));
	}
	else {
        magicBallSprite.setPosition(sprite.getPosition() + sf::Vector2f(-50.f, -20.f));
	}
	float totalTime = animationClock.getElapsedTime().asSeconds();
	float switchTime = 0.1f;
	if (totalTime >= switchTime) {
        magicBallSprite.setTexture(magicBallTextures[magicBallFrameCnt]);
		magicBallFrameCnt = (magicBallFrameCnt + 1) % magicBallTextures.size();
	}
}

void Charachter::updateVelocity(float direction_x, float direction_y)
{
	velocity.x+= direction_x * acceleration;
    velocity.y += direction_y * 1;
}

void Charachter::changeSpriteDirection()
{
	switch (direction) {
	case Direction::Left:
		if (sprite.getScale() != sf::Vector2f(-0.5f, 0.5f)) {
			sprite.setScale(-0.5f, 0.5f);
		}
		break;
	case Direction::Right:
		if (sprite.getScale() != sf::Vector2f(0.5f, 0.5f)) {
			sprite.setScale(0.5f, 0.5f);
		}
		break;
	default:
		throw std::runtime_error("Invalid direction");
        break;
	}
}

bool Charachter::isWallCollision(sf::FloatRect playerRect, sf::FloatRect wallRect)
{
	//暂时
	if (spriteRect.getPosition().x > Setting.getWindowWidth() || spriteRect.getPosition().x < 0) {
		return true;
	}
	return false;
}

bool Charachter::isGroundCollision(sf::FloatRect playerRect, sf::FloatRect groundRect)
{
	//暂时
	if(spriteRect.getPosition().y > Setting.getWindowHeight()-200 || spriteRect.getPosition().y < 200) {
		return true;
	}
	return false;
}

bool Charachter::isCollicionWithNpc(Npc* npc)
{
	
	if (this->spriteRect.getGlobalBounds().intersects(npc->getSpriteRect().getGlobalBounds())) {
		canInteractingWithNpc = true;
		//std::cout << "CANinteracting" << std::endl;
		return true;
	}
	canInteractingWithNpc = false;
	return false;
}

bool Charachter::isCollicionWithSeller(Seller* seller)
{
	if (this->spriteRect.getGlobalBounds().intersects(seller->getSpriteRect().getGlobalBounds())) {
		std::cout << "seller" << std::endl;
		canInteractingWithSeller = true;
		seller->startCollision();
        return true;
	}
	canInteractingWithSeller = false;
	seller->endCollision();
	return false;
}

void Charachter::renderState(sf::RenderTarget& target)

{   
	sf::Texture texture1, texture2, texture3, texture4;
	texture1.loadFromFile("Resources\\Image\\Debuff\\Effect_hearty.png");
	texture2.loadFromFile("Resources\\Image\\Debuff\\Effect_On_fire.png");
	texture3.loadFromFile("Resources\\Image\\Debuff\\Effect_Frozen.png");
	texture4.loadFromFile("Resources\\Image\\Debuff\\Effect_Jarated.png");

	sf::Sprite sprite1, sprite2, sprite3, sprite4;
	sprite1.setTexture(texture1);
	sprite2.setTexture(texture2);
	sprite3.setTexture(texture3);
	sprite4.setTexture(texture4);
	sprite1.setScale(0.5f, 0.5f);
	sprite2.setScale(0.5f, 0.5f);
	sprite3.setScale(0.5f, 0.5f);
	sprite4.setScale(0.5f, 0.5f);
	hurtTypeCountMap[HurtType::Normal] = sprite1;
	hurtTypeCountMap[HurtType::Fire] = sprite2;
	hurtTypeCountMap[HurtType::Ice] = sprite3;
	hurtTypeCountMap[HurtType::Poison] = sprite4;




	

	
	
	
	
	
	
	int size = hurtTypes.size();
	for (int i = 0; i < size; i++) {
		sf::Sprite &sp = hurtTypeCountMap[hurtTypes[i].first];
        sp.setPosition(this->sprite.getPosition().x-55+i*30, this->sprite.getPosition().y-70);
		target.draw(sp);
	}
}

void Charachter::loadMagicBallTextures()
{
	for (int i = 1; i <= 41; ++i) {
		sf::Texture texture;
		std::string filePath = "Resources//Image//Portal//Portal_100x100px" + std::to_string(i) + ".png";
		if (texture.loadFromFile(filePath)) {
			magicBallTextures.push_back(texture);
		}
		else {
			std::cerr << "Failed to load texture: " << filePath << std::endl;
		}
	}
}

void Charachter::hitAttack()
{
	std::cout << "Hit Attack" << std::endl;
	for (IEnemy* enemy : enemies) {
		if (enemy->getBoundingBox().intersects(getSpriteRectBox())) {
			enemy->takeDamage(attackDamage);
		}
	}


	for (auto it = enemies.begin(); it != enemies.end();) {
		if ((*it)->getHealth() <= 0) {
			std::cout << "Enemy killed" << std::endl;
			it=enemies.erase(it);
		}
		else {
			++it;
		}
	}
}

Charachter::Charachter(int tileSize,int spriteSize, std::vector<Npc*>& npcs, std::vector<Seller*>& sellers,HP_MP* hp_mp,Coins *coins)
{
	this->hp_mp = hp_mp;
	this->coins = coins;
	InitHurtFrameCntMap();
	initVariables(tileSize,spriteSize,npcs,sellers);
	InitAnimationTexturesMap();
	InitSpriteRect();
    InitSprite();
	InitMagicBallSprite();

}

Charachter::~Charachter()
{
}

void Charachter::update(const float& dt)
{
	if (!isGameOver) {
		if (!isDead) {
			userInput();
			updateHurt();
			updateMovement(dt);
			updateMagicBall();
			updateInteractionWithNpcs();
			updateInteractionWithSellers();
		}
		
		updateAnimation();
		updateSpritePos();
	}
}

void Charachter::render(sf::RenderTarget& target)
{
	if (!isGameOver) {
		sprite.setPosition(sprite.getPosition()+sf::Vector2f(0,10));
		target.draw(sprite);
		//target.draw(spriteRect);
		renderState(target);
		target.draw(magicBallSprite);
	}
}

int Charachter::getPoints()
{
	return point;
}

sf::Vector2f Charachter::getMagicBallPosition() const
{
	return magicBallSprite.getPosition();
}

sf::FloatRect Charachter::getSpriteRectBox() const
{
	return spriteRect.getGlobalBounds();
}

sf::Vector2f Charachter::getSpritePosition() const
{
	return spriteRect.getPosition();
}

bool Charachter::pay(int money)
{
	if (money <= this->money) {
		std::cout << "pay " << money << " money" << std::endl;
		this->money -= money;
		this->coins->spendCoins(money);
		return true;
	}
	else {
		std::cout << "money is not enough" << std::endl;
        return false;
	}
	
}

void Charachter::Init(sf::Vector2f position)
{
	hurtTypes.clear();
	initVariables(tileSize, spriteSize, *npcs, *sellers);
	spriteRect.setPosition(position);
	oldPosition = spriteRect.getPosition();
	sprite.setPosition(spriteRect.getPosition());

}

void Charachter::takeDamage(int damage, bool isCriticalHit,int hurtType)
{
	int finalDamage = isCriticalHit ? damage * 2 : damage;

	HurtType ht = static_cast<HurtType>(hurtType);
	hurtTypes.push_back(std::pair<HurtType,int>(ht, hurtTypeFrameCntMap[ht]));

	Hp -= finalDamage;
	hp_mp->reduceHP(float(finalDamage)/100);
	Hurt();
}

void Charachter::addMoney(int money)
{
    this->money += money;
}

void Charachter::addPoint(int point)
{
    this->point += point;
}

void Charachter::start()
{
	isGameOver = false;
}

void Charachter::addHp(int hp)
{
	float r=float(hp)/100;
	Hp += hp;
	Hp = (Hp > 100) ? 100 : Hp;
	hp_mp->increaseHP(r);
}

bool Charachter::isOver()
{
	return isGameOver;
}

void Charachter::Hurt()
{
	isHurt = true;
}

void Charachter::clearHurtType()
{
	this -> hurtTypes.clear();
}

void Charachter::reSetSellers(std::vector<Seller*>& sellesr)
{
	this->sellers = sellers;
}

void Charachter::reSetNpcs(std::vector<Npc*>& npcs)
{
	this->npcs = &npcs;
}

sf::Vector2f Charachter::getVelocity()
{
	return velocity;
}


