#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#pragma once

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