#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <vector>
#include <memory>
#include "Scene.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class SceneManager
{
	//默认private
	std::vector<std::unique_ptr<Scene>> scenes;
	int currentSceneIndex;
    public:
		SceneManager();
		void addScene(std::unique_ptr<Scene> scene);
		void switchScene(int index);
		void handleInput();//处理一些场景管理的输入，比如切换场景（选关）
		void update(float dt);
		void render(sf::RenderWindow& window);
		std::vector<std::unique_ptr<Entity>> & getCurrentScenes();
		~SceneManager()
		{

		}
};
#endif // 




