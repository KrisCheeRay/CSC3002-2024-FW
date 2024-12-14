#ifndef CHARACHTER_H
#define CHARACHTER_H
#include "Entity.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Setting.h"
#include <vector>
#include "IEnemy.h"
#include <utility>
#include "HP_MP.h"
#include "Coins.h"




class Npc;
class Seller;
class IEnemy;
class gameScene;


enum class CharachterAnlmationState
{
    Idle=0,
    Run=1,
    Attack=2,
    Dash_Attack=3,
    Injury=4,
    Dead=5

};



enum class HurtType {
    Normal=0,
    Fire=1,
    Ice=2,
    Poison=3
};




class Charachter :
    public Entity
{
private:
    //animationTexturesMap
    std::unordered_map<CharachterAnlmationState,std::vector<sf::Texture>> animationTexturesMap;
    std::unordered_map<CharachterAnlmationState,int> animationCurrentIndexMap;





    //Variables
    Direction direction;
    CharachterAnlmationState animationState;
    double Hp;
    double Mp;
    float jumpVelocity;
    bool canJump;
    bool isJumping;
    bool canAttack;
    bool isDashing;
    bool isAttacking;
    bool isHurt;
    bool isDead;
    bool isGameOver;
    int attackDamage;
    int attackFrameCnt;
    int dashingVelocity;
    int interactionTime;
    int money;
    int deadFrameCnt;
    int hurtAnimationFrameCnt;
    int point;
    sf::Vector2f oldPosition;
    Setting Setting;


    //hurtState
    std::vector<std::pair<HurtType, int>> hurtTypes;

    std::unordered_map < HurtType, sf::Sprite > hurtTypeCountMap;
    std::unordered_map < HurtType, int> hurtTypeFrameCntMap;


    //tileSize
    int tileSize;
    int spriteSize;




    //Magicball ´ý¶¨
    sf::Sprite magicBallSprite;
    std::vector<sf::Texture> magicBallTextures;
    int magicBallFrameCnt;


    //NPC interaction
    bool canInteractingWithNpc;
    bool canInteractingWithSeller;
    bool comfirmInteractingWithNpc;
    bool comfirmInteractingWithSeller;

    std::vector<Npc*> *npcs;
    std::vector<Seller*> *sellers;
    std::vector<IEnemy*> enemies;

    HP_MP *hp_mp;
    Coins *coins;


    void initVariables(int tileSize,int spriteSize, std::vector<Npc*>& npcs, std::vector<Seller*>& sellers);
    void InitSpriteRect();
    void InitSprite();
    void InitAnimationTexturesMap();
    void InitHurtFrameCntMap();
    void InitMagicBallSprite();
    void userInput();
    void updateAnimation();
    void updateMovement(const float& dt);
    void updateVelocity(float direction_x, float direction_y);
    void updateSpritePos();
    void updateInteractionWithNpcs();
    void updateInteractionWithSellers();
    void updateHurt();
    void updateMagicBall();
    void changeSpriteDirection();
    bool isWallCollision(sf::FloatRect playerRect=sf::FloatRect(), sf::FloatRect wallRect = sf::FloatRect());
    bool isGroundCollision(sf::FloatRect playerRect= sf::FloatRect(), sf::FloatRect groundRect= sf::FloatRect());
    bool isCollicionWithNpc(Npc* npc);
    bool isCollicionWithSeller(Seller * seller);
    void renderState(sf::RenderTarget& target);
    void loadMagicBallTextures();
    void hitAttack();
public:
    Charachter(int tileSize,int spriteSize, std::vector<Npc*>& npcs, std::vector<Seller*>& sellers,HP_MP * hp_mp,Coins * coins);
    virtual ~Charachter();

    void update(const float& dt);

    void render(sf::RenderTarget& target);

    int getPoints();

    sf::Vector2f getMagicBallPosition() const;

    sf::FloatRect getSpriteRectBox() const;

    sf::Vector2f getSpritePosition() const;
    bool pay(int money);

    void Init(sf::Vector2f position);

    void takeDamage(int damage,bool isCriticalHit,int hurtType);

    void addMoney(int money);
    void addPoint(int point);
    void start();
    void addHp(int hp);

    bool isOver();

    void Hurt();

    void clearHurtType();
    void reSetSellers(std::vector<Seller*>& seller);
    void reSetNpcs(std::vector<Npc*>& npcs);

    sf::Vector2f getVelocity();
    
};
#endif // 



