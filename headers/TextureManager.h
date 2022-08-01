#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

using namespace std;

class TextureManager
{
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName);
    static string imagesDirectory;

public:
    static sf::Texture &GetTexture(string textureName);
    static void Clear();
};

#endif // TEXTUREMANAGER_H_
