#include "GameIntro.h"
#include <iostream>

GameIntro::GameIntro(sf::RenderWindow& window) : window(window), finished(false), currentPage(Page::BACKGROUND_INFO)
{
    if (!backgroundTexture.loadFromFile("Resources\\Image\\Background\\Level_1.png"))
    {
        throw std::runtime_error("Failed to load background image");
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );


    if (!font.loadFromFile("Resources\\Image\\Font\\font.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }


    //introText.setFont(font);
    //introText.setString("Welcome    to    the    Game!");
    //introText.setCharacterSize(50);
    //introText.setOutlineThickness(2.0f);
    //introText.setFillColor(sf::Color::Red);
    //introText.setPosition(window.getSize().x / 2 - introText.getGlobalBounds().width / 2, 30.f);

    if (!font2.loadFromFile("Resources\\Image\\Font\\28177148754.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    backgroundInfoText.setFont(font2);
    backgroundInfoText.setString("Above vast skies, the roc takes flight,\nIts mighty wings eclipse the light.\nWith countless birds, it soars and sweeps,\nThrough boundless air and endless deeps.\n\nIt strikes the sea with thunder¡¯s roar,\nThree thousand leagues, the waters soar.\nUpon the wind¡¯s spiraling tide,\nNine myriad leagues, it climbs the skies.\n\nThrough cloud and storm, o¡¯er azure dome,\nIt crosses oceans vast, its home.\nAt last, it rests, and eggs are laid,\nThree seeds of fate, creation's braid.\n\nOne egg falls, its shell does break,\nAnd blood flows forth, a crimson lake.\nFor seven nights and seven days,\nLife and death find ancient ways.\n\nThe yolk flows west, a frozen sprawl,\nA thousand leagues of icy thrall.\nThe yolk flows east, volcanic flame,\nTen thousand leagues of molten claim.\n\nThe lightest air ascends, the skies,\nThe heaviest sinks, where earth shall rise.\nFrom fragments torn, the world takes form,\nWith rivers mild and mountains warm.\n\nFrom first egg¡¯s shell, the spirit wakes,\nAnd nature stirs, the ground it shapes.");
    backgroundInfoText.setCharacterSize(20);
    backgroundInfoText.setFillColor(sf::Color(205, 192, 176));
    backgroundInfoText.setOutlineThickness(2.f);
    backgroundInfoText.setPosition(window.getSize().x / 4 - backgroundInfoText.getGlobalBounds().width / 2, 30);

    backgroundInfoText2.setFont(font2);
    backgroundInfoText2.setString("Beasts and trees, the valleys, hills,\nBorn of will and nature¡¯s skills.\n\nThe second cracks, a god appears,\nMagic born to soothe and sear.\nIt gifts each thing a soul profound,\nGold¡¯s pure glow, or earth¡¯s dark mound.\n\nYet magic bends and breaks the law,\nThe natural god stands firm in awe.\nTheir voices clash, their truths collide,\nA vision lost where both abide.\n\nThe final egg, the last divine,\nFrom it springs a reasoned mind.\nThe god of tools, of thought, of lore,\nBrings wisdom vast, to nature¡¯s core.\n\nIt writes their tale, from start to end,\nIn epic verse, where truths ascend.\nThe Kalevala, a world¡¯s first song,\nOf gods at odds, and lives prolonged.\n\nFor countless years, their works remain,\nA silent world through time¡¯s domain.\nUntil a hero, bold and pure,\nArises with a heart unsure.\n\nHe reads the Emerald Scroll¡¯s decree,\n¡°To seek the One, through land and sea.\nAs above, so below,\nIn wisdom¡¯s light, the truth shall grow.¡±\n\n¡°Thus holds the strength of all that bends,\nA power to shape, a force to end.¡±\nWith steps that span a thousand lands,\nHe seeks the seed with steadfast hands.");
    backgroundInfoText2.setFillColor(sf::Color(205, 192, 176));
    backgroundInfoText2.setOutlineThickness(2.f);
    backgroundInfoText2.setPosition(window.getSize().x / 4 - backgroundInfoText.getGlobalBounds().width / 2+800, 30);
    backgroundInfoText2.setCharacterSize(20);


    continueText.setFont(font);
    continueText.setString("Press    any    key    or    click    to    continue...");
    continueText.setCharacterSize(30);
    continueText.setFillColor(sf::Color::Red);
    continueText.setOutlineThickness(2.0f);
    continueText.setPosition(window.getSize().x / 4 - continueText.getGlobalBounds().width / 2+20, window.getSize().y / 2 + 400.f);


    aText.setFont(font);
    aText.setString("A :  Walk  Left");
    aText.setCharacterSize(25);
    aText.setFillColor(sf::Color::Black);
    aText.setOutlineColor(sf::Color::White);
    aText.setOutlineThickness(2.f);
    aText.setPosition(60.f, window.getSize().y / 5);



    for (int i = 1; i <=6; i++) {
        sf::Texture t;
        t.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_walk_"+std::to_string(i)+".png");
        walkTextures.push_back(t);
    }
    aSprite.setTexture(walkTextures[0]);
    dSprite.setTexture(walkTextures[0]);
    aSprite.setScale(-1, 1);
    aSprite.setPosition(60.f+200, window.getSize().y / 5+50);
    walk = 0;


    dText.setFont(font);
    dText.setString("D :  Walk  Right");
    dText.setCharacterSize(25);
    dText.setFillColor(sf::Color::Black);
    dText.setOutlineColor(sf::Color::White);
    dText.setOutlineThickness(2.f);
    dText.setPosition(360.f, window.getSize().y / 5);
    dSprite.setPosition(360.f, window.getSize().y / 5+50);


    spaceText.setFont(font);
    spaceText.setString("Space :  Jump  High\n\nTAB : Switch \nShooting  Mode/\nRandom  Mode/\nFixed  Mode/\nUnique  Mode");
    spaceText.setCharacterSize(25);
    spaceText.setFillColor(sf::Color::Black);
    spaceText.setOutlineColor(sf::Color::White);
    spaceText.setOutlineThickness(2.f);
    spaceText.setPosition(60.f, window.getSize().y / 5 + 250);



    enterText.setFont(font);
    enterText.setString("Enter/K :  \nMelee  /  Rushing  Attack");
    enterText.setCharacterSize(25);
    enterText.setFillColor(sf::Color::Black);
    enterText.setOutlineColor(sf::Color::White);
    enterText.setOutlineThickness(2.f);
    enterText.setPosition(360.f, window.getSize().y / 5 + 250);
    for (int i = 1; i <= 5; i++) {
        sf::Texture t;
        t.loadFromFile("Resources\\Image\\Charachter\\cultist_priest_attack_" + std::to_string(i) + ".png");
        enterTextures.push_back(t);
    }
    enterSprite.setTexture(enterTextures[0]);
    enterSprite.setPosition(360.f + 50, window.getSize().y / 5 + 300);
    enter = 0;





    magicBallText.setFont(font);
    magicBallText.setString("Magic Ball : \nThe  Emission  \nSource  Of  Magic  \nBullets");
    magicBallText.setCharacterSize(25);
    magicBallText.setFillColor(sf::Color::Black);
    magicBallText.setOutlineColor(sf::Color::White);
    magicBallText.setOutlineThickness(2.f);
    magicBallText.setPosition(60.f, window.getSize().y / 5 + 500.f);
    for (int i = 1; i <= 41; ++i) {
        sf::Texture texture;
        std::string filePath = "Resources//Image//Portal//Portal_100x100px" + std::to_string(i) + ".png";
        if (texture.loadFromFile(filePath)) {
            magicBallTextures.push_back(texture);
        }
        else {
            std::cerr << "Failed to load texture: " << filePath << std::endl;
        }
    }
    magicBallSprite.setTexture(magicBallTextures[0]);
    magicBallSprite.setScale(2, 2);
    magicBallSprite.setPosition(60.f , window.getSize().y / 5 + 600.f);
    magicBall = 0;


    escText.setFont(font);
    escText.setString("ESC : Pause Game");
    escText.setCharacterSize(25);
    escText.setFillColor(sf::Color::Black);
    escText.setOutlineColor(sf::Color::White);
    escText.setOutlineThickness(2.f);
    escText.setPosition(360.f, window.getSize().y / 5. + 500.f);

    startText.setFont(font);
    startText.setString("Press    any    key    or    click    to    START...");
    startText.setCharacterSize(40);
    startText.setFillColor(sf::Color::Red);
    startText.setOutlineThickness(2.0f);
    startText.setPosition(window.getSize().x / 2 - startText.getGlobalBounds().width / 2, window.getSize().y / 2 + 400.f);

    controlText.setFont(font);
    controlText.setString("Character  Control");
    controlText.setCharacterSize(35);
    controlText.setFillColor(sf::Color::Green);
    controlText.setOutlineThickness(2.0f);
    controlText.setPosition(30, window.getSize().y / 5 - 100.f);



    bText.setFont(font);
    bText.setString("B : \nBack");
    bText.setCharacterSize(25);
    bText.setFillColor(sf::Color::Black);
    bText.setOutlineColor(sf::Color::White);
    bText.setOutlineThickness(2.f);
    bText.setPosition(900.f, window.getSize().y / 5);

    sellerNPCText.setFont(font);
    sellerNPCText.setString("All   NPC ");
    sellerNPCText.setCharacterSize(35);
    sellerNPCText.setFillColor(sf::Color::Green);
    sellerNPCText.setOutlineThickness(2.0f);
    sellerNPCText.setPosition(1100.f, window.getSize().y / 5 - 100.f);
    if (!npcTexture.loadFromFile("Resources\\Image\\NPC\\sprite sheets\\medieval\\shady_guy.png")) {
        throw("ERROR::NPC::FAILED TO LOAD TEXTURE");
    }
    intRect1 = sf::IntRect(0, 0, 34, 34);
    npcSprite.setTextureRect(intRect1);
    npcSprite.setTexture(npcTexture);
    npcSprite.setScale(4, 4 );
    npcSprite.setPosition(950.f, window.getSize().y / 5 + 100.f);
    npc = 0;

    if (!sellerTexture.loadFromFile("Resources\\Image\\NPC\\seller\\Gipsy _spritesheet.png")) {
        throw("ERROR::NPC::FAILED TO LOAD TEXTURE");
    }
    intRect2 = sf::IntRect(0, 0, 80, 80);
    sellerSprite.setTextureRect(intRect2);
    sellerSprite.setTexture(sellerTexture);
    sellerSprite.setScale(2.5f, 2.5f);
    sellerSprite.setPosition(1100.f, window.getSize().y / 5+20);
    seller = 0;



    eText.setFont(font);
    eText.setString("E :\nInteract  with  \nNPC \ Seller");
    eText.setCharacterSize(25);
    eText.setFillColor(sf::Color::Black);
    eText.setOutlineColor(sf::Color::White);
    eText.setOutlineThickness(2.f);
    eText.setPosition(1350.f, window.getSize().y / 5);

    yText.setFont(font);
    yText.setString("Y : \nBuying  Stuff  From  Seller");
    yText.setCharacterSize(25);
    yText.setFillColor(sf::Color::Black);
    yText.setOutlineColor(sf::Color::White);
    yText.setOutlineThickness(2.f);
    yText.setPosition(900.f, window.getSize().y / 5 + 250.f);


    deBuffText.setFont(font);
    deBuffText.setString("Four   DeBUFF ");
    deBuffText.setCharacterSize(35);
    deBuffText.setFillColor(sf::Color::Green);
    deBuffText.setOutlineThickness(2.0f);
    deBuffText.setPosition(1100.f, window.getSize().y / 5. + 320.f);






    deBuff1Texture.loadFromFile("Resources\\Image\\Debuff\\Effect_hearty.png");
    deBuff2Texture.loadFromFile("Resources\\Image\\Debuff\\Effect_On_fire.png");
    deBuff3Texture.loadFromFile("Resources\\Image\\Debuff\\Effect_Frozen.png");
    deBuff4Texture.loadFromFile("Resources\\Image\\Debuff\\Effect_Jarated.png");

    deBuff1Sprite.setTexture(deBuff1Texture);
    deBuff2Sprite.setTexture(deBuff2Texture);
    deBuff3Sprite.setTexture(deBuff3Texture);
    deBuff4Sprite.setTexture(deBuff4Texture);
    deBuff1Sprite.setScale(2, 2);
    deBuff2Sprite.setScale(2, 2);
    deBuff3Sprite.setScale(2, 2);
    deBuff4Sprite.setScale(2, 2);
    deBuff1Sprite.setPosition(950.f, window.getSize().y / 5 + 450.f);
    deBuff2Sprite.setPosition(1250.f, window.getSize().y / 5 + 430.f);
    deBuff3Sprite.setPosition(950.f, window.getSize().y / 5 + 610.f);
    deBuff4Sprite.setPosition(1290.f, window.getSize().y / 5 + 610.f);

    deBuff1.setFont(font);
    deBuff1.setString("Normal :");
    deBuff1.setCharacterSize(25);
    deBuff1.setFillColor(sf::Color::Black);
    deBuff1.setOutlineColor(sf::Color::White);
    deBuff1.setOutlineThickness(2.f);
    deBuff1.setPosition(900.f, window.getSize().y / 5 + 400.f);

    deBuff2.setFont(font);
    deBuff2.setString("FIRE :");
    deBuff2.setCharacterSize(25);
    deBuff2.setFillColor(sf::Color::Black);
    deBuff2.setOutlineColor(sf::Color::White);
    deBuff2.setOutlineThickness(2.f);
    deBuff2.setPosition(1200.f, window.getSize().y / 5 + 400.f);

    deBuff3.setFont(font);
    deBuff3.setString("ICE:");
    deBuff3.setCharacterSize(25);
    deBuff3.setFillColor(sf::Color::Black);
    deBuff3.setOutlineColor(sf::Color::White);
    deBuff3.setOutlineThickness(2.f);
    deBuff3.setPosition(900.f, window.getSize().y / 5 + 650.f);

    deBuff4.setFont(font);
    deBuff4.setString("POISON:");
    deBuff4.setCharacterSize(25);
    deBuff4.setFillColor(sf::Color::Black);
    deBuff4.setOutlineColor(sf::Color::White);
    deBuff4.setOutlineThickness(2.f);
    deBuff4.setPosition(1200.f, window.getSize().y / 5 + 650.f);


}

void GameIntro::handleEvent(sf::Event& event, bool& gameStarted)
{
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed)
    {

        if (currentPage == Page::BACKGROUND_INFO)
        {
            currentPage = Page::GAMEPLAY_INFO;
        }

        else if (currentPage == Page::GAMEPLAY_INFO)
        {
            finished = true;
            gameStarted = true;
        }
    }
}

void GameIntro::render()
{
    window.draw(backgroundSprite);


    if (currentPage == Page::BACKGROUND_INFO)
    {
        window.draw(backgroundInfoText);
        window.draw(backgroundInfoText2);

        window.draw(continueText);
    }
    else if (currentPage == Page::GAMEPLAY_INFO)
    {
        window.draw(startText);
        window.draw(aText);
        window.draw(dText);
        window.draw(bText);
        window.draw(escText);
        window.draw(spaceText);
        window.draw(enterText);
        window.draw(magicBallText);
        window.draw(controlText);
        window.draw(sellerNPCText);
        window.draw(eText);
        window.draw(yText);
        window.draw(deBuffText);
        window.draw(deBuff1);
        window.draw(deBuff2);
        window.draw(deBuff3);
        window.draw(deBuff4);



        window.draw(aSprite);
        window.draw(dSprite);
        window.draw(enterSprite);
        window.draw(magicBallSprite);
        window.draw(npcSprite);
        window.draw(sellerSprite);
        window.draw(deBuff1Sprite);
        window.draw(deBuff2Sprite);
        window.draw(deBuff3Sprite);
        window.draw(deBuff4Sprite);



    }

    //window.draw(introText);
}

bool GameIntro::isFinished() const
{
    return finished;
}

void GameIntro::update()
{
    if (currentPage == Page::GAMEPLAY_INFO) {
        float totalTime = animationClock.getElapsedTime().asSeconds();
        float switchTime = 0.1f;
        if (totalTime >= switchTime) {

            aSprite.setTexture(walkTextures[walk]);
            dSprite.setTexture(walkTextures[walk]);
            walk = (walk + 1) % 6;

            enterSprite.setTexture(enterTextures[enter]);
            enter = (enter + 1) % 5;

            magicBallSprite.setTexture(magicBallTextures[magicBall]);
            magicBall = (magicBall + 1) % magicBallTextures.size();

            int width1 = npcTexture.getSize().x;
            int width2 = sellerTexture.getSize().x;
            if (intRect1.left == width1 - 34) {
                intRect1.left = 0;
            }
            else {
                intRect1.left += 34;
            }
            npcSprite.setTextureRect(intRect1);


            if (intRect2.left == width2 - 80) {
                intRect2.left = 0;
            }
            else {
                intRect2.left += 80;
            }
            sellerSprite.setTextureRect(intRect2);

            animationClock.restart();
        }
    }

}
