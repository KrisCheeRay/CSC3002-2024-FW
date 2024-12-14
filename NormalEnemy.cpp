#include "NormalEnemy.h"
#include <stdexcept>
#include <iostream>

bool NormalEnemy::loadAnimationFrames(std::vector<sf::Texture>& textures, const std::string& basePath, int frameCount) {
    textures.clear();
    textures.reserve(frameCount);

    std::cout << "\n=== Debug Info ===\n";
    std::cout << "Base path: " << basePath << "\n";
    std::cout << "Frame count: " << frameCount << "\n";

    for (int i = 1; i <= frameCount; ++i) {
        sf::Texture texture;
        std::string path = basePath + std::to_string(i) + ".png";
        std::cout << "Loading: " << path << "\n";

        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load texture: " << path << "\n";
            return false;
        }
        textures.push_back(texture);
    }
    std::cout << "=== Debug End ===\n\n";
    return true;
}

void NormalEnemy::updateSpriteOrigin() {
    // 设置精灵的原点为中心
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void NormalEnemy::InitHurtFrameCntMap()
{
    this->hurtTypeFrameCntMap[HurtType::Normal] = 10;
    this->hurtTypeFrameCntMap[HurtType::Fire] = 50;
    this->hurtTypeFrameCntMap[HurtType::Ice] = 50;
    this->hurtTypeFrameCntMap[HurtType::Poison] = 50;
}

void NormalEnemy::fireBullet(std::vector<Bullet>& bullets, const sf::Vector2f& targetPosition) {
    if (!canAttack) return;

    Bullet bullet(true);
    bullet.sprite.setPosition(sprite.getPosition());


    sf::Vector2f direction = targetPosition - sprite.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction /= length;
    }

    bullet.velocity = direction;

    bullet.sprite.setRotation(std::atan2(direction.y, direction.x) * 180 / 3.14159265);

    // 根据伤害类型设置子弹颜色
    switch (bulletDamageType) {
    case 0: // Normal
        bullet.setTexture(0);
        break;
    case 1: // Fire
        bullet.setTexture(1);
        break;
    case 2: // Ice
        bullet.setTexture(2);
        break;
    case 3: // Poison
        bullet.setTexture(3);
        break;
    default:
        break;
    }



    bullets.push_back(bullet);
    std::cout << "add bullet" << bullets.size() << std::endl;

    std::cout << "Bullet fired!\n";
    canAttack = false;
    attackTimer = 0.f;
}
void NormalEnemy::setCircularAttack(bool enable) {
    isCircularAttacking = enable;
    if (enable) {
        circularAttackAngle = 0.f;
    }
}

void NormalEnemy::fireCircularBullets(std::vector<Bullet>& bullets) {
    if (!canAttack) return;

    float angleRadians = circularAttackAngle * 3.14159f / 180.f;

    // 创建当前角度的子弹
    Bullet bullet(true);
    bullet.speed = bulletSpeed;
    bullet.sprite.setPosition(sprite.getPosition());

    // 计算方向向量
    sf::Vector2f direction(
        cos(angleRadians),
        sin(angleRadians)
    );

    bullet.velocity = direction;

    // 设置子弹颜色
    // 根据伤害类型设置子弹颜色
    switch (bulletDamageType) {
    case 0: // Normal
        bullet.setTexture(0);
        break;
    case 1: // Fire
        bullet.setTexture(1);
        break;
    case 2: // Ice
        bullet.setTexture(2);
        break;
    case 3: // Poison
        bullet.setTexture(3);
        break;
    default:
        break;
    }


    bullets.push_back(bullet);

    // 更新角度
    circularAttackAngle += angleIncrement;
    if (circularAttackAngle >= 360.f) {
        circularAttackAngle = 0.f;
        canAttack = false;
        attackTimer = 0.f;
    }
}

