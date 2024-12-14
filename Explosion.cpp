#include"Explosion.h"
std::vector<sf::Texture> loadTextures(const std::string& folderPath, int frameCount) {
    std::vector<sf::Texture> textures;
    for (int i = 1; i <= frameCount; ++i) {
        sf::Texture texture;
        std::string filePath = "Resources//Image//Explosion//CircleSplosionV2_100x100px" + std::to_string(i) + ".png";
        if (texture.loadFromFile(filePath)) {
            textures.push_back(texture);
        }
        else {
            std::cerr << "Failed to load texture: " << filePath << std::endl;
        }
    }
    return textures;
}