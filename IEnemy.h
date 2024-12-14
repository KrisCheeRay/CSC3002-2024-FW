#ifndef IENEMY_H
#define IENEMY_H

#include "Entity.h"

class IEnemy :public Entity {
public:

    // 获取敌人的碰撞矩形
    virtual sf::FloatRect getBoundingBox() const = 0;

    // 扣除敌人血量
    virtual void takeDamage(int damage) = 0;

    // 获取敌人当前血量
    virtual int getHealth() const = 0;

    // 虚析构函数
    virtual ~IEnemy() = default;
};

#endif // IENEMY_H