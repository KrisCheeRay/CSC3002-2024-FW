#ifndef NORMALENEMY_H
#define NORMALENEMY_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <utility>
#include "Bullet.hpp"
#include "Charachter.h"
#include "GameScene.h"

enum class EnemyState {
    IDLE,
    PATROL,
    ATTACK,
    INJURY,  // ������һ��
    DEATH
};

enum class EnemyType {
    BigEye,
    Ghost,
    BossEye,
    fireimp,
    firedog,
    Bossdragon,
    icemonster,
    iceslime,
    Bossmonster,
};



class NormalEnemy {
private:
    // ��������
    int health;
    float movementSpeed;
    int attackDamage;
    Direction facing;
    EnemyState currentState;
    bool isBoss;
    GameScene* gameScene;



    EnemyType enemyType;
    std::string resourcePath;


    // SFML �������
    sf::Sprite sprite;
    std::vector<sf::Texture> idleTextures;
    std::vector<sf::Texture> walkTextures;
    std::vector<sf::Texture> attackTextures;
    std::vector<sf::Texture> deathTextures;
    std::vector<sf::Texture> injuryTextures;  // ������һ��
    sf::Clock animationTimer;
    sf::Vector2f scale;          // �洢X��Y���������ֵ
    float baseWidth;             // ������ȣ�δ����ʱ�Ŀ�ȣ�
    float baseHeight;            // �����߶ȣ�δ����ʱ�ĸ߶ȣ�

    // �������
    int currentFrame;
    bool isAnimating;
    float animationCooldown;
    float frameWidth;  // ���֡���
    float frameHeight; // ���֡�߶�

    // Ѳ�����
    sf::FloatRect patrolArea;
    bool isPlayerInPatrolArea;  // �������Ƿ���Ѳ��������
    sf::RectangleShape patrolAreaShape;  // ���ڿ��ӻ�Ѳ���������״
    bool showPatrolArea;  // �����Ƿ���ʾѲ������
    sf::Vector2f initialPosition;
    float patrolTimer;
    float patrolDuration;

    // ��ײ������
    sf::RectangleShape spriteRect;  // ��������� SFML ������ر�������
    float spriteSize;  // ����ڻ������Բ���

    // �������
    float attackCooldown;
    float attackTimer;
    bool canAttack;

    // ˽�з���
    void updateAnimation();
    void updateMovement(const float& dt);
    void updateState();
    void checkPatrolArea(const sf::FloatRect& playerBounds);
    bool loadAnimationFrames(std::vector<sf::Texture>& textures, const std::string& basePath, int frameCount);
    void updateSpriteOrigin(); // ���������¾���ԭ��
    void InitHurtFrameCntMap(); // ��������ʼ�����˶���֡��
    void updateSpritePos(); // ���������¾���λ��
    void InitSpriteRect(); // ��������ʼ����ײ���
    void updateSpriteDirection(); // ���������¾��鳯��

    // �������������
    float injuryDuration;   // ����״̬����ʱ��
    float injuryTimer;      // ����״̬��ʱ��


    // �������
    std::vector<std::pair<HurtType, int>> hurtTypes;
    std::unordered_map<HurtType, sf::Sprite> hurtTypeCountMap;
    std::unordered_map<HurtType, int> hurtTypeFrameCntMap;

    // �ӵ�����
    float bulletRadius;
    float bulletSpeed;
    float bulletLifetime;
    int bulletDamageType;

    // ����֡��
    int idleFrameCount;
    int walkFrameCount;
    int attackFrameCount;
    int injuryFrameCount;
    int deathFrameCount;

    // Ѳ������ߴ�
    float patrolWidth;
    float patrolHeight;

