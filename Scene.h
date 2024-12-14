#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include "Entity.h"

class Scene {


protected:
    float deltaTime;

    std::vector<std::unique_ptr<Entity>> characters;     // 角色（玩家）
    std::vector<std::unique_ptr<Entity>> enemies;        // 敌人
    std::vector<std::unique_ptr<Entity>> friendlyNPC;    // 友方NPC

    sf::View view;
    sf::RectangleShape player;

    //sf::Texture backgroundTexture;
    //sf::Sprite backgroundSprite;

    sf::Texture tilesetTexture;  // 瓦片集纹理
    sf::Sprite tileSprite;       // 瓦片精灵

    int tileWidth = 0;
    int tileHeight = 0;
    int mapWidth = 0;
    int mapHeight = 0;
    int columns = 0;

    //void renderTileMap(sf::RenderWindow& window);

public:
    virtual ~Scene() = default;
    Scene(sf::RenderWindow& window);

    std::vector<sf::Texture> backgroundTextures;         // 背景纹理
    std::vector<sf::Sprite> backgroundSprites;          // 背景精灵

    std::vector<sf::Texture> tileMapTextures;
    std::vector<sf::Sprite> tileMapSprites;

    sf::RenderWindow& window;                           // 窗口引用

    //void draw(sf::RenderWindow& window);

    virtual void update(float deltaTime, float entityX, float entityY, float entityWidth, float entityHeight) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    /*
    //加载背景图片
    bool loadBackground(std::string filepaths);
    // 加载瓦片地图
    bool loadTileMap(const std::vector<std::string>& tileMapPath);
*/
// 视角操作
    void setViewCenter(float x, float y);
    void moveView(float offsetX, float offsetY);
    sf::View& getView();

    // 玩家相关操作
    sf::Vector2f getPlayerPosition() const;

};

#endif
