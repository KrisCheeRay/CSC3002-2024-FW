#ifndef IENEMY_H
#define IENEMY_H

#include "Entity.h"

class IEnemy :public Entity {
public:

    // ��ȡ���˵���ײ����
    virtual sf::FloatRect getBoundingBox() const = 0;

    // �۳�����Ѫ��
    virtual void takeDamage(int damage) = 0;

    // ��ȡ���˵�ǰѪ��
    virtual int getHealth() const = 0;

    // ����������
    virtual ~IEnemy() = default;
};

#endif // IENEMY_H