    bool isCircularAttacking;  // �������Ƿ��ڽ��л��ι���
    float circularAttackAngle; // ���������ι�����ǰ�Ƕ�
    static const int CIRCULAR_BULLET_COUNT = 12; // ���������ι������ӵ�����
    float angleIncrement;      // ������ÿ���ӵ�֮��ĽǶ�����

public:
    // ���캯������������
    NormalEnemy(const sf::Vector2f& position,
        const std::string& resourcePath,
        float spriteSize = 64.f,
        int initialHealth = 100,
        float initialMovementSpeed = 100.f,
        int initialAttackDamage = 10,
        float initialAttackCooldown = 1.0f,
        float bulletRadius = 15.f,
        float bulletSpeed = 200.f,
        float bulletLifetime = 5.f,
        int bulletDamageType = 0,
        float patrolWidth = 200.f,
        float patrolHeight = 100.f,
        int idleFrameCount = 20,
        int walkFrameCount = 13,
        int attackFrameCount = 13,
        int injuryFrameCount = 4,
        int deathFrameCount = 15,
        bool showPatrolArea = false);    // ����ӵĲ���


    ~NormalEnemy() = default;


    // ���Ĺ���
    void update(const float& dt, const sf::FloatRect& playerBounds);
    void render(sf::RenderTarget& target);

    // ״̬����
    void takeDamage(int damage, int hurtType = 0);  // Ĭ��Ϊ��ͨ�˺�
    void attack();
    bool isDead() const;


    static std::string getPathByType(EnemyType type) {
        switch (type) {
        case EnemyType::BigEye:
            return "Resources/Image/Enemy/1_big_eye/";
        case EnemyType::Ghost:
            return "Resources/Image/Enemy/2_ghost/";
        case EnemyType::BossEye:
            return "Resources/Image/Enemy/3_Boss_eye/";
        case EnemyType::fireimp:
            return "Resources/Image/Enemy/4_fire_imp/";
        case EnemyType::firedog:
            return "Resources/Image/Enemy/5_fire_dog/";
        case EnemyType::Bossdragon:
            return "Resources/Image/Enemy/6_Boss_dragon/";
        case EnemyType::icemonster:
            return "Resources/Image/Enemy/7_ice_monster/";
        case EnemyType::iceslime:
            return "Resources/Image/Enemy/8_ice_slime/";
        case EnemyType::Bossmonster:
            return "Resources/Image/Enemy/9_Boss_monster/";
        default:
            return "Resources/Image/Enemy/1_big_eye/";
        }
    }

    void setBoss(bool boss) {
        isBoss = boss;
        if (isBoss) {
            // Bossʹ�û��ι���
            setCircularAttack(true);
        }
    }
    bool getIsBoss() const { return isBoss; }
    // Getters
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    int getHealth() const;
    EnemyState getCurrentState() const;
    Direction getFacing() const;

    // Setters
    void setPosition(const sf::Vector2f& pos);
    void setPatrolArea(const sf::FloatRect& area);
    bool isPlayerDetected() const;  // ��ȡ����Ƿ���Ѳ��������
    void togglePatrolAreaVisibility(bool show);  // ����Ѳ������Ŀ��ӻ�
    void updatePatrolArea();  // ����Ѳ�������λ��
    void setMovementSpeed(float speed);
    void setAttackDamage(int damage);
    // �ӵ��������
    void fireBullet(std::vector<Bullet>& bullets, const sf::Vector2f& targetPosition);
    void update(const float& dt, const sf::FloatRect& playerBounds, const sf::Vector2f& playerPosition, std::vector<Bullet>& bullets);  // ����update����

    void setCircularAttack(bool enable); // �����������Ƿ����û��ι���
    void fireCircularBullets(std::vector<Bullet>& bullets); // ���������价���ӵ�

    // ������������
    void setInitialHealth(int health);
    void setInitialMovementSpeed(float speed);
    void setInitialAttackDamage(int damage);
    void setInitialAttackCooldown(float cooldown);

    // �ӵ���������
    void setBulletProperties(float radius, float speed, float lifetime, int damageType);

    // Ѳ����������
    void setPatrolDimensions(float width, float height);

    // ����֡������
    void setAnimationFrameCounts(int idle, int walk, int attack, int injury, int death);

    void setScale(float scaleX, float scaleY);
    void setScale(const sf::Vector2f& newScale);
    sf::Vector2f getScale() const;
    void updateCollisionBox();




    void takeDamage(int damage, bool isCriticalHit, int hurtType);


    void setGameScene(GameScene* gameScene);


};


#endif#pragma once