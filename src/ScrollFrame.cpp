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
    scrollBar.setPosition(sf::Vector2f(710, 400));
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

std::vector<TextBox> &ScrollFrame::getRows()
{
    return rows;
}
void ScrollFrame::setScrollBar(sf::Vector2f worldPos)
{
    float xPos = scrollBar.getPosition().x;
    if (xPos < 400)
    {
        xPos = 400;
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
    if (yPos < 400)
        yPos = 400;
    if (yPos > 710)
        yPos = 710;
    float scrollRatio = (yPos - 400) / 10;
    scrollBar.setPosition(scrollBar.getPosition().x, yPos);
    setRow("im delusion", scrollRatio);
}

void ScrollFrame::setRow(std::string s, float ratio)
{
    for (int i = 0; i < rows.size(); i++)
    {
        rows[i].setText(s);
        rows[i].setBox(100, 400 + ratio * 310 - i * 30);
    }
}