void NormalEnemy::InitSpriteRect() {
    baseWidth = spriteSize;
    baseHeight = spriteSize;
    updateCollisionBox();
    spriteRect.setFillColor(sf::Color::Transparent);
    spriteRect.setOutlineThickness(1.f);
    spriteRect.setOutlineColor(sf::Color::Red);
}
NormalEnemy::NormalEnemy(const sf::Vector2f& position, const std::string& resourcePath, float spriteSize,
    int initialHealth, float initialMovementSpeed, int initialAttackDamage, float initialAttackCooldown,
    float bulletRadius, float bulletSpeed, float bulletLifetime, int bulletDamageType,
    float patrolWidth, float patrolHeight,
    int idleFrameCount, int walkFrameCount, int attackFrameCount, int injuryFrameCount, int deathFrameCount,
    bool showPatrolArea)
    : scale(1.f, 1.f)  // 添加这一行
    , baseWidth(spriteSize)  // 添加这一行
    , baseHeight(spriteSize)  // 添加这一行
    , isBoss(isBoss)  // 在初始化列表中添加
    , health(initialHealth)
    , movementSpeed(initialMovementSpeed)
    , attackDamage(initialAttackDamage)
    , facing(Direction::Right)
    , currentState(EnemyState::IDLE)
    , currentFrame(0)
    , isAnimating(false)
    , animationCooldown(0.1f)
    , frameWidth(0.f)
    , frameHeight(0.f)
    , patrolTimer(0.f)
    , patrolDuration(2.f)
    , attackCooldown(initialAttackCooldown)
    , attackTimer(0.f)
    , canAttack(true)
    , isPlayerInPatrolArea(false)
    , showPatrolArea(showPatrolArea)    // 使用传入的参数
    , injuryDuration(0.5f)
    , injuryTimer(0.f)
    , injuryFrameCount(injuryFrameCount)
    , spriteSize(spriteSize)
    , bulletRadius(bulletRadius)
    , bulletSpeed(bulletSpeed)
    , bulletLifetime(bulletLifetime)
    , bulletDamageType(bulletDamageType)
    , idleFrameCount(idleFrameCount)
    , walkFrameCount(walkFrameCount)
    , attackFrameCount(attackFrameCount)
    , deathFrameCount(deathFrameCount)
    , patrolWidth(patrolWidth)
    , patrolHeight(patrolHeight)
    , enemyType(EnemyType::BigEye)  // 添加这行
    , resourcePath(resourcePath)     // 添加这行
    , isCircularAttacking(false)
    , circularAttackAngle(0.f)
    , angleIncrement(360.f / CIRCULAR_BULLET_COUNT)
{
    try {
        InitHurtFrameCntMap();

        std::string path = resourcePath;

        // 加载各种状态的动画帧
        if (!loadAnimationFrames(idleTextures, resourcePath + "idle_", idleFrameCount)) {
            throw std::runtime_error("Failed to load idle animations!");
        }
        if (!loadAnimationFrames(walkTextures, resourcePath + "walk_", walkFrameCount)) {
            throw std::runtime_error("Failed to load walk animations!");
        }
        if (!loadAnimationFrames(attackTextures, resourcePath + "attack_", attackFrameCount)) {
            throw std::runtime_error("Failed to load attack animations!");
        }
        if (!loadAnimationFrames(injuryTextures, resourcePath + "takehit_", injuryFrameCount)) {
            throw std::runtime_error("Failed to load injury animations!");
        }
        if (!loadAnimationFrames(deathTextures, resourcePath + "death_", deathFrameCount)) {
            throw std::runtime_error("Failed to load death animations!");
        }

        // 设置初始精灵状态
        if (!idleTextures.empty()) {
            sprite.setTexture(idleTextures[0]);
            updateSpriteOrigin();
            sprite.setPosition(position);
            sprite.setScale(scale.x, scale.y);
            InitSpriteRect();
        }
        else {
            throw std::runtime_error("No textures loaded for idle animation!");
        }

        // 设置初始位置和巡逻区域
        initialPosition = position;
        patrolArea = sf::FloatRect(position.x - patrolWidth / 2, position.y - patrolHeight / 2,
            patrolWidth, patrolHeight);
        patrolAreaShape.setFillColor(sf::Color(255, 0, 0, 50));
        patrolAreaShape.setOutlineColor(sf::Color::Red);
        patrolAreaShape.setOutlineThickness(2.f);
        updatePatrolArea();
    }
    catch (const std::exception& e) {
        std::cerr << "Error initializing NormalEnemy: " << e.what() << std::endl;
        throw;
    }
}

