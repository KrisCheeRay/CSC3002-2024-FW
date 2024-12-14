#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ResourceManager {
    std::map<std::string, sf::Texture> textures;
public:
    const sf::Texture& getTexture(const std::string& filename);
};

#endif // RESOURCEMANAGER_H