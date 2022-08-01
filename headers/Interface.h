#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include "ScrollFrame.h"
#include "TextureManager.h"
#include "List.h"
#include "Matrix.h"

class Interface
{
    int width;
    int height;
    sf::RenderWindow window;
    map<std::string, sf::Sprite> sprites;
    map<std::string, TextBox> textBoxes;
    ScrollFrame frame;

public:
    // Creates window object
    Interface(int width, int height, std::string title, const sf::Font &font);
    void GenerateWindow();
    void DrawObjects();
    void AddSprite(std::string name, std::string imageName, std::pair<double, double> posScaleXY, std::pair<double, double> sizeScaleXY);
    void AddTextBox(string name, std::pair<double, double> posScaleXY, std::pair<double, double> sizeScaleXY, std::string message, const sf::Font &font, int outline = 0, bool editable = true, bool isB = false);
    void ClearSprites();
};


#endif // INTERFACE_H_
