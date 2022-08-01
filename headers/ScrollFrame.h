#include <SFML/Graphics.hpp>
#include <string>

#include "TextBox.h"

#pragma once

using namespace std;

class ScrollFrame
{
    float height;
    float width;
    sf::RectangleShape frame;
    sf::RectangleShape scrollBar;
    bool mouseDown;
    std::vector<TextBox> rows;

public:
    sf::Font font;
    ScrollFrame();
    ScrollFrame(float height, float width, std::vector<TextBox> &obj);
    void Scroll(sf::Vector2f worldPos);
    sf::RectangleShape getFrame();
    sf::RectangleShape getScrollBar();
    vector<TextBox> &getRows();
    bool getMouseDown();
    float setScrollBar();
    void setMouseDown(bool tf);
    void setRow(float ratio);
    void newRow(string s);
};
