#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Entity.h"
#include <vector>
#include <memory>

class CollisionManager {
public:
    void checkCollisions(std::vector<std::unique_ptr<Entity>>& entities);//����֮һ����ײ
};

#endif // COLLISIONMANAGER_H