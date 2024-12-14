#include "gameFunction.h"
#include <SFML/Graphics.hpp>

namespace gf {
	void eventHandler(sf::RenderWindow& window, Charachter& c,
        std::vector<Bullet>& bullets,
        sf::Clock& bulletClock,
        sf::Time& bulletInterval,
        Wand& wand,
        bool &gameStarted,
        bool &gameOverState,
        bool &gamePaused,
        bool & gameRestarted,
        bool & gameClosed,
        bool & victoryState,
        MainMenu& mainMenu,
        AudioManager& audioManager,
        HP_MP &hpMp,
        Backpack &backpack,
        GameOver &gameOver,
        Coins &coins,
        sf::Event &event, 
        std::vector<Npc*>& npcs,
        std::vector<Seller*>& sellers,Seller &seller,
        Npc& npc,
        int& currentTileMapIndex,
        int& currentBackgroundIndex,
        GameScene &gameScene,
        std::vector<std::string>& tileMaps,
        std::vector<std::string>& backgrounds,
        std::vector<NormalEnemy>& normalEnemys,
        std::vector<Explosion>& explosions)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab)
            {
                // �л� Wand ģʽ
                if (wand.mode == Wand::Mode::IndexColor) {
                    wand.setMode(Wand::Mode::SingleColor);
                }
                else if (wand.mode == Wand::Mode::SingleColor) {
                    wand.setMode(Wand::Mode::RandomColor);
                }
                else {
                    wand.setMode(Wand::Mode::IndexColor);
                }
                std::cout << "Wand mode switched." << std::endl;
            }

            if (victoryState)
            {
                if (gameOver.isStoryPageActive())
                {
                    if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonPressed)
                    {
                        gameOver.setStoryPageActive(false);
                    }
                }
                else
                {
                    gameOver.handleEvent(event, gameRestarted, gameClosed);

                    if (gameClosed)
                    {
                        window.close();
                    }
                }
                continue;
            }


            // ���˵��߼�
            if (!gameStarted && !gameOverState && !gamePaused)
            {
                mainMenu.handleEvent(event, gameStarted, gamePaused);
                if (gameStarted)
                {   // **********************************************************************
                    // �Ҽ���һ��bool ��ǩ ��Ŀǰд����������Ϊ�Ҹо����ֻ��ʹ��һ�� �����߼�����
                    audioManager.stopBackgroundMusic();
                    audioManager.playMusic("intro");
                    GameIntro gameIntro(window);
                    bool introFinished = false;

                    while (!introFinished && window.isOpen())
                    {
                        sf::Event introEvent;
                        while (window.pollEvent(introEvent))
                        {
                            if (introEvent.type == sf::Event::Closed)
                            {
                                window.close();
                            }
                            gameIntro.handleEvent(introEvent, introFinished);
                        }
                        window.clear();
                        gameIntro.update();
                        gameIntro.render();
                        window.display();
                    }
                    audioManager.stopBackgroundMusic();
                    audioManager.playMusic("gameplay");
                }
                //*****************************************************************************
                c.start();
            }

            // ��ͣ�߼�
            if (gameStarted && gamePaused)
            {
                mainMenu.handleEvent(event, gameStarted, gamePaused);
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    std::cout << "Escape Key Pressed. Resuming game." << std::endl;
                    gamePaused = false; // �˳���ͣ״̬
                    audioManager.resumeBackgroundMusic();
                    hpMp.resumeEffects(); // �ָ�Ч��
                }
                // ������ Back ��ť
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (mainMenu.isBackButtonClicked(mousePos))
                    {
                        gamePaused = false;
                        audioManager.resumeBackgroundMusic();
                        std::cout << "Back Button Clicked. Resuming game." << std::endl;
                    }
                }
            }





            // ��Ϸ�����߼�
            if (gameStarted && !gamePaused && !gameOverState)
            {
                backpack.handleEvent(event);
                if (event.type == sf::Event::KeyPressed)
                {
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Escape: // ��ͣ��Ϸ
                        gamePaused = true;
                        audioManager.pauseBackgroundMusic(); // ��ͣ����
                        hpMp.pauseEffects(); // ��ͣЧ��
                        std::cout << "Escape Key Pressed. Game Paused." << std::endl;
                        break;
                    //case sf::Keyboard::Q: // ���� 0.2 HP
                    //    hpMp.increaseHP(0.2f);
                    //    hpMp.update(hpMp.getHPRatio(), hpMp.getMPRatio());
                    //    break;
                    //case sf::Keyboard::W: // ���� 0.2 HP
                    //    hpMp.reduceHP(0.2f);
                    //    hpMp.update(hpMp.getHPRatio(), hpMp.getMPRatio());
                    //    if (hpMp.getHPRatio() <= EPSILON)
                    //    {
                    //        gameOverState = true;
                    //        gameStarted = false;
                    //        audioManager.pauseBackgroundMusic();
                    //        std::cout << "Game Over triggered due to HP <= 0." << std::endl;
                    //    }
                    //    break;
                    //case sf::Keyboard::E: // ������������ 0.2 HP ���� 3 ��
                    //    hpMp.reduceHPOverTime(0.2f, 3.0f);
                    //    break;
                    //case sf::Keyboard::R: // ���� 0.2 MP
                    //    hpMp.increaseMP(0.2f);
                    //    hpMp.update(hpMp.getHPRatio(), hpMp.getMPRatio());
                    //    break;
                    //case sf::Keyboard::T: // ���� 0.2 MP
                    //    hpMp.reduceMP(0.2f);
                    //    hpMp.update(hpMp.getHPRatio(), hpMp.getMPRatio());
                    //    break;
                    //case sf::Keyboard::Y: // ���� 50 ���
                    //    coins.addCoins(50);
                    //    std::cout << "Added 50 coins. Current coins: " << coins.getCoins() << std::endl;
                    //    break;
                    //case sf::Keyboard::U: // ģ�⹺����Ϊ���۳� 70 ���
                    //    if (coins.spendCoins(70))
                    //        std::cout << "Purchase successful! Spent 70 coins. Current coins: " << coins.getCoins() << std::endl;
                    //    else
                    //        std::cout << "Not enough coins to purchase." << std::endl;
                    //    break;
                    //case sf::Keyboard::I: // ������һ��
                    //    if (!levelBGManager.isLoading())
                    //    {
                    //        levelBGManager.startLoadingScreen();
                    //        std::cout << "Started loading next level." << std::endl;
                    //    }
                    //    break;
                    case sf::Keyboard::O: // ��ʾʤ��ҳ��
                        victoryState = true;
                        gameOver.showVictory();
                        gameStarted = false;
                        //******************************
                        //******************************
                        audioManager.stopBackgroundMusic();
                        audioManager.playMusic("victory");
                        //******************************
                        //******************************
                        break;
                    default:
                        break;
                    }
                }


                

            }



            // ��Ϸ�����߼�
            if (gameOverState)
            {
                gameOver.handleEvent(event, gameRestarted, gameClosed);
                if (gameRestarted)
                {
                    gameOverState = false;
                    gameStarted = true;
                    gameRestarted = false;
                    hpMp.reset();
                    coins.reset();
                    //******************************
                    //******************************
                    audioManager.stopBackgroundMusic();
                    audioManager.playMusic("gameplay");
                    std::cout << "Game Restarted. Background Music Playing." << std::endl;
                    //******************************
                    //******************************
                    renewGame(&c, npcs, sellers, wand, seller, npc, currentTileMapIndex, currentBackgroundIndex, gameScene, tileMaps, backgrounds,normalEnemys,bullets,explosions);

                }
                else if (gameClosed)
                {
                    window.close();
                }
            }

        }

        




        // ����������Ƿ���
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&(gameStarted && !gamePaused && !gameOverState))
        {
            std::cout << "Left mouse button is pressed" << std::endl;
            // ��ȡ�����λ��
            sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            // �����ӵ����ٶ�����
            sf::Vector2f bulletDirection = mousePosition - c.getMagicBallPosition();
            float length = std::sqrt(bulletDirection.x * bulletDirection.x + bulletDirection.y * bulletDirection.y);
            bulletDirection /= length; // ��һ��

            // ����ӵ������ʱ���Ƿ�ﵽ�趨ʱ����
            if (bulletClock.getElapsedTime() >= bulletInterval)
            {
                // ʹ�� Wand �������ӵ�
                wand.fire(bullets, c.getMagicBallPosition(), bulletDirection);
                wand.print_magazine();

                // �����ӵ������ʱ��
                bulletClock.restart();
            }
        }
	}



    void update(sf::RenderWindow& window,
        std::vector<Charachter*>& characters, std::vector<Npc*> &npcs,
        std::vector<Seller*> &sellers,
        std::vector<Bullet>& bullets,
        std::vector<Explosion>& explosions,
        sf::Clock& clock,
        std::vector<sf::Texture> explosionTextures,
        sf::Time& targetSpawnTime,
        int &currentTileMapIndex,
        int &currentBackgroundIndex,
        GameScene & gameScene,
        std::vector<std::string> &tileMaps,
        std::vector<std::string> &backgrounds,
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
        LevelBGManager & levelBGManager,
        std::vector<std::vector<bool>>& blocks,
        Seller& seller,
        Seller& seller2,
        Seller& seller3,
        Seller& seller4,
        Seller& seller5,
        Seller& seller6,
        Npc & npc,
        Npc& npc2,
        Npc& npc3,
        Wand& wand,
        std::vector<NormalEnemy>& normalEnemys) {

        // �����߼�
        if (!victoryState && gameStarted && !gamePaused && !gameOverState)
        {
            if (characters[0]->isOver()) {
                renewGame(characters[0],npcs,sellers,wand,seller,npc,currentTileMapIndex, currentBackgroundIndex,gameScene,tileMaps,backgrounds,normalEnemys,bullets,explosions);
                gameOverState = true;
                gameStarted = false;
                audioManager.stopBackgroundMusic();
                audioManager.playMusic("gameOver");
                std::cout << "Game Over triggered due to HP <= 0." << std::endl;
            }
            else {
                if (levelBGManager.isLoading()) {
                    levelBGManager.update(0.016f);

                }
                else {
                    hpMp.updateEffects();
                    hpMp.update(hpMp.getHPRatio(), hpMp.getMPRatio());
                    coins.updateAnimation(0.016f);
                    levelBGManager.update(0.016f);



                    //update bullet

                    for (auto& bullet : bullets)
                    {
                        bullet.update();
                    }



                    // �Ƴ����ڵ��ӵ�
                    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& bullet) {
                        return bullet.isExpired();
                        }), bullets.end());



                    // ����ӵ�����ӵ���ײ
                    for (auto& normalEnemy : normalEnemys) {
                        bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&normalEnemy, &explosions, &explosionTextures](Bullet& bullet) {

                            if (!bullet.canHitCharacter) {
                                if (bullet.sprite.getGlobalBounds().intersects(normalEnemy.getBounds())) {
                                    normalEnemy.takeDamage(bullet.damage, bullet.isCriticalHit(), bullet.damageType);
                                    // ������ըЧ����ʹ���ӵ���λ�ò������Ϸ��ƶ�200������
                                    sf::Vector2f explosionPosition = bullet.sprite.getPosition() - sf::Vector2f(130.f, 170.f);
                                    explosions.emplace_back(explosionTextures, explosionPosition);
                                    return true;
                                }
                            }
                            
                            return false;
                            }), bullets.end());
                    }

                    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&characters, &explosions, &explosionTextures](Bullet& bullet) {


                        if (bullet.canHitCharacter) {
                            if (bullet.sprite.getGlobalBounds().intersects(characters[0]->getSpriteRectBox())) {
                                characters[0]->takeDamage(bullet.damage, bullet.isCriticalHit(), bullet.damageType);
                                // ������ըЧ����ʹ���ӵ���λ�ò������Ϸ��ƶ�200������
                                sf::Vector2f explosionPosition = bullet.sprite.getPosition() - sf::Vector2f(120.f, 180.f);
                                explosions.emplace_back(explosionTextures, explosionPosition);
                                return true;
                            }
                        }



                        return false;
                        }), bullets.end());


                    int boss_num = 1;
                    if (currentTileMapIndex == 2 || currentTileMapIndex == 5 || currentTileMapIndex == 8) {
                        
                        
                        
                        
                        if (normalEnemys[0].isDead()) {
                            if (currentTileMapIndex == 8) {
                                victoryState = true;
                                gameOver.showVictory();
                                gameStarted = false;
                                //******************************
                                //******************************
                                audioManager.stopBackgroundMusic();
                                audioManager.playMusic("victory");
                            }
                            boss_num = 0;
                        }

                    }

                    // �Ƴ����ݻٵİ���
            // ���µ��˲��Ƴ������ĵ���
                    for (auto it = normalEnemys.begin(); it != normalEnemys.end();) {
                        bool shouldRemove = false;

                        if (it->isDead()) {
                            if (!it->getIsBoss()) {
                                // ��ͨС��������ֱ���Ƴ�
                                shouldRemove = true;
                            }
                            else if (it->getCurrentState() == EnemyState::DEATH) {
                                // Boss��Ҫ������������������Ƴ�
                                shouldRemove = true;
                            }
                        }

                        if (shouldRemove) {
                            it = normalEnemys.erase(it);
                        }
                        else {
                            it->update(0.016f, characters[0]->getSpriteRectBox(), characters[0]->getSpritePosition(), bullets);
                            ++it;
                        }
                    }



                    // ���±�ը����
                    for (auto& explosion : explosions) {
                        explosion.update();
                    }

                    // �Ƴ�����ɵı�ը
                    explosions.erase(std::remove_if(explosions.begin(), explosions.end(), [](Explosion& explosion) {
                        return explosion.isFinished;
                        }), explosions.end());





                    //update gameScene

                    gameScene.update(
                        0.016f,
                        characters[0]->getSpritePosition().x - 50,
                        characters[0]->getSpritePosition().y - 50,
                        characters[0]->getSpriteRectBox().getSize().x,
                        characters[0]->getSpriteRectBox().getSize().y
                    );





                    sf::Vector2f offset(gameScene.getSceneVelocity() * 0.016f);

                    sf::Vector2f tile_offset = gameScene.tileMapSprites[0].getPosition();





                    if (currentTileMapIndex <= 8) {

                        if ((currentTileMapIndex + 1) % 3 != 0 && gameScene.arrive(characters[0]->getSpritePosition().x - 50, offset.x, characters[0]->getSpriteRectBox().getSize().x, tile_offset, 4.f, blocks)) {
                            audioManager.pauseBackgroundMusic();
                            //һЩ����
                            levelBGManager.startLoadingScreen();
                            npcs.clear();
                            sellers.clear();
                            normalEnemys.clear();
                            characters[0]->clearHurtType();
                            explosions.clear();
                            bullets.clear();
                            if (currentTileMapIndex == 0) {

                                NormalEnemy enemy3(
                                    sf::Vector2f(2000.f, 500.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::Ghost),  // �������ͼ·��
                                    50.f,                             // spriteSize
                                    80,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    3,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    3,                                // idleFrameCount (�������鶯��֡������)
                                    5,                                // walkFrameCount
                                    4,                               // attackFrameCount
                                    2,                                // injuryFrameCount
                                    5,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy3.setScale(1, 1);
                                enemy3.setGameScene(&gameScene);
                                normalEnemys.push_back(enemy3);


                                NormalEnemy enemy4(
                                    sf::Vector2f(1600.f, 500.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::Ghost),  // �������ͼ·��
                                    50.f,                             // spriteSize
                                    80,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    3,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    3,                                // idleFrameCount (�������鶯��֡������)
                                    5,                                // walkFrameCount
                                    4,                               // attackFrameCount
                                    2,                                // injuryFrameCount
                                    5,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy4.setScale(1, 1);
                                enemy4.setGameScene(&gameScene);
                                normalEnemys.push_back(enemy4);

                                sellers.push_back(&seller2);
                                characters[0]->reSetSellers(sellers);
                            }
                            else if (currentTileMapIndex == 1) {


                                NormalEnemy enemy5(
                                    sf::Vector2f(1300.f, 400.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::BossEye),  // �������ͼ·��
                                    190.f,                             // spriteSize
                                    500,                               // �ϵ͵�����ֵ
                                    200.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    3,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    6,                                // idleFrameCount (�������鶯��֡������)
                                    32,                                // walkFrameCount
                                    32,                               // attackFrameCount
                                    9,                                // injuryFrameCount
                                    9,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy5.setScale(0.5, 0.5);
                                enemy5.setGameScene(&gameScene);
                                //enemy5.setBoss(true);
                                normalEnemys.push_back(enemy5);
                            }
                            else if (currentTileMapIndex == 3) {

                                NormalEnemy enemy8(
                                    sf::Vector2f(1900.f, 500.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::firedog),  // �������ͼ·��
                                    64.f,                             // spriteSize
                                    80,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    1,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    8,                                // idleFrameCount (�������鶯��֡������)
                                    6,                                // walkFrameCount
                                    9,                               // attackFrameCount
                                    15,                                // injuryFrameCount
                                    5,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy8.setScale(2, 2);
                                enemy8.setGameScene(&gameScene);


                                NormalEnemy enemy9(
                                    sf::Vector2f(1500.f, 500.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::firedog),  // �������ͼ·��
                                    64.f,                             // spriteSize
                                    80,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    1,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    8,                                // idleFrameCount (�������鶯��֡������)
                                    6,                                // walkFrameCount
                                    9,                               // attackFrameCount
                                    15,                                // injuryFrameCount
                                    5,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy9.setScale(2, 2);
                                enemy9.setGameScene(&gameScene);

                                normalEnemys.push_back(enemy8);
                                normalEnemys.push_back(enemy9);
                                sellers.push_back(&seller4);
                                characters[0]->reSetSellers(sellers);
                            }
                            else if (currentTileMapIndex == 4) {
                                NormalEnemy enemy10(
                                    sf::Vector2f(1300.f, 400.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::Bossdragon),  // �������ͼ·��
                                    370.f,                             // spriteSize
                                    600,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    1,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    10,                                // idleFrameCount (�������鶯��֡������)
                                    10,                                // walkFrameCount
                                    7,                               // attackFrameCount
                                    10,                                // injuryFrameCount
                                    10,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy10.setScale(0.5, 0.5);
                                enemy10.setGameScene(&gameScene);
                                //enemy10.setBoss(true);
                                normalEnemys.push_back(enemy10);
                            }
                            else if(currentTileMapIndex == 6) {


                                NormalEnemy enemy13(
                                    sf::Vector2f(1900.f, 670),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::iceslime),  // �������ͼ·��
                                    20.f,                             // spriteSize
                                    80,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    2,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    4,                                // idleFrameCount (�������鶯��֡������)
                                    4,                                // walkFrameCount
                                    5,                               // attackFrameCount
                                    4,                                // injuryFrameCount
                                    4,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy13.setScale(4, 4);
                                enemy13.setGameScene(&gameScene);


                                NormalEnemy enemy14(
                                    sf::Vector2f(1400.f, 750.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::iceslime),  // �������ͼ·��
                                    20.f,                             // spriteSize
                                    80,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    2,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    4,                                // idleFrameCount (�������鶯��֡������)
                                    4,                                // walkFrameCount
                                    5,                               // attackFrameCount
                                    4,                                // injuryFrameCount
                                    4,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy14.setScale(4, 4);
                                enemy14.setGameScene(&gameScene);

                                normalEnemys.push_back(enemy13);
                                normalEnemys.push_back(enemy14);
                                sellers.push_back(&seller6);
                                characters[0]->reSetSellers(sellers);
                            }



                            else if (currentTileMapIndex == 7) {
                                NormalEnemy enemy15(
                                    sf::Vector2f(1300.f, 520.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::Bossmonster),  // �������ͼ·��
                                    400.f,                             // spriteSize
                                    700,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ���mo��ʱ��
                                    2,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    20,                                // idleFrameCount (�������鶯��֡������)
                                    19,                                // walkFrameCount
                                    20,                               // attackFrameCount
                                    20,                                // injuryFrameCount
                                    20,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy15.setScale(0.5, 0.5);
                                enemy15.setGameScene(&gameScene);
                                //enemy15.setBoss(true);
                                normalEnemys.push_back(enemy15);
                            }
                            audioManager.resumeBackgroundMusic();

                            currentTileMapIndex++;
                            gameScene.loadTileMaps(tileMaps[currentTileMapIndex]);
                            std::cout << "load new tile map" << std::endl;
                            if (currentTileMapIndex % 3 == 0) {
                                currentBackgroundIndex++;
                            }

                        }

                        if ((currentTileMapIndex + 1) % 3 == 0 && boss_num == 0) {

                            currentTileMapIndex++;
                            if (currentTileMapIndex > 8) {
                                std::cout << "reach the last tilemap" << std::endl;

                                
                            }
                            if (currentTileMapIndex <= 8) {

                                gameScene.loadTileMaps(tileMaps[currentTileMapIndex]);
                            }
                            std::cout << "load new tile map" << std::endl;
                            if (currentTileMapIndex % 3 == 0 && currentTileMapIndex <= 8) {
                                currentBackgroundIndex++;

                            }
                            else if (currentTileMapIndex > 8) {
                                currentBackgroundIndex = 3;
                            }
                            audioManager.pauseBackgroundMusic();

                            if (currentTileMapIndex == 3) {
                                NormalEnemy enemy6(
                                    sf::Vector2f(1900.f, 500.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::fireimp),  // �������ͼ·��
                                    40.f,                             // spriteSize
                                    80,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    1,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    3,                                // idleFrameCount (�������鶯��֡������)
                                    6,                                // walkFrameCount
                                    5,                               // attackFrameCount
                                    2,                                // injuryFrameCount
                                    4,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy6.setScale(1, 1);
                                enemy6.setGameScene(&gameScene);


                                NormalEnemy enemy7(
                                    sf::Vector2f(1600.f, 500.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::fireimp),  // �������ͼ·��
                                    40.f,                             // spriteSize
                                    80,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    3,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    1,                                // idleFrameCount (�������鶯��֡������)
                                    6,                                // walkFrameCount
                                    5,                               // attackFrameCount
                                    2,                                // injuryFrameCount
                                    4,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy7.setScale(1, 1);
                                enemy7.setGameScene(&gameScene);
                                normalEnemys.push_back(enemy6);
                                normalEnemys.push_back(enemy7);
                            }
                            else if (currentTileMapIndex == 6) {
                                NormalEnemy enemy11(
                                    sf::Vector2f(1600.f, 500.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::icemonster),  // �������ͼ·��
                                    160.f,                             // spriteSize
                                    80,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    2,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    6,                                // idleFrameCount (�������鶯��֡������)
                                    6,                                // walkFrameCount
                                    6,                               // attackFrameCount
                                    6,                                // injuryFrameCount
                                    6,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy11.setScale(1, 1);
                                enemy11.setGameScene(&gameScene);


                                NormalEnemy enemy12(
                                    sf::Vector2f(2000.f, 500.f),      // position - ����Ļ�Ҳ�
                                    NormalEnemy::getPathByType(EnemyType::icemonster),  // �������ͼ·��
                                    160.f,                             // spriteSize
                                    80,                               // �ϵ͵�����ֵ
                                    150.f,                            // �Ͽ���ƶ��ٶ�
                                    8,                                // �ϵ͵Ĺ����˺�
                                    0.6f,                             // �϶̵Ĺ�����ȴ
                                    6.f,                              // ��С���ӵ��뾶
                                    180.f,                            // �Ͽ���ӵ��ٶ�
                                    1.5f,                             // �϶̵��ӵ����ʱ��
                                    2,                                // �ӵ��˺����� (Poison��������)
                                    800.f,                            // ��С��Ѳ�߿��
                                    850.f,                            // ��С��Ѳ�߸߶�
                                    6,                                // idleFrameCount (�������鶯��֡������)
                                    6,                                // walkFrameCount
                                    6,                               // attackFrameCount
                                    6,                                // injuryFrameCount
                                    6,                               // deathFrameCount
                                    false                            // ����ʾѲ������
                                );
                                enemy12.setScale(1, 1);
                                enemy12.setGameScene(&gameScene);

                                normalEnemys.push_back(enemy11);
                                normalEnemys.push_back(enemy12);

                            }

                            characters[0]->clearHurtType();
                            explosions.clear();
                            bullets.clear();
                            switch (currentTileMapIndex)
                            {


                            case 3:
                                sellers.push_back(&seller3);
                                npcs.push_back(&npc2);
                                characters[0]->reSetSellers(sellers);
                                characters[0]->reSetNpcs(npcs);

                                break;


                            case 6:
                                sellers.push_back(&seller5);
                                npcs.push_back(&npc3);
                                characters[0]->reSetSellers(sellers);
                                characters[0]->reSetNpcs(npcs);

                                break;
                            default:
                                break;
                            }
                            levelBGManager.startLoadingScreen();
                            audioManager.resumeBackgroundMusic();


                        }

                    }



                    if (currentTileMapIndex % 3 == 0 && currentTileMapIndex <= 8) {

                        if (currentBackgroundIndex > 2) {
                            std::cout << "reach the last background" << std::endl;
                        }

                        if (currentBackgroundIndex <= 2) {
                            gameScene.loadBackgrounds(backgrounds[currentBackgroundIndex]);
                        }


                    }





                    //if (hpMp.getHPRatio() <= EPSILON)
                    //{
                    //    gameOverState = true;
                    //    gameStarted = false;
                    //    audioManager.pauseBackgroundMusic();
                    //}









                    for (Charachter* character : characters) {
                        character->update(0.016f);
                    }

                    for (Npc* npc : npcs) {
                        npc->update();

                    }

                  


                    for (Seller* seller : sellers) {
                        seller->update();
                    }
                }
                
                //std::cout << "updateInteractionWithSellers222" <<& sellers<< std::endl;
            }



            
        }



    }


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
        sf::Event &event,
        std::vector<NormalEnemy> &normalEnemies
        )
    {
        window.clear(sf::Color::Black);


        //std::cout << "die"<<gameOverState << std::endl;
        // ��Ⱦ�߼�
        if (victoryState)
        {
            gameOver.render();
            gameOver.handleEvent(event, gameRestarted, gameClosed);
        }
        else if (!gameStarted && !gameOverState)
        {
            mainMenu.render(false, false);
        }
        else if (gameStarted && !gamePaused && !gameOverState)
        {
            gameScene.render(window);   // ????��??��??TileMap

            levelBGManager.render();
            if (!levelBGManager.isLoading())
            {
                gameScene.render(window);   // ????��??��??TileMap

                hpMp.render();
                coins.render();

                // �����ӵ�
                for (auto& bullet : bullets)
                {
                    window.draw(bullet.sprite);
                }


                // ���Ʊ�ը����
                for (auto& explosion : explosions) {
                    explosion.render(window);
                }








                for (Npc* npc : npcs) {
                    npc->render(window);
                }
                for (Seller* seller : sellers) {
                    seller->render(window);
                }

                // ��Ⱦ����
                for ( auto& enemy : normalEnemies) {
                    enemy.render(window);
                }


                for (Charachter* character : characters) {
                    character->render(window);
                }




                backpack.render();
            }
        }
        else if (gamePaused)
        {
            //levelBGManager.render();
            gameScene.render(window);   // ????��??��??TileMap

            hpMp.render();
            coins.render();

            // �����ӵ�
            for (auto& bullet : bullets)
            {
                window.draw(bullet.sprite);
            }


            // ���Ʊ�ը����
            for (auto& explosion : explosions) {
                explosion.render(window);
            }



            for (Npc* npc : npcs) {
                npc->render(window);
            }
            for (Seller* seller : sellers) {
                seller->render(window);
            }


            // ��Ⱦ����
            for ( auto& enemy : normalEnemies) {
                enemy.render(window);
            }


            //for (Charachter* character : characters) {
            //    character->render(window);
            //}

            backpack.render();
            mainMenu.render(true, true);
        }
        else if (gameOverState)
        {
            std::cout << "gameOverState" << std::endl;
            gameOver.render();
            levelBGManager.onPlayerDeath();
            }



       



        window.display();






       
    }


    void renewGame(Charachter *character,
        std::vector<Npc*>& npcs, std::vector<Seller*>& sellers, 
        Wand& wand, 
        Seller& seller, Npc& npc,
        int& currentTileMapIndex,int& currentBackgroundIndex,GameScene& gameScene,std::vector<std::string>& tileMaps,std::vector<std::string>& backgrounds,std::vector<NormalEnemy> & normalenemies, std::vector<Bullet>& bullet, std::vector<Explosion>& ex) {
        
        ex.clear();
        
        character->Init(sf::Vector2f(800.f, 500.f));
        character->start();
        currentTileMapIndex = 0;
        currentBackgroundIndex = 0;
        gameScene.loadTileMaps(tileMaps[currentTileMapIndex]);
        gameScene.loadBackgrounds(backgrounds[currentBackgroundIndex]);
        wand.setSingleTexture(0);
        sellers.clear();
        npcs.clear();
        sellers.push_back(&seller);
        npcs.push_back(&npc);
        gameScene.isDroped = false;
        normalenemies.clear();
        bullet.clear();
        NormalEnemy enemy1(
            sf::Vector2f(1600.f, 500.f),      // position - ����Ļ�Ҳ�
            NormalEnemy::getPathByType(EnemyType::BigEye),  // �������ͼ·��
            64.f,                             // spriteSize
            80,                               // �ϵ͵�����ֵ
            150.f,                            // �Ͽ���ƶ��ٶ�
            8,                                // �ϵ͵Ĺ����˺�
            0.6f,                             // �϶̵Ĺ�����ȴ
            6.f,                              // ��С���ӵ��뾶
            180.f,                            // �Ͽ���ӵ��ٶ�
            1.5f,                             // �϶̵��ӵ����ʱ��
            3,                                // �ӵ��˺����� (Poison��������)
            800.f,                            // ��С��Ѳ�߿��
            850.f,                            // ��С��Ѳ�߸߶�
            20,                                // idleFrameCount (�������鶯��֡������)
            13,                                // walkFrameCount
            13,                               // attackFrameCount
            4,                                // injuryFrameCount
            15,                               // deathFrameCount
            false                            // ����ʾѲ������
        );
        enemy1.setScale(1, 1);
        enemy1.setGameScene(&gameScene);
        normalenemies.push_back(enemy1);



        NormalEnemy enemy2(
            sf::Vector2f(1800.f, 500.f),      // position - ����Ļ�Ҳ�
            NormalEnemy::getPathByType(EnemyType::BigEye),  // �������ͼ·��
            64.f,                             // spriteSize
            80,                               // �ϵ͵�����ֵ
            150.f,                            // �Ͽ���ƶ��ٶ�
            8,                                // �ϵ͵Ĺ����˺�
            0.6f,                             // �϶̵Ĺ�����ȴ
            6.f,                              // ��С���ӵ��뾶
            180.f,                            // �Ͽ���ӵ��ٶ�
            1.5f,                             // �϶̵��ӵ����ʱ��
            3,                                // �ӵ��˺����� (Poison��������)
            800.f,                            // ��С��Ѳ�߿��
            850.f,                            // ��С��Ѳ�߸߶�
            20,                                // idleFrameCount (�������鶯��֡������)
            13,                                // walkFrameCount
            13,                               // attackFrameCount
            4,                                // injuryFrameCount
            15,                               // deathFrameCount
            false                            // ����ʾѲ������
        );
        enemy2.setScale(1, 1);
        enemy2.setGameScene(&gameScene);
        normalenemies.push_back(enemy2);

    }
    
}