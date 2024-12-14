#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.h"

// 构造函数
Scene::Scene(sf::RenderWindow& win) : window(win), player(sf::Vector2f(50, 50)), deltaTime(0.0f) {
    // 初始化视角
    view.setSize(static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y));
    view.setCenter(0.0f, 0.0f);

    // 初始化玩家
    player.setFillColor(sf::Color::Green);
    player.setPosition(0, 0); // 设置玩家起始位置
}

// 绘制场景

// 设置视角中心
void Scene::setViewCenter(float x, float y)
{
    view.setCenter(x, y);
}

// 移动视角
void Scene::moveView(float offsetX, float offsetY)
{
    view.move(offsetX, offsetY);
}

// 获取视角
sf::View& Scene::getView()
{
    return view;
}

sf::Vector2f Scene::getPlayerPosition() const
{
    return sf::Vector2f();
}
