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

    std::vector<std::unique_ptr<Entity>> characters;     // ��ɫ����ң�
    std::vector<std::unique_ptr<Entity>> enemies;        // ����
    std::vector<std::unique_ptr<Entity>> friendlyNPC;    // �ѷ�NPC

    sf::View view;
    sf::RectangleShape player;

    //sf::Texture backgroundTexture;
    //sf::Sprite backgroundSprite;

    sf::Texture tilesetTexture;  // ��Ƭ������
    sf::Sprite tileSprite;       // ��Ƭ����

    int tileWidth = 0;
    int tileHeight = 0;
    int mapWidth = 0;
    int mapHeight = 0;
    int columns = 0;

    //void renderTileMap(sf::RenderWindow& window);

public:
    virtual ~Scene() = default;
    Scene(sf::RenderWindow& window);

    std::vector<sf::Texture> backgroundTextures;         // ��������
    std::vector<sf::Sprite> backgroundSprites;          // ��������

    std::vector<sf::Texture> tileMapTextures;
    std::vector<sf::Sprite> tileMapSprites;

    sf::RenderWindow& window;                           // ��������

    //void draw(sf::RenderWindow& window);

    virtual void update(float deltaTime, float entityX, float entityY, float entityWidth, float entityHeight) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    /*
    //���ر���ͼƬ
    bool loadBackground(std::string filepaths);
    // ������Ƭ��ͼ
    bool loadTileMap(const std::vector<std::string>& tileMapPath);
*/
// �ӽǲ���
    void setViewCenter(float x, float y);
    void moveView(float offsetX, float offsetY);
    sf::View& getView();

    // �����ز���
    sf::Vector2f getPlayerPosition() const;

};

#endif
