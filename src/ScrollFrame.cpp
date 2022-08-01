#include "../headers/ScrollFrame.h"

#include <vector>

ScrollFrame::ScrollFrame()
{
}
ScrollFrame::ScrollFrame(float w, float h, std::vector<TextBox> &obj)
{
    width = w;
    height = h;
    mouseDown = false;
    frame.setSize(sf::Vector2f(w, h));
    frame.setPosition(sf::Vector2f(0, 800));
    frame.setFillColor(sf::Color(255, 255, 255, 100));
    scrollBar.setSize(sf::Vector2f(20, 50));
    scrollBar.setPosition(sf::Vector2f(1230, 800));
    scrollBar.setFillColor(sf::Color(0, 0, 0, 100));
    rows = obj;
}

sf::RectangleShape ScrollFrame::getFrame()
{
    return frame;
}
sf::RectangleShape ScrollFrame::getScrollBar()
{
    return scrollBar;
}
bool ScrollFrame::getMouseDown()
{
    return mouseDown;
}

void ScrollFrame::setScrollBar(sf::Vector2f worldPos)
{
    float xPos = scrollBar.getPosition().x;
    if (xPos < 800)
    {
        xPos = 800;
    }
    scrollBar.setPosition(xPos, worldPos.y);
}

void ScrollFrame::setMouseDown(bool tf)
{
    mouseDown = tf;
}
void ScrollFrame::Scroll(sf::Vector2f worldPos)
{
    float yPos = worldPos.y;
    float scrollRatio = (yPos - 800) / 400;
    if (yPos < 800)
        yPos = 800;
    if (yPos > 1200)
        yPos = 1200;
    scrollBar.setPosition(scrollBar.getPosition().x, yPos);
}

void ScrollFrame::setRow(std::string s, float ratio)
{
    for (int i = 0; i < rows.size(); i++)
    {
        rows[i].setText(s);
        rows[i].getBox().setPosition(sf::Vector2f(rows[i].getBox().getPosition().x, 800 + ratio * 400));
    }
}
