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
    INJURY,  // 新增这一行
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
    // 基础属性
    int health;
    float movementSpeed;
    int attackDamage;
    Direction facing;
    EnemyState currentState;
    bool isBoss;
    GameScene* gameScene;



    EnemyType enemyType;
    std::string resourcePath;


    // SFML 精灵相关
    sf::Sprite sprite;
    std::vector<sf::Texture> idleTextures;
    std::vector<sf::Texture> walkTextures;
    std::vector<sf::Texture> attackTextures;
    std::vector<sf::Texture> deathTextures;
    std::vector<sf::Texture> injuryTextures;  // 新增这一行
    sf::Clock animationTimer;
    sf::Vector2f scale;          // 存储X和Y方向的缩放值
    float baseWidth;             // 基础宽度（未缩放时的宽度）
    float baseHeight;            // 基础高度（未缩放时的高度）

    // 动画相关
    int currentFrame;
    bool isAnimating;
    float animationCooldown;
    float frameWidth;  // 添加帧宽度
    float frameHeight; // 添加帧高度

    // 巡逻相关
    sf::FloatRect patrolArea;
    bool isPlayerInPatrolArea;  // 标记玩家是否在巡逻区域内
    sf::RectangleShape patrolAreaShape;  // 用于可视化巡逻区域的形状
    bool showPatrolArea;  // 控制是否显示巡逻区域
    sf::Vector2f initialPosition;
    float patrolTimer;
    float patrolDuration;

    // 碰撞体积相关
    sf::RectangleShape spriteRect;  // 添加在其他 SFML 精灵相关变量附近
    float spriteSize;  // 添加在基础属性部分

    // 攻击相关
    float attackCooldown;
    float attackTimer;
    bool canAttack;

    // 私有方法
    void updateAnimation();
    void updateMovement(const float& dt);
    void updateState();
    void checkPatrolArea(const sf::FloatRect& playerBounds);
    bool loadAnimationFrames(std::vector<sf::Texture>& textures, const std::string& basePath, int frameCount);
    void updateSpriteOrigin(); // 新增：更新精灵原点
    void InitHurtFrameCntMap(); // 新增：初始化受伤动画帧数
    void updateSpritePos(); // 新增：更新精灵位置
    void InitSpriteRect(); // 新增：初始化碰撞体积
    void updateSpriteDirection(); // 新增：更新精灵朝向

    // 新增：受伤相关
    float injuryDuration;   // 受伤状态持续时间
    float injuryTimer;      // 受伤状态计时器


    // 受伤相关
    std::vector<std::pair<HurtType, int>> hurtTypes;
    std::unordered_map<HurtType, sf::Sprite> hurtTypeCountMap;
    std::unordered_map<HurtType, int> hurtTypeFrameCntMap;

    // 子弹属性
    float bulletRadius;
    float bulletSpeed;
    float bulletLifetime;
    int bulletDamageType;

    // 动画帧数
    int idleFrameCount;
    int walkFrameCount;
    int attackFrameCount;
    int injuryFrameCount;
    int deathFrameCount;

    // 巡逻区域尺寸
    float patrolWidth;
    float patrolHeight;

    bool isCircularAttacking;  // 新增：是否在进行环形攻击
    float circularAttackAngle; // 新增：环形攻击当前角度
    static const int CIRCULAR_BULLET_COUNT = 12; // 新增：环形攻击的子弹数量
    float angleIncrement;      // 新增：每颗子弹之间的角度增量

public:
    // 构造函数和析构函数
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
        bool showPatrolArea = false);    // 新添加的参数


    ~NormalEnemy() = default;


    // 核心功能
    void update(const float& dt, const sf::FloatRect& playerBounds);
    void render(sf::RenderTarget& target);

    // 状态控制
    void takeDamage(int damage, int hurtType = 0);  // 默认为普通伤害
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
            // Boss使用环形攻击
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
    bool isPlayerDetected() const;  // 获取玩家是否在巡逻区域内
    void togglePatrolAreaVisibility(bool show);  // 控制巡逻区域的可视化
    void updatePatrolArea();  // 更新巡逻区域的位置
    void setMovementSpeed(float speed);
    void setAttackDamage(int damage);
    // 子弹发射相关
    void fireBullet(std::vector<Bullet>& bullets, const sf::Vector2f& targetPosition);
    void update(const float& dt, const sf::FloatRect& playerBounds, const sf::Vector2f& playerPosition, std::vector<Bullet>& bullets);  // 更新update声明

    void setCircularAttack(bool enable); // 新增：设置是否启用环形攻击
    void fireCircularBullets(std::vector<Bullet>& bullets); // 新增：发射环形子弹

    // 基础属性设置
    void setInitialHealth(int health);
    void setInitialMovementSpeed(float speed);
    void setInitialAttackDamage(int damage);
    void setInitialAttackCooldown(float cooldown);

    // 子弹属性设置
    void setBulletProperties(float radius, float speed, float lifetime, int damageType);

    // 巡逻区域设置
    void setPatrolDimensions(float width, float height);

    // 动画帧数设置
    void setAnimationFrameCounts(int idle, int walk, int attack, int injury, int death);

    void setScale(float scaleX, float scaleY);
    void setScale(const sf::Vector2f& newScale);
    sf::Vector2f getScale() const;
    void updateCollisionBox();




    void takeDamage(int damage, bool isCriticalHit, int hurtType);


    void setGameScene(GameScene* gameScene);


};


#endif#pragma once