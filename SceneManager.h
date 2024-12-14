#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <vector>
#include <memory>
#include "Scene.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class SceneManager
{
	//Ĭ��private
	std::vector<std::unique_ptr<Scene>> scenes;
	int currentSceneIndex;
    public:
		SceneManager();
		void addScene(std::unique_ptr<Scene> scene);
		void switchScene(int index);
		void handleInput();//����һЩ������������룬�����л�������ѡ�أ�
		void update(float dt);
		void render(sf::RenderWindow& window);
		std::vector<std::unique_ptr<Entity>> & getCurrentScenes();
		~SceneManager()
		{

		}
};
#endif // 




