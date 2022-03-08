#include "TextureManager.h"

TextureManager::TextureManager()
{
    initialize();
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

    sf::Texture* characterTex = new sf::Texture();
    characterTex->loadFromFile(basePath + "platformerPack_character.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("character", characterTex));

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

    sf::Texture* reaperWalkingTex = new sf::Texture();
    reaperWalkingTex->loadFromFile(basePath + "character_reaper_walking_spritesheet.png");
    m_textures.insert(std::pair<std::string, sf::Texture*>("reaper_walking", reaperWalkingTex));
}