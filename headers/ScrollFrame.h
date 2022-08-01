#ifndef SCROLL_FRAME_H_
#define SCROLL_FRAME_H_

#include <SFML/Graphics.hpp>

#include "TextBox.h"

class ScrollFrame
{
    float height;
    float width;
    sf::RectangleShape frame;
    sf::RectangleShape scrollBar;
    bool mouseDown;
    vector<TextBox> rows;

public:
    ScrollFrame();
    ScrollFrame(float height, float width, std::vector<TextBox> &obj);
    void Scroll(sf::Vector2f worldPos);
    sf::RectangleShape getFrame();
    sf::RectangleShape getScrollBar();
    bool getMouseDown();
    void setScrollBar(sf::Vector2f worldPos);
    void setMouseDown(bool tf);
    void setRow(string s, float ratio);
};

#endif // SCROLL_FRAME_H_
