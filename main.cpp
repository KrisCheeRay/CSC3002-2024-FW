#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "gameFunction.h"
#include "Setting.h"
#include <vector>



int main()
{
    Setting setting(1600, 1000);
    sf::RenderWindow window(sf::VideoMode(setting.getWindowWidth(), setting.getWindowHeight()), "Game");
    window.setFramerateLimit(setting.getFpsLimit());

    // 创建音频管理对象
    AudioManager audioManager;

    // 创建各个UI元素的实例
    MainMenu mainMenu(window);
    HP_MP hpMp(window);
    GameOver gameOver(window);
    Backpack backpack(window);
    Coins coins(window);
    LevelBGManager levelBGManager(window);


    // 初始化游戏状态
    bool gameStarted = false;
    bool gamePaused = false;
    bool gameOverState = false;
    bool gameRestarted = false;
    bool gameClosed = false;
    bool victoryState = false;
    


    audioManager.playMusic("mainMenu");



    Npc npc(32,32,90,90, "Resources\\Image\\NPC\\sprite sheets\\elementals\\leaf_ranger.png",sf::Vector2f(520,820), "Listen well, young seeker.\n\nThe world is woven by ancient forces.\nEvery land, every stream, every wind follows\n its own path, guided by the laws of nature.\nYet deeper still, hidden within these laws, \nlies a greater mystery—one that calls to those \nwith the wisdom to hear.\n\nThree powers rule this world:\nNature, Magic, and Technology.\nNature is the source, shaping life and death, \ngiving purpose to all things.\nMagic lies beyond, unseen but ever - changing, \ncapable of bending the very fabric of existence.\nTechnology, born of knowledge, lets us shape \nthe world itself.\n\nBut beyond all these, there is the \nseed of THE ONE.It is the root, the first spark \nof life and power, the source of all things.\nIt is not found in the land, nor the sky, \nnor in any known form.\nIt lies in the heart of the world—and within \nyour own heart.\n\nBut be warned—this quest is not for the faint of \nheart.The path is fraught with trials.\nOnly the wise, the patient, and the humble\nmay find the way.");
    Npc npc2(32, 32, 90, 90, "Resources\\Image\\NPC\\sprite sheets\\elementals\\fire_knight.png", sf::Vector2f(435, 250), "Listen well, young seeker.\n\nThe world is woven by ancient forces.\nEvery land, every stream, every wind\nhas its own path,\nguided by nature's laws.\n\nYet deeper, within these laws,\nlies a greater mystery.\nIt calls to those with wisdom.\n\nBut beyond these, there's the seed of THE ONE.\nIt's the root, the first spark of life and power,\nthe source of all.\n\nNot found in land or sky,\nnor in any known form.\nIt lies in the heart of the world—\nand within your own heart.\n\nSeek it not with greed or haste.\nOnly when your soul is calm,\nyour mind clear, will it reveal itself.\n\nBut be warned: this quest is not for the faint.\nThe path is full of trials.\nOnly the wise, the patient, and the humble\nmay find the way.");
    Npc npc3(32, 32, 90, 90, "Resources\\Image\\NPC\\sprite sheets\\elementals\\water_priestess.png", sf::Vector2f(420, 440), "Ha! You've come far, haven't you?\nMany would have faltered, but not you, brave \nsoul.Now, at the edge of all things,\nyou stand on the precipice of your legend.\n\nBut now... the moment you've been waiting for.\nFeel the thrill in the air,\nthe pulse of destiny?\n\nIt's not in the gentle winds or calm waters.\nIt's in the storm, the battle, the challenge!\nThe true hero is forged in the fire of battle,\nfacing insurmountable odds.\n\nDo not hesitate!\nThe world is yours to shape,\nthe destiny of all within your grasp.\n\nIn this final clash, you're not alone.\nYou carry your trials, lessons, will.\nTrust in your strength, trust in your heart,\nand know you're the author of your saga.\n\nSo, go forward.\nFight as though the stars watch your every move.\nYour story will be written in flames and blood,\ntriumphs and sacrifices.\n\nBe the hero you were meant to be.\nLet the world remember your name,\nfor it will echo through the ages!");

    std::vector<Npc*> npcs;
    npcs.push_back(&npc);

    Seller seller(80, 80, 120, 120, "Resources\\Image\\NPC\\seller\\Gipsy _spritesheet.png", sf::Vector2f(1500, 810), &window);
    Seller seller2(80, 80, 120, 120, "Resources\\Image\\NPC\\seller\\Gipsy _spritesheet.png", sf::Vector2f(1600, 570), &window);
    Seller seller3(80, 80, 120, 120, "Resources\\Image\\NPC\\seller\\Gipsy _spritesheet.png", sf::Vector2f(800, 230), &window);
    Seller seller4(80, 80, 120, 120, "Resources\\Image\\NPC\\seller\\Gipsy _spritesheet.png", sf::Vector2f(1600, 360), &window);
    Seller seller5(80, 80, 120, 120, "Resources\\Image\\NPC\\seller\\Gipsy _spritesheet.png", sf::Vector2f(1450, 520), &window);
    Seller seller6(80, 80, 120, 120, "Resources\\Image\\NPC\\seller\\Gipsy _spritesheet.png", sf::Vector2f(1660, 315), &window);


    std::vector<Seller*> sellers;
    sellers.push_back(&seller);
std::cout << &seller << std::endl;

    
    std::vector<Charachter *> characters;
    Charachter character(200, 100,npcs,sellers,&hpMp,&coins);
    characters.push_back(&character);


     seller.setCharacter(&character);


    //Δtime
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);



    // Scene Manager
    std::vector<std::vector<bool>> blocks(1000, std::vector<bool>(1000, false));
    GameScene gameScene(window, blocks);
    std::vector<std::string> backgrounds =
    {
        "Resources\\Maps\\Background\\DarkForestBackgroungbe.png",
        "Resources\\Maps\\Background\\VolcanoBackground.png",
        "Resources\\Maps\\Background\\GlacierMountainBackground.png"
    };

    std::vector<std::string> tileMaps =
    {
        "Resources\\TileMap\\poison_map\\poison_map1.png",
        "Resources\\TileMap\\poison_map\\poison_map2.png",
        "Resources\\TileMap\\poison_map\\poison_boss_map.png",

        "Resources\\TileMap\\fire_map\\fire_map1.png",
        "Resources\\TileMap\\fire_map\\fire_map2.png",
        "Resources\\TileMap\\fire_map\\fire_boss_map.png",

         "Resources\\TileMap\\snowfield_map\\snowfield_map1.png",
        "Resources\\TileMap\\snowfield_map\\snowfield_map2.png",
        "Resources\\TileMap\\snowfield_map\\snowfield_boss_map.png"
    };
    int currentBackgroundIndex = 0;
    int currentTileMapIndex = 0;


    //gameScene.loadBackgrounds(backgrounds[gameScene.getCurrentBackgroundIndex()]);
    //gameScene.loadTileMaps(tileMaps[gameScene.getCurrentTileMapIndex()]);
    gameScene.loadBackgrounds(backgrounds[currentBackgroundIndex]);
    gameScene.loadTileMaps(tileMaps[currentTileMapIndex]);

    gameScene.SetCharacter(&character);







    // 创建一个子弹容器
    std::vector<Bullet > bullets;

    // 创建一个靶子容器
    std::vector<NormalEnemy> enemies;
    NormalEnemy enemy1(
        sf::Vector2f(1600.f, 500.f),      // position - 在屏幕右侧
        NormalEnemy::getPathByType(EnemyType::BigEye),  // 幽灵的贴图路径
        30.f,                             // spriteSize
        80,                               // 较低的生命值
        150.f,                            // 较快的移动速度
        8,                                // 较低的攻击伤害
        0.6f,                             // 较短的攻击冷却
        6.f,                              // 较小的子弹半径
        180.f,                            // 较快的子弹速度
        1.5f,                             // 较短的子弹存活时间
        3,                                // 子弹伤害类型 (Poison毒性类型)
        800.f,                            // 较小的巡逻宽度
        850.f,                            // 较小的巡逻高度
        20,                                // idleFrameCount (根据幽灵动画帧数调整)
        13,                                // walkFrameCount
        13,                               // attackFrameCount
        4,                                // injuryFrameCount
        15,                               // deathFrameCount
        false                            // 不显示巡逻区域
    );
    enemy1.setScale(1, 1);
    enemy1.setGameScene(&gameScene);
    enemies.push_back(enemy1);



    NormalEnemy enemy2(
        sf::Vector2f(2000.f, 500.f),      // position - 在屏幕右侧
        NormalEnemy::getPathByType(EnemyType::BigEye),  // 幽灵的贴图路径
        30.f,                             // spriteSize
        80,                               // 较低的生命值
        150.f,                            // 较快的移动速度
        8,                                // 较低的攻击伤害
        0.6f,                             // 较短的攻击冷却
        6.f,                              // 较小的子弹半径
        180.f,                            // 较快的子弹速度
        1.5f,                             // 较短的子弹存活时间
        3,                                // 子弹伤害类型 (Poison毒性类型)
        800.f,                            // 较小的巡逻宽度
        850.f,                            // 较小的巡逻高度
        20,                                // idleFrameCount (根据幽灵动画帧数调整)
        13,                                // walkFrameCount
        13,                               // attackFrameCount
        4,                                // injuryFrameCount
        15,                               // deathFrameCount
        false                            // 不显示巡逻区域
    );
    enemy2.setScale(1, 1);
    enemy2.setGameScene(&gameScene);
    enemies.push_back(enemy2);



   




    

    




    


    



    // 创建一个爆炸容器
    std::vector<Explosion > explosions;
    // 加载爆炸动画帧
    std::vector<sf::Texture> explosionTextures = loadTextures(".", 59); // 假设有59帧动画


    // 创建一个计时器
    sf::Clock clock;
    sf::Time targetSpawnTime = sf::seconds(3.f);


    // 创建一个子弹发射计时器
    sf::Clock bulletClock;
    sf::Time bulletInterval = sf::seconds(0.2f); // 每0.2秒发射一颗子弹




    // 创建一个 Wand 对象并装载子弹
    Wand wand(false, 1, 0, 0, 100.0, 10.0, 4, 0.0);
    wand.singleTextureChoice = 0;
    for (int i = 0; i < 4; ++i) {
        Bullet bullet(false);
        bullet.setTexture(i);
        wand.add_bullet(bullet);

    }

    wand.print_magazine();
    wand.setMode(Wand::Mode::RandomColor);

  
    seller.setGameScene(&gameScene);
    seller.setWand(&wand);

    seller2.setGameScene(&gameScene);
    seller2.setWand(&wand);
    seller2.setCharacter(&character);

    seller3.setGameScene(&gameScene);
    seller3.setWand(&wand);
    seller3.setCharacter(&character);


    seller4.setGameScene(&gameScene);
    seller4.setWand(&wand);
    seller4.setCharacter(&character);


    seller5.setGameScene(&gameScene);
    seller5.setWand(&wand);
    seller5.setCharacter(&character);


    seller6.setGameScene(&gameScene);
    seller6.setWand(&wand);
    seller6.setCharacter(&character);


    npc.setGameScene(&gameScene);
    npc2.setGameScene(&gameScene);
    npc3.setGameScene(&gameScene);


    while (window.isOpen())
    {
        sf::Event event;

        //Player's input handling
        gf::eventHandler(window,character,bullets,bulletClock,bulletInterval, wand,gameStarted,gameOverState,gamePaused,gameRestarted,gameClosed,victoryState,mainMenu,audioManager,hpMp,backpack,gameOver,coins,event,npcs,sellers,seller,npc,currentTileMapIndex,currentBackgroundIndex,gameScene,tileMaps,backgrounds,enemies,explosions);

        //Game's elements and status updating
        gf::update(window, characters, npcs, sellers,bullets,explosions,clock,explosionTextures,targetSpawnTime,currentTileMapIndex,currentBackgroundIndex,gameScene,tileMaps,backgrounds,gameStarted,gameOverState,gamePaused,gameRestarted
        ,gameClosed,victoryState,mainMenu,audioManager,hpMp,backpack,gameOver,coins,levelBGManager,blocks,seller,seller2,seller3,seller4,seller5,seller6,npc,npc2,npc3,wand,enemies);

        //Screeen updating and elements rendering
        gf::render(window, characters, npcs,sellers,bullets,explosions,gameScene, gameStarted, gameOverState, gamePaused, gameRestarted
            , gameClosed, victoryState, mainMenu, audioManager, hpMp, backpack, gameOver, coins, levelBGManager,event,enemies);
    }

    return 0;
}