void NormalEnemy::update(const float& dt, const sf::FloatRect& playerBounds, const sf::Vector2f& playerPosition, std::vector<Bullet>& bullets) {
    if (currentState != EnemyState::DEATH) {
        // 处理受伤状态
        float totalTime = animationTimer.getElapsedTime().asSeconds();
        float switchTime = 0.1f;

        if (totalTime >= switchTime) {
            for (auto& hurtType : hurtTypes) {
                if (hurtType.second > 0) {
                    switch (hurtType.first) {
                    case HurtType::Normal:
                        health -= 1;
                        break;
                    case HurtType::Fire:
                        health -= 20.0 / 50.0;
                        break;
                    case HurtType::Ice:
                        if (hurtType.second == 50) {
                            health -= 10.0;
                        }
                        movementSpeed = (movementSpeed - 45 < 0) ? 0 : movementSpeed - 45;
                        break;
                    case HurtType::Poison:
                        health *= 0.993;
                        break;
                    }
                    hurtType.second--;
                }
            }

            hurtTypes.erase(
                std::remove_if(hurtTypes.begin(), hurtTypes.end(),
                    [](const auto& pair) { return pair.second <= 0; }),
                hurtTypes.end());
        }

        // 更新攻击冷却
        if (!canAttack) {
            attackTimer += dt;
            if (attackTimer >= attackCooldown) {
                canAttack = true;
                attackTimer = 0.f;
            }
        }

        // 处理受伤状态
        if (currentState == EnemyState::INJURY) {
            injuryTimer += dt;
            if (injuryTimer >= injuryDuration) {
                currentState = EnemyState::PATROL;
                injuryTimer = 0.f;
            }
        }
        else {
            // 检查玩家是否在巡逻区域内
            checkPatrolArea(playerBounds);

            if (isPlayerInPatrolArea) {
                currentState = EnemyState::ATTACK;
                if (canAttack) {
                    if (isCircularAttacking) {
                        fireCircularBullets(bullets);
                    }
                    else {
                        fireBullet(bullets, playerPosition);
                    }
                }
            }

            // 更新移动和状态
            updateMovement(dt);

            // 更新巡逻区域位置（始终跟随怪物）
            sf::Vector2f centerPos = sprite.getPosition();
            patrolArea = sf::FloatRect(
                centerPos.x - patrolArea.width / 2,
                centerPos.y - patrolArea.height / 2,
                patrolArea.width,
                patrolArea.height
            );
            updatePatrolArea();
        }

        updateSpritePos();
        updateSpriteDirection();
        updateAnimation();
    }
}


void NormalEnemy::updateAnimation() {
    if (animationTimer.getElapsedTime().asSeconds() >= animationCooldown) {
        std::vector<sf::Texture>* currentTextures = &idleTextures;
        int maxFrames = idleTextures.size();

        // 根据当前状态选择对应的动画帧集合
        switch (currentState) {
        case EnemyState::IDLE:
            currentTextures = &idleTextures;
            maxFrames = idleTextures.size();
            break;
        case EnemyState::PATROL:
            currentTextures = &walkTextures;
            maxFrames = walkTextures.size();
            break;
        case EnemyState::ATTACK:
            currentTextures = &attackTextures;
            maxFrames = attackTextures.size();
            break;
        case EnemyState::DEATH:
            currentTextures = &deathTextures;
            maxFrames = deathTextures.size();
            break;
        case EnemyState::INJURY:
            currentTextures = &injuryTextures;
            maxFrames = injuryTextures.size();
            if (currentFrame >= maxFrames - 1) {
                currentState = EnemyState::PATROL;
            }
            break;
        }

        // 更新当前帧
        currentFrame = (currentFrame + 1) % maxFrames;

        // 特殊状态处理
        if (currentState == EnemyState::DEATH && currentFrame >= maxFrames - 1) {
            currentFrame = maxFrames - 1;
        }
        else if (currentState == EnemyState::ATTACK && currentFrame >= maxFrames - 1) {
            currentState = EnemyState::PATROL;
            currentFrame = 0;
        }

        // 保存当前位置
        sf::Vector2f currentPos = sprite.getPosition();

        // 更新精灵纹理
        sprite.setTexture((*currentTextures)[currentFrame]);
        updateSpriteOrigin();

        // 设置缩放和朝向
        float scaleX = scale.x;
        //if (facing == Direction::Left) {
        //    scaleX = -std::abs(scale.x);
        //}
        //else {
        //    scaleX = std::abs(scale.x);
        //}
        //sprite.setScale(scaleX, scale.y);

        // 恢复位置
        sprite.setPosition(currentPos);

        animationTimer.restart();
    }
}

