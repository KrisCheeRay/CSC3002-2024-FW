#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Entity.h"
#include <vector>
#include <memory>

class CollisionManager {
public:
    void checkCollisions(std::vector<std::unique_ptr<Entity>>& entities);//其中之一的碰撞
};

#endif // COLLISIONMANAGER_H