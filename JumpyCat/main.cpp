#include <SFML/Graphics.hpp>

#include <iostream>
#include <format>

#include "GameEngine.h"
#include "TextureManager.h"
#include "Player.h"
#include "GameObjectWall.h"

class GameObjectFactory
{
    TextureManager& m_tm;
    GameEngine& m_engine;
    GameObjectBase* m_prototype;

    GameObjectFactory(TextureManager& tm, GameEngine& engine, GameObjectBase* prototype):
        m_tm{tm},
        m_engine{engine},
        m_prototype{prototype}
    {}

    GameObjectBase* createObject(sf::Vector2f position)
    {
        GameObjectBase* newObj = m_prototype->clone(position);
        newObj->setPosition(position);
        return newObj;
    }
};

void loadPlayerGraphics(TextureManager& tm, Player* player)
{
    float sizeX{ 100 }, sizeY{ 90 };
    float texSizeX{ 542 }, texSizeY{ 474 };
    Animation standingAnimation(tm.getTexture("cat_standing"), 10, {texSizeX, texSizeY}, {sizeX, sizeY}, 1.0f, true);
    Animation jumpingAnimation(tm.getTexture("cat_jumping"), 8, { texSizeX, texSizeY }, { sizeX, sizeY }, 1.0f, false);
    Animation movingAnimation(tm.getTexture("cat_moving"), 10, { texSizeX, texSizeY }, { sizeX, sizeY }, 1.0f, true);
    Animation duckingAnimation(tm.getTexture("cat_ducking"), 10, { texSizeX, texSizeY }, { sizeX, sizeY }, 1.0f, true);
    Animation fallingAnimation(tm.getTexture("cat_falling"), 8, { texSizeX, texSizeY }, { sizeX, sizeY }, 1.0f, false);

    player->m_graphicsComponent.addAnimation("standing", standingAnimation, {-25, 0});
    player->m_graphicsComponent.addAnimation("jumping", jumpingAnimation, { -25, 0 });
    player->m_graphicsComponent.addAnimation("moving", movingAnimation, { -25, 0 });
    player->m_graphicsComponent.addAnimation("ducking", duckingAnimation, { -25, 0 });
    player->m_graphicsComponent.addAnimation("falling", fallingAnimation, { -25, 0 });

    player->initializeState();

    sf::RectangleShape collider1 = sf::RectangleShape();
    collider1.setFillColor(sf::Color::Transparent);
    collider1.setOutlineColor(sf::Color::Green);
    collider1.setOutlineThickness(1);
    collider1.setPosition(sf::Vector2f({ 400.0f, 250.0f }));
    collider1.setSize({ 50, 90 });
    player->m_colliderComponent.addColliders({ collider1 }, { {0,0} });

    player->initializeFeelers();
}

void loadReaperGraphics(TextureManager& tm, Player* reaper)
{
    float sizeX{ 100 }, sizeY{ 90 };
    float texSizeX{ 900 }, texSizeY{ 900 };
    Animation walkingAnimation(tm.getTexture("reaper_walking"), 23, { texSizeX, texSizeY }, { sizeX, sizeY }, 2.0f, true);

    reaper->m_graphicsComponent.addAnimation("standing", walkingAnimation, { 0,0 });
    reaper->m_graphicsComponent.m_currentAnimation = "standing";
    reaper->initializeState();

    sf::RectangleShape collider1 = sf::RectangleShape();
    collider1.setFillColor(sf::Color::Transparent);
    collider1.setOutlineColor(sf::Color::Green);
    collider1.setOutlineThickness(1);
    collider1.setPosition(sf::Vector2f({ 400.0f, 250.0f }));
    collider1.setSize({ 50, 90 });
    reaper->m_colliderComponent.addColliders({ collider1 }, { {30,0} });

    reaper->initializeFeelers();
}