void NormalEnemy::updateMovement(const float& dt) {
    if (currentState == EnemyState::DEATH) return;

    sf::Vector2f movement(0.f, 0.f);
    switch (currentState) {
    case EnemyState::IDLE:
    {
        // 待机状态下的小幅左右移动
        patrolTimer += dt;
        float idleMovementSpeed = movementSpeed * 0.3; // 降低待机时的移动速度

        if (facing == Direction::Left) {
            movement.x = -idleMovementSpeed * dt;
        }
        else {
            movement.x = idleMovementSpeed * dt;
        }

        // 在原位置左右各移动50像素
        float currentX = sprite.getPosition().x;
        float distanceFromStart = currentX - (initialPosition.x-this->gameScene->getMapPos().x/3);

        if (distanceFromStart <= -100.f) {
            facing = Direction::Right;
        }
        else if (distanceFromStart >= 100.f) {
            facing = Direction::Left;
        }
        //std::cout << "1111 " << distanceFromStart << std::endl;
        movement = movement + this->gameScene->sceneVelocity * dt;
        sprite.move(movement);

        break;
    }

    case EnemyState::PATROL:
    {
        // 在巡逻区域内移动
        if (facing == Direction::Left) {
            movement.x = -movementSpeed * dt;
            if (sprite.getPosition().x - frameWidth / 2 <= patrolArea.left) {
                facing = Direction::Right;
            }
        }
        else {
            movement.x = movementSpeed * dt;
            if (sprite.getPosition().x + frameWidth / 2 >= patrolArea.left + patrolArea.width) {
                facing = Direction::Left;
            }
        }
        movement = movement + this->gameScene->sceneVelocity * dt;

        sprite.move(movement);

        break;
    }

    case EnemyState::ATTACK:
        // 攻击状态不移动
        sprite.move(this->gameScene->sceneVelocity * dt);

        break;

    case EnemyState::INJURY:
        sprite.move(this->gameScene->sceneVelocity * dt);
        break;
    default:
        break;
    }
}

void NormalEnemy::updateState() {
    // 状态转换逻辑
    switch (currentState) {
    case EnemyState::IDLE:
        if (isPlayerInPatrolArea) {
            currentState = EnemyState::PATROL;
            currentFrame = 0;
        }
        break;

    case EnemyState::PATROL:
        if (!isPlayerInPatrolArea) {
            currentState = EnemyState::IDLE;
            currentFrame = 0;
        }
        break;

    case EnemyState::ATTACK:
        if (!isPlayerInPatrolArea) {
            currentState = EnemyState::IDLE;
            currentFrame = 0;
        }
        break;

    default:
        break;
    }
}

void NormalEnemy::updateSpritePos()
{
    spriteRect.setPosition(sprite.getPosition());
}

void NormalEnemy::checkPatrolArea(const sf::FloatRect& playerBounds) {
    bool wasPlayerInPatrolArea = isPlayerInPatrolArea;
    isPlayerInPatrolArea = patrolArea.intersects(playerBounds);

    // 处理玩家进入或离开巡逻区域的情况
    if (wasPlayerInPatrolArea && !isPlayerInPatrolArea) {
        currentState = EnemyState::IDLE;
        currentFrame = 0;
    }
    else if (!wasPlayerInPatrolArea && isPlayerInPatrolArea) {
        currentState = EnemyState::PATROL;
        currentFrame = 0;
    }

    // 仅在showPatrolArea为true时更新巡逻区域的颜色
    if (showPatrolArea) {
        if (isPlayerInPatrolArea) {
            patrolAreaShape.setFillColor(sf::Color(255, 0, 0, 50));
            patrolAreaShape.setOutlineColor(sf::Color::Red);
        }
        else {
            patrolAreaShape.setFillColor(sf::Color(0, 255, 0, 50));
            patrolAreaShape.setOutlineColor(sf::Color::Green);
        }
    }
}


void NormalEnemy::attack() {
    if (canAttack && currentState != EnemyState::DEATH) {
        // 这里可以创建投射物或执行其他攻击逻辑
        canAttack = false;
        attackTimer = 0.f;
        currentState = EnemyState::ATTACK;
        currentFrame = 0; // 重置动画帧以开始攻击动画
    }
}

void NormalEnemy::takeDamage(int damage, int hurtType) {
    if (currentState != EnemyState::DEATH) {
        HurtType ht = static_cast<HurtType>(hurtType);
        hurtTypes.push_back(std::pair<HurtType, int>(ht, hurtTypeFrameCntMap[ht]));

        health -= damage;
        currentFrame = 0;

        if (health <= 0) {
            health = 0;
            currentState = EnemyState::DEATH;
        }
        else {
            currentState = EnemyState::INJURY;
            injuryTimer = 0.f;
        }
    }
}

void NormalEnemy::render(sf::RenderTarget& target)
{

    if (showPatrolArea) {
        target.draw(patrolAreaShape);
    }
    target.draw(sprite);
    if (showPatrolArea) {  // 只在显示巡逻区域时显示碰撞体积
        target.draw(spriteRect);
    }
}

bool NormalEnemy::isDead() const {
    return health <= 0;
}

sf::FloatRect NormalEnemy::getBounds() const {
    return spriteRect.getGlobalBounds();
}

sf::Vector2f NormalEnemy::getPosition() const {
    return sprite.getPosition();
}

int NormalEnemy::getHealth() const {
    return health;
}

