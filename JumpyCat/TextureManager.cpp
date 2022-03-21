#include "TextureManager.h"

TextureManager::TextureManager()
{
    initialize();
}

TextureManager::~TextureManager()
{
    for (auto& [name, texture] : m_textures)
    {
        delete texture;
    }
}

sf::Texture* TextureManager::getTexture(std::string name)
{
    return m_textures[name];
}

void TextureManager::initialize()
{
    std::string basePath = "./assets/graphics/";

    sf::Texture* backgroundTex = new sf::Texture();
    backgroundTex->loadFromFile(basePath + "background.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("background", backgroundTex));

    sf::Texture* tileTex = new sf::Texture();
    tileTex->loadFromFile(basePath + "tile.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("tile", tileTex));

    sf::Texture* runeTex = new sf::Texture();
    runeTex->loadFromFile(basePath + "rune.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("rune", runeTex));

    sf::Texture* characterTex = new sf::Texture();
    characterTex->loadFromFile(basePath + "platformerPack_character.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("character", characterTex));

    sf::Texture* heartTex = new sf::Texture();
    heartTex->loadFromFile(basePath + "heart.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("heart", heartTex));

    sf::Texture* heartEmptyTex = new sf::Texture();
    heartEmptyTex->loadFromFile(basePath + "heart_empty.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("heartEmpty", heartEmptyTex));

    sf::Texture* coinTex = new sf::Texture();
    coinTex->loadFromFile(basePath + "coin.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("coin", coinTex));

    // player - cat

    sf::Texture* catStandingTex = new sf::Texture();
    catStandingTex->loadFromFile(basePath + "character_cat_standing_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("cat_standing", catStandingTex));

    sf::Texture* catMovingTex = new sf::Texture();
    catMovingTex->loadFromFile(basePath + "character_cat_walking_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("cat_moving", catMovingTex));

    sf::Texture* catJumpingTex = new sf::Texture();
    catJumpingTex->loadFromFile(basePath + "character_cat_jumping_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("cat_jumping", catJumpingTex));

    sf::Texture* catFallingTex = new sf::Texture();
    catFallingTex->loadFromFile(basePath + "character_cat_falling_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("cat_falling", catFallingTex));

    sf::Texture* catDuckingTex = new sf::Texture();
    catDuckingTex->loadFromFile(basePath + "character_cat_ducking_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("cat_ducking", catDuckingTex));

    sf::Texture* catHurtingTex = new sf::Texture();
    catHurtingTex->loadFromFile(basePath + "character_cat_hurting_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("cat_hurting", catHurtingTex));

    sf::Texture* catDyingTex = new sf::Texture();
    catDyingTex->loadFromFile(basePath + "character_cat_dying_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("cat_dying", catDyingTex));

    // enemy - reaper

    sf::Texture* reaperStandingTex = new sf::Texture();
    reaperStandingTex->loadFromFile(basePath + "character_reaper_standing_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("reaper_standing", reaperStandingTex));

    sf::Texture* reaperWalkingTex = new sf::Texture();
    reaperWalkingTex->loadFromFile(basePath + "character_reaper_walking_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("reaper_walking", reaperWalkingTex));

    sf::Texture* reaperJumpingTex = new sf::Texture();
    reaperJumpingTex->loadFromFile(basePath + "character_reaper_jumping_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("reaper_jumping", reaperJumpingTex));

    sf::Texture* reaperFallingTex = new sf::Texture();
    reaperFallingTex->loadFromFile(basePath + "character_reaper_falling_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("reaper_falling", reaperFallingTex));

    sf::Texture* reaperHurtingTex = new sf::Texture();
    reaperHurtingTex->loadFromFile(basePath + "character_reaper_hurting_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("reaper_hurting", reaperHurtingTex));

    sf::Texture* reaperDyingTex = new sf::Texture();
    reaperDyingTex->loadFromFile(basePath + "character_reaper_dying_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("reaper_dying", reaperDyingTex));
}