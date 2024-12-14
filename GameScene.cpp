/*
掉出地图死亡需要补写

人物大小调整
*/


#include "GameScene.h"
#include "Entity.h"
#include <iostream>

GameScene::GameScene(sf::RenderWindow& window, std::vector<std::vector<bool>>& blocksRef)
    : Scene(window), currentBackgroundIndex(0), currentTileMapIndex(0), gravity(9.8f), maxSpeed(700.f), blockSize(4),
    blocks(blocksRef) {}

void GameScene::SetCharacter(Charachter* c)
{
    this->c = c;
}

//加载背景
bool GameScene::loadBackgrounds(const std::string& backgroundPath) {
    //for (const std::string& path : backgroundPath) {
    backgroundTextures.clear();
    sf::Texture texture;

    if (!texture.loadFromFile(backgroundPath)) {
        std::cerr << "ERROR::Scene::Failed to load " << backgroundPath << std::endl;
        return false;
    }

    backgroundTextures.push_back(texture);
    sf::Sprite currentBackground(backgroundTextures[currentBackgroundIndex]);//backgroundTextures.back()

    // 计算窗口中心位置
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTextures[currentBackgroundIndex].getSize();//backgroundTextures.back()

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    float scale = std::max(scaleX, scaleY);  // 保证填满窗口

    currentBackground.setScale(scale, scale);  // 设置背景精灵缩放
    backgroundSprites.clear();  // 清空当前背景精灵
    backgroundSprites.push_back(currentBackground);  // 添加当前背景精灵
    //}
    return true;
}


bool GameScene::loadTileMaps(const std::string& tileMapPath) {
    tileMapTextures.clear();
    sf::Texture texture;
    if (!texture.loadFromFile(tileMapPath)) {
        std::cerr << "ERROR::Scene::Failed to load " << tileMapPath << std::endl;
        return false;
    }

    tileMapTextures.push_back(texture);
    sf::Sprite currentTileMap(tileMapTextures[currentTileMapIndex]);

    sf::Image mapImage = texture.copyToImage();
    mapImages.push_back(mapImage);  // 存储图像数据，避免每次都读取纹理

    // 计算窗口中间的位置
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    float tileMapWidth = currentTileMap.getLocalBounds().width * currentTileMap.getScale().x;
    float tileMapHeight = currentTileMap.getLocalBounds().height * currentTileMap.getScale().y;

    // 将 TileMap 的最左端对齐到画面水平中心
    float posX = windowWidth / 3.f;
    float posY = (windowHeight - tileMapHeight) / 1.5f;


    currentTileMap.setPosition(posX, posY);
    //currentTileMap.setPosition(0, 0);


    blocks.clear();

    //blockSize = 4; // 每个块的大小

    // 先计算地图的块数
    int numBlocksX = mapImage.getSize().x / blockSize;
    int numBlocksY = mapImage.getSize().y / blockSize;

    //std::cout << "numBlocksX = " << numBlocksX << std::endl;
    //std::cout << "numBlocksY = " << numBlocksY << std::endl;



    blocks.resize(numBlocksX, std::vector<bool>(numBlocksY, false));



    // 遍历地图图像，检测每个块是否包含墙体（即透明度 > 0）
    for (int x = 0; x < numBlocksX; ++x) {
        for (int y = 0; y < numBlocksY; ++y) {
            bool hasWall = false;
            for (int bx = x * blockSize; bx < (x + 1) * blockSize; ++bx) {
                for (int by = y * blockSize; by < (y + 1) * blockSize; ++by) {
                    sf::Color pixelColor = mapImage.getPixel(bx, by);
                    if (pixelColor.a > 0) {
                        hasWall = true;
                        break;
                    }

                }
                if (hasWall) break;
            }
            blocks[x][y] = hasWall;
        }

    }


    tileMapSprites.clear();
    tileMapSprites.push_back(currentTileMap);


    return true;
}


bool GameScene::checkHorizontalCollision(float entityX, float entityY, float entityWidth, float entityHeight, sf::Vector2f tile_offset,
    float offset_x, int blockSize, std::vector<std::vector<bool>>& blocks) {


    int leftBlock = ((entityX - tile_offset.x - offset_x) / blockSize);
    int rightBlock = ((entityX - tile_offset.x - offset_x + entityWidth) / blockSize);

    for (int x = leftBlock; x <= rightBlock; ++x) {
        for (int y = ((entityY - tile_offset.y) / blockSize); y < (entityY + entityHeight - tile_offset.y) / blockSize; ++y) {
            if (blocks[x][y]) {
                //std::cout << "horizontal" << std::endl;
                return true;  // 碰撞检测
            }
        }
    }
    return false;  // 没有水平碰撞
}