EnemyState NormalEnemy::getCurrentState() const {
    return currentState;
}

Direction NormalEnemy::getFacing() const {
    return facing;
}

void NormalEnemy::setPosition(const sf::Vector2f& pos) {
    sprite.setPosition(pos);
    initialPosition = pos;
}

void NormalEnemy::setPatrolArea(const sf::FloatRect& area) {
    patrolArea = area;
    updatePatrolArea();
}

void NormalEnemy::setMovementSpeed(float speed) {
    movementSpeed = speed;
}

void NormalEnemy::setAttackDamage(int damage) {
    attackDamage = damage;
}
bool NormalEnemy::isPlayerDetected() const {
    return isPlayerInPatrolArea;
}

void NormalEnemy::togglePatrolAreaVisibility(bool show) {
    showPatrolArea = show;
}

void NormalEnemy::updatePatrolArea() {
    patrolAreaShape.setPosition(patrolArea.left, patrolArea.top);
    patrolAreaShape.setSize(sf::Vector2f(patrolArea.width, patrolArea.height));
}

void NormalEnemy::setInitialHealth(int newHealth) {
    health = newHealth;
}

void NormalEnemy::setInitialMovementSpeed(float speed) {
    movementSpeed = speed;
}

void NormalEnemy::setInitialAttackDamage(int damage) {
    attackDamage = damage;
}

void NormalEnemy::setInitialAttackCooldown(float cooldown) {
    attackCooldown = cooldown;
}

void NormalEnemy::setBulletProperties(float radius, float speed, float lifetime, int damageType) {
    bulletRadius = radius;
    bulletSpeed = speed;
    bulletLifetime = lifetime;
    bulletDamageType = damageType;
}

void NormalEnemy::setPatrolDimensions(float width, float height) {
    patrolWidth = width;
    patrolHeight = height;
    patrolArea = sf::FloatRect(sprite.getPosition().x - width / 2,
        sprite.getPosition().y - height / 2,
        width, height);
    updatePatrolArea();
}

void NormalEnemy::setAnimationFrameCounts(int idle, int walk, int attack, int injury, int death) {
    idleFrameCount = idle;
    walkFrameCount = walk;
    attackFrameCount = attack;
    injuryFrameCount = injury;
    deathFrameCount = death;
}

void NormalEnemy::setScale(float scaleX, float scaleY) {
    scale = sf::Vector2f(scaleX, scaleY);

    // 根据朝向设置正确的X轴缩放
    float finalScaleX = facing == Direction::Left ? -std::abs(scaleX) : std::abs(scaleX);
    sprite.setScale(finalScaleX, scaleY);

    // 更新碰撞体积
    updateCollisionBox();
}

void NormalEnemy::setScale(const sf::Vector2f& newScale) {
    setScale(newScale.x, newScale.y);
}

sf::Vector2f NormalEnemy::getScale() const {
    return scale;
}

void NormalEnemy::updateCollisionBox() {
    // 更新碰撞矩形的大小，考虑缩放
    float scaledWidth = baseWidth * std::abs(scale.x);
    float scaledHeight = baseHeight * std::abs(scale.y);
    spriteRect.setSize(sf::Vector2f(scaledWidth, scaledHeight));

    // 重新设置原点为中心
    spriteRect.setOrigin(scaledWidth / 2.f, scaledHeight / 2.f);

    // 更新位置以保持与精灵同步
    spriteRect.setPosition(sprite.getPosition());
}

void NormalEnemy::takeDamage(int damage, bool isCriticalHit, int hurtType)
{
    int finalDamage = isCriticalHit ? damage * 2 : damage;

    HurtType ht = static_cast<HurtType>(hurtType);
    hurtTypes.push_back(std::pair<HurtType, int>(ht, hurtTypeFrameCntMap[ht]));

    if (currentState != EnemyState::DEATH) {
        HurtType ht = static_cast<HurtType>(hurtType);
        hurtTypes.push_back(std::pair<HurtType, int>(ht, hurtTypeFrameCntMap[ht]));

        health -= finalDamage;
        currentFrame = 0;

        if (health <= 0) {
            health = 0;
            currentState = EnemyState::DEATH;
        }
        else {
            currentState = EnemyState::INJURY;
            injuryTimer = 0.f;
        }
    }
}

void NormalEnemy::setGameScene(GameScene* gameScene)
{
    this->gameScene = gameScene;
}

void NormalEnemy::updateSpriteDirection() {
    float scaleX = std::abs(scale.x);
    if (facing == Direction::Left) {
        sprite.setScale(-scaleX, scale.y);
    }
    else {
        sprite.setScale(scaleX, scale.y);
    }
}



