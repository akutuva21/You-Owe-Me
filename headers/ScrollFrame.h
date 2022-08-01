#include <SFML/Graphics.hpp>

#include "TextBox.h"
#pragma once

class ScrollFrame
{
    float height;
    float width;
    sf::RectangleShape frame;
    sf::RectangleShape scrollBar;
    bool mouseDown;
    std::vector<TextBox> rows;

public:
    ScrollFrame();
    ScrollFrame(float height, float width, std::vector<TextBox> &obj);
    void Scroll(sf::Vector2f worldPos);
    sf::RectangleShape getFrame();
    sf::RectangleShape getScrollBar();
    std::vector<TextBox> &getRows();
    bool getMouseDown();
    void setScrollBar(sf::Vector2f worldPos);
    void setMouseDown(bool tf);
    void setRow(std::string s, float ratio);
};