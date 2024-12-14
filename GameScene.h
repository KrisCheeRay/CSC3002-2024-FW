#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "Scene.h"
#include "Entity.h"
#include <vector>
#include <string>
#include "Charachter.h"



class Charachter;
class GameScene : public Scene {
private:
    std::vector<sf::Image> mapImages;

    int blockSize;


    std::vector<std::vector<bool>>& blocks;




    float jumpCooldownTimer = 0.5f;      // ��ȴ��ʱ��
    bool canJump = true;                // ��Ծ�������

    sf::Vector2f tile_offset;

    float maxSpeed;                         //����ƶ��ٶ�
    float gravity;
    float acceleration = 26.f;
    float deceleration = 19.f;
    float jumpSpeed = 2000.f;




    size_t currentTileMapIndex;         // ��ǰС�ؿ�
    size_t currentBackgroundIndex;      // ��ǰ��ؿ�



    std::vector<sf::Texture> backgroundTextures;
    std::vector<sf::Texture> tileMapTextures;

    Charachter* c;


public:
    bool isDroped = false;
    sf::Vector2f sceneVelocity;             //�����ƶ��ٶ�

    GameScene(sf::RenderWindow& window, std::vector<std::vector<bool>>& blocksRef);

    void SetCharacter(Charachter* c);


    bool loadBackgrounds(const std::string& paths);
    bool loadTileMaps(const std::string& paths);


    bool checkHorizontalCollision(float entityX, float entityY, float entityWidth, float entityHeight, sf::Vector2f tile_offset,
        float offset_x, int blockSize, std::vector<std::vector<bool>>& blocks);
    bool checkVerticalCollision(float entityX, float entityY, float entityWidth, float entityHeight, sf::Vector2f tile_offset,
        float offset_y, int blockSize, std::vector<std::vector<bool>>& blocks);

    bool isOutOfMapBounds(float entityX, float entityY, float entityHeight, sf::Vector2f tile_offset, float offset_y, int blockSize, const std::vector<std::vector<bool>>& blocks);

    bool arrive(float entityX, float offset_x, float entityWidth, sf::Vector2f tile_offset, int blockSize, const std::vector<std::vector<bool>>& blocks);




    void update(float deltaTime, float entityX, float entityY, float entityWidth, float entityHeight) override;
    void updateVelocity(float dir_x, bool isJumping);





    void render(sf::RenderWindow& window) override;     // ��Ⱦ��ǰ����

    sf::Vector2f getSceneVelocity();


    sf::Vector2f getMapPos();
};




#endif