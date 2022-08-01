// Adapted from Minesweeper Project COP3503
#include "../headers/TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string FileName)
{
	string path = "../assets/images/";
	path += FileName + ".png";

	textures[FileName].loadFromFile(path);
}

sf::Texture &TextureManager::GetTexture(string TextureName)
{
	if (textures.find(TextureName) == textures.end())
		LoadTexture(TextureName);
	return textures[TextureName];
}

void TextureManager::Clear()
{
	textures.clear();
}