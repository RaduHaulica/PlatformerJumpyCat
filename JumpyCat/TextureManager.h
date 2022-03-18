#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager
{
public:
    TextureManager();
    ~TextureManager();
    std::map<std::string, sf::Texture*> m_textures;

    void initialize();
    sf::Texture* getTexture(std::string name);
};