bool GameScene::checkVerticalCollision(float entityX, float entityY, float entityWidth, float entityHeight, sf::Vector2f tile_offset,
    float offset_y, int blockSize, std::vector<std::vector<bool>>& blocks) {


    int topBlock = (entityY - offset_y - tile_offset.y) / blockSize;
    int bottomBlock = (entityY - offset_y - tile_offset.y + entityHeight) / blockSize;


    for (int y = topBlock; y <= bottomBlock; ++y) {
        for (int x = (entityX - tile_offset.x) / blockSize; x < (entityX + entityWidth - tile_offset.x) / blockSize; ++x) {
            if (blocks[x][y] && x >= 0 && y >= 0) {
                //std::cout << "vertical" << std::endl;
                return true;  // 碰撞检测到
            }
        }
    }
    return false;  // 没有垂直碰撞
}

bool GameScene::isOutOfMapBounds(float entityX, float entityY, float offset_y, sf::Vector2f tile_offset, float entityHeight, int blockSize, const std::vector<std::vector<bool>>& blocks) {


    int bottomBlock = (entityY - tile_offset.y - offset_y + entityHeight) / blockSize;


    if (bottomBlock >= blocks[0].size()) {
        return true;  // 掉出了地图边界
    }
    return false;  // 在地图范围内
}

bool GameScene::arrive(float entityX, float offset_x, float entityWidth, sf::Vector2f tile_offset, int blockSize, const std::vector<std::vector<bool>>& blocks) {

    int rightBlock = ((entityX - tile_offset.x - offset_x + entityWidth) / blockSize);

    if (rightBlock >= blocks.size()-20) {

        return true;
    }
    return false;
}


//更新地图速度
void GameScene::updateVelocity(float dir_x, bool isJumping) {
    // 更新横向速度
    float oldy = sceneVelocity.y;
    //std::cout << "oldy" << oldy << std::endl;
    sceneVelocity = c->getVelocity();
    sceneVelocity.x *= -1;
    sceneVelocity.y = oldy;
    //sceneVelocity.y *=0;
    if (isJumping) {
        sceneVelocity.y = jumpSpeed + gravity * 5;  // 瞬间向下移动（地图向下，人物跳跃）
        canJump = false;                            // 禁止再次跳跃

    }
    else {
        sceneVelocity.y -= gravity * 5; // 恒定向上的重力加速度
    }

    // 限制纵向速度
    if (sceneVelocity.y > maxSpeed) sceneVelocity.y = maxSpeed;
    if (sceneVelocity.y < -maxSpeed) sceneVelocity.y = -maxSpeed;
}


//更新场景, 接收输入, 检测碰撞
void GameScene::update(float deltaTime, float entityX, float entityY, float entityWidth, float entityHeight) {

    // 获取玩家输入方向
    float dir_x = 0.f;
    bool isJumping = false;



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
        isJumping = true; // 触发跳跃
        //canJump = false;
        jumpCooldownTimer = 0.5f;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        dir_x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        dir_x += 1.f;
    }

    if (!canJump) {
        jumpCooldownTimer -= deltaTime;
        if (jumpCooldownTimer <= 0.f) {
            canJump = true; // 冷却时间结束，允许跳跃
        }
    }

    // 更新速度
    updateVelocity(dir_x, isJumping);

    // 计算每帧的偏移量
    sf::Vector2f offset(sceneVelocity.x * deltaTime, sceneVelocity.y * deltaTime);

    sf::Vector2f tile_offset = tileMapSprites[currentTileMapIndex].getPosition();

    if (isOutOfMapBounds(entityX, entityY, offset.y, tile_offset, entityHeight, blockSize, blocks)) {
        std::cout << "Fall out of the bounds." << std::endl;
        this -> c->takeDamage(100, true, 0);
        isDroped = true;
        /*掉出地图边界死亡*/
    }


    // 检测碰撞并移动地图
    if ((!isDroped) && !checkHorizontalCollision
    (entityX, entityY, entityWidth, entityHeight, tile_offset, offset.x, blockSize, blocks)) {

        for (auto& sprite : tileMapSprites) {
            sprite.move(offset.x, 0.f);
        }
    }
    else {
        sceneVelocity.x = 0.f; // 水平碰撞后停止
    }


    if ((!isDroped) && !checkVerticalCollision
    (entityX, entityY, entityWidth, entityHeight, tile_offset, offset.y, blockSize, blocks)) {
        for (auto& sprite : tileMapSprites) {
            sprite.move(0.f, offset.y);
        }
    }
    else {
        sceneVelocity.y = 0.f; // 垂直碰撞后停止

    }



}


// 渲染画面
void GameScene::render(sf::RenderWindow& window) {
    if (!backgroundSprites.empty())
    {
        window.draw(backgroundSprites[currentBackgroundIndex]);
        //std::cout << currentBackgroundIndex << std::endl;
    }


    if (!tileMapSprites.empty())
    {
        window.draw(tileMapSprites[currentTileMapIndex]);
    }
}
sf::Vector2f GameScene::getSceneVelocity() {
    return sceneVelocity;
}
sf::Vector2f GameScene::getMapPos()
{
    return this-> tileMapSprites[currentTileMapIndex].getPosition();
}
