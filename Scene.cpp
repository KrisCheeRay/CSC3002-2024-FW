#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.h"

// ���캯��
Scene::Scene(sf::RenderWindow& win) : window(win), player(sf::Vector2f(50, 50)), deltaTime(0.0f) {
    // ��ʼ���ӽ�
    view.setSize(static_cast<float>(win.getSize().x), static_cast<float>(win.getSize().y));
    view.setCenter(0.0f, 0.0f);

    // ��ʼ�����
    player.setFillColor(sf::Color::Green);
    player.setPosition(0, 0); // ���������ʼλ��
}

// ���Ƴ���

// �����ӽ�����
void Scene::setViewCenter(float x, float y)
{
    view.setCenter(x, y);
}

// �ƶ��ӽ�
void Scene::moveView(float offsetX, float offsetY)
{
    view.move(offsetX, offsetY);
}

// ��ȡ�ӽ�
sf::View& Scene::getView()
{
    return view;
}

sf::Vector2f Scene::getPlayerPosition() const
{
    return sf::Vector2f();
}
