#pragma once
#ifndef GAMEFUNCTION_H
#define GAMEFUNCTION_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "CollisionManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Charachter.h"
#include "Npc.h"
#include "Seller.h"
#include "Explosion.h"
#include "Bullet.hpp"
#include "Wand.hpp"
#include <vector>
#include "GameScene.h"
#include "MainMenu.h"
#include "HP_MP.h"
#include "GameOver.h"
#include "AudioManager.h"
#include "Backpack.h"
#include "Coins.h"
#include "LevelBGManager.h"
#include "GameIntro.h"
#include "NormalEnemy.h"

namespace gf {

	const float EPSILON = 1e-5f;
	void eventHandler(sf::RenderWindow& window, Charachter& c,
		std::vector<Bullet>& bullets,
		sf::Clock& bulletClock,
		sf::Time& bulletInterval,
		Wand& wand,
		bool& gameStarted,
		bool& gameOverState,
		bool& gamePaused,
		bool& gameRestarted,
		bool& gameClosed,
		bool& victoryState,
		MainMenu& mainMenu,
		AudioManager& audioManager,
		HP_MP& hpMp,
		Backpack& backpack,
		GameOver& gameOver,
		Coins& coins,
		sf::Event& event,
		std::vector<Npc*>& npcs,
		std::vector<Seller*>& sellers, Seller& seller,
		Npc& npc,
		int& currentTileMapIndex,
		int& currentBackgroundIndex,
		GameScene& gameScene,
		std::vector<std::string>& tileMaps,
		std::vector<std::string>& backgrounds,
		std::vector<NormalEnemy>& normalEnemy,
		std::vector<Explosion> &explosion);//About the players input





	void update(sf::RenderWindow& window,
		std::vector<Charachter*>& characters, std::vector<Npc*> &npcs,
		std::vector<Seller*> &sellers,
		std::vector<Bullet>& bullets,
		std::vector<Explosion>& explosions,
		sf::Clock& clock,
		std::vector<sf::Texture> explosionTextures,
		sf::Time& targetSpawnTime,
		int& currentTileMapIndex,
		int& currentBackgroundIndex,
		GameScene& gameScene,
		std::vector<std::string>& tileMaps,
		std::vector<std::string>& backgrounds,
		bool& gameStarted,
		bool& gameOverState,
		bool& gamePaused,
		bool& gameRestarted,
		bool& gameClosed,
		bool& victoryState,
		MainMenu& mainMenu,
		AudioManager& audioManager,
		HP_MP& hpMp,
		Backpack& backpack,
		GameOver& gameOver,
		Coins& coins,
		LevelBGManager& levelBGManager,
		std::vector<std::vector<bool>>& blocks,
		Seller &seller,
		Seller &seller2,
		Seller &seller3, 
		Seller &seller4, 
		Seller &seller5, 
		Seller &seller6, 
		Npc& npc,
		Npc &npc2,
		Npc& npc3,
		Wand& wand,
		std::vector<NormalEnemy> &normalEnemy);//About the update of game elements from collision to movement
    
	void render(sf::RenderWindow& window,
		std::vector<Charachter*>& characters,
		std::vector<Npc*> &npcs,
		std::vector<Seller*> &sellers,
		std::vector<Bullet>& bullets,
		std::vector<Explosion>& explosions,
		GameScene& gameScene,
		bool& gameStarted,
		bool& gameOverState,
		bool& gamePaused,
		bool& gameRestarted,
		bool& gameClosed,
		bool& victoryState,
		MainMenu& mainMenu,
		AudioManager& audioManager,
		HP_MP& hpMp,
		Backpack& backpack,
		GameOver& gameOver,
		Coins& coins,
		LevelBGManager& levelBGManager,
		sf::Event& event,
		std::vector<NormalEnemy>& normalEnemies);//About the renew of game elements
	void renewGame(Charachter* character,
		std::vector<Npc*>& npcs, std::vector<Seller*>& sellers,
		Wand& wand,
		Seller& seller, Npc& npc,
		int& currentTileMapIndex, int& currentBackgroundIndex, GameScene& gameScene, std::vector<std::string>& tileMaps, std::vector<std::string>& backgrounds,std::vector<NormalEnemy>& normalenemies,std::vector<Bullet> &bullet,std::vector<Explosion> &ex);
}





#endif