void createTile(TextureManager& textureManager, GameEngine& engine, sf::Vector2f position)
{
    GameObjectWall* tile = new GameObjectWall();
    Animation tileAnimation(textureManager.getTexture("tile"), 1, { 128, 128 }, { 100, 100 }, 0.0f, false);
    tile->m_graphicsComponent.addAnimation("tile", tileAnimation, { 0, 0 });
    tile->m_graphicsComponent.m_currentAnimation = "tile";
    tile->m_graphicsComponent.m_animations["tile"].m_animationFrames[0].setPosition(position);
    sf::RectangleShape collider1 = sf::RectangleShape();
    collider1.setFillColor(sf::Color::Transparent);
    collider1.setOutlineColor(sf::Color::Red);
    collider1.setOutlineThickness(1);
    collider1.setPosition(position);
    collider1.setSize({ 100, 100 });
    tile->m_colliderComponent.addColliders({ collider1 }, { {0, 0} });
    tile->setPosition(position);
    engine.addEntity(tile);
}

void createBackground(TextureManager& textureManager, GameEngine& engine, sf::Vector2f position)
{
    Scenery* background = new Scenery();
    Animation backgroundAnimation(textureManager.getTexture("background"), 1, { 1000, 800 }, { 1920, 1080 }, 0.0f, false);
    background->m_graphicsComponent.addAnimation("background", backgroundAnimation, { 0, 0 });
    background->m_graphicsComponent.m_currentAnimation = "background";
    background->m_graphicsComponent.m_animations["background"].m_animationFrames[0].setPosition(position);
    engine.addScenery(background);
}

void loadScenery(TextureManager& textureManager, GameEngine& engine)
{
    createBackground(textureManager, engine, { -200, -200 });
    createBackground(textureManager, engine, { -200 + 1920 * 1, -200 });
    createBackground(textureManager, engine, { -200 + 1920 * 2, -200 });
    createBackground(textureManager, engine, { -200 + 1920 * 3, -200 });

    // left mid island
    createTile(textureManager, engine, { 300, 700 });
    createTile(textureManager, engine, { 400, 700 });
    createTile(textureManager, engine, { 500, 700 });
    createTile(textureManager, engine, { 500, 600 });

    // right mid island
    createTile(textureManager, engine, { 700, 400 });
    createTile(textureManager, engine, { 700, 500 });
    createTile(textureManager, engine, { 800, 500 });
    createTile(textureManager, engine, { 900, 500 });

    // left top island
    createTile(textureManager, engine, { 200, 300 });
    createTile(textureManager, engine, { 300, 300 });
    createTile(textureManager, engine, { 400, 300 });

    // bottom row
    for (int i = 0; i < 7; i++)
    {
        createTile(textureManager, engine, { 200 + float(i * 100), 900 });
    }
    for (int i = 9; i < 13; i++)
    {
        createTile(textureManager, engine, { 200 + float(i * 100), 900 });
    }
    for (int i = 15; i < 21; i++)
    {
        createTile(textureManager, engine, { 200 + float(i * 100), 900 });
    }

    //middle platforms
    createTile(textureManager, engine, { 1400, 700 });
    createTile(textureManager, engine, { 1500, 700 });
    createTile(textureManager, engine, { 1600, 700 });
    createTile(textureManager, engine, { 1600, 600 });

    // top rising platforms
    createTile(textureManager, engine, { 1300, 400 });

    createTile(textureManager, engine, { 1000, 200 });

    createTile(textureManager, engine, { 700, 000 });

    createTile(textureManager, engine, { 400, -200 });

    // right transition platforms
    createTile(textureManager, engine, { 1900, 700 });
    createTile(textureManager, engine, { 1900, 400 });
    createTile(textureManager, engine, { 2000, 400 });
    createTile(textureManager, engine, { 2100, 400 });

    //top platforms
    for (int i = 24; i < 31; i++)
    {
        createTile(textureManager, engine, { float(i * 100), 400 });
    }

}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Jumpy cat!");

    sf::View mainView;
    mainView.setCenter(700, 400);
    mainView.setSize(1920, 1080);

    sf::View miniMapView;
    miniMapView.setCenter(2 * 1920 / 2, 1 * 1080 / 2);
    miniMapView.setSize(2 * 1920, 1080);
    miniMapView.setViewport(sf::FloatRect(0.70f, 0.0f, 0.30f, 0.15f));

    TextureManager textureManager;

    Player* player = new Player("It's a-me, Mario!", { 120, 100 });
    loadPlayerGraphics(textureManager, player);
    player->setPosition({ 400, 400 });

    Player* reaper = new Player("Reaper", { 100, 100 });
    loadReaperGraphics(textureManager, reaper);
    reaper->setPosition({ 700, -300 });

    GameEngine engine;
    loadScenery(textureManager, engine);
    engine.addPlayer(player);
    engine.addEntity(reaper);

    // extended background for main view
    sf::RectangleShape bck;
    sf::Color color;
    color.r = 207;
    color.g = 239;
    color.b = 252;
    color.a = 255;
    bck.setFillColor(color);
    bck.setPosition(sf::Vector2f(-200, -200 - 1080));
    bck.setSize(sf::Vector2f(400 + 1920.0f * 3, 400 + 1080.0f * 2));

    sf::RectangleShape bck2;
    sf::Color color2;
    color2.r = 183;
    color2.g = 231;
    color2.b = 250;
    color2.a = 255;
    bck2.setFillColor(color2);
    bck2.setPosition(sf::Vector2f(-200, 400));
    bck2.setSize(sf::Vector2f(400 + 1920.0f * 3, 400 + 1080.0f * 2));

    // background and frame for minimap
    sf::RectangleShape bck3;
    sf::Color color3;
    color3.r = 183;
    color3.g = 231;
    color3.b = 250;
    color3.a = 255;
    bck3.setFillColor(color3);
    bck3.setPosition(sf::Vector2f(0, 0));
    bck3.setSize(sf::Vector2f(1920.0f * 3, 1080.0f * 1));
    bck3.setOutlineColor(sf::Color::Blue);
    bck3.setOutlineThickness(1);

    sf::RectangleShape frame;
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color::Blue);
    frame.setOutlineThickness(10);
    frame.setPosition({ 10, 10 });
    frame.setSize({ 1920 * 2 - 20 , 1080 - 20 });

    float dt;
    sf::Clock frameClock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
        {
            //config.debug = !config.debug;
        }

        dt = frameClock.restart().asSeconds();
        
        // ===== INPUT =====
        // in engine update
        std::vector<Input> input = engine.collectInput();
        engine.handleInput(input);

        // ===== UPDATE =====
        engine.update(dt);

        //mainView.setCenter(engine.getPlayerPosition());
        window.setView(mainView);
        sf::Vector2f playerPosition = engine.getPlayerPosition();
        playerPosition = (sf::Vector2f)window.mapCoordsToPixel(playerPosition, mainView);
        //std::cout << "Player position: ( " << playerPosition.x << " , " << playerPosition.y << " )\n";
        float width = 1920.0f;
        float height = 1080.0f;
        if (playerPosition.x < width / 3)
            mainView.move(sf::Vector2f({ -width / 20, 0 }) * dt * 10.0f);
        if (playerPosition.x > 2 * width / 3)
            mainView.move(sf::Vector2f({ width / 20, 0 }) * dt * 10.0f);
        if (playerPosition.y < height / 3)
            mainView.move(sf::Vector2f({ 0,-height/20 }) * dt * 10.0f);
        if (playerPosition.y > 2 * height / 3 - 100)
            mainView.move(sf::Vector2f({ 0,height/20 }) * dt * 10.0f);

        // ===== DRAW =====
        window.clear();

        window.setView(mainView);
        window.draw(bck);
        window.draw(bck2);
        window.draw(engine);

        window.setView(miniMapView);
        window.draw(bck3);
        window.draw(engine);
        window.draw(frame);

        window.display();
    }

    return 0;
}