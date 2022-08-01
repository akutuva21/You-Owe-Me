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

#pragma once

using namespace std;

class Interface
{
    int width;
    int height;
    sf::RenderWindow window;
    map<string, sf::Sprite> sprites;
    map<string, TextBox> textBoxes;
    ScrollFrame frame;

public:
    // Creates window object
    Interface(int width, int height, string title);
    void GenerateWindow();
    void DrawObjects();
    void AddSprite(string name, string imageName, pair<double, double> posScaleXY, pair<double, double> sizeScaleXY);
    void AddTextBox(string name, pair<double, double> posScaleXY, pair<double, double> sizeScaleXY, string message, const sf::Font &font, int outline = 0, bool editable = true, bool isB = false);
    void ClearSprites();
};
