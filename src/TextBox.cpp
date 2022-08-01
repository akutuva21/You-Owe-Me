#include "../headers/TextBox.h"

#include <iostream>

TextBox::TextBox()
{
    message = "";
}
TextBox::TextBox(std::pair<int, int> posXY, std::pair<int, int> widthHeight, std::string message, const sf::Font &font, int outline, bool edit, bool isB)
{
    editable = edit;
    isButton = isB;
    // box around text
    box.setSize(sf::Vector2f(widthHeight.first, widthHeight.second));
    box.setPosition(posXY.first, posXY.second);
    box.setOutlineColor(sf::Color(0, 0, 0, 255));
    box.setFillColor(sf::Color(255, 255, 255, 150));
    if (!editable && isButton)
    {
        box.setOutlineColor(sf::Color(0, 0, 0, 125));
        box.setFillColor(sf::Color(0, 0, 0, 200));
    }
    if (outline == 0)
    {
        box.setFillColor(sf::Color(255, 255, 255, 75));
        editable = false;
    }
    box.setOutlineThickness(outline);

    // select font
    text.setFont(font);
    // set string
    text.setString(message);
    // set font size
    text.setCharacterSize(30);
    // set color
    text.setFillColor(sf::Color::Black);
    // set text style
    text.setStyle(sf::Text::Regular);
    // set position
    int boxHeight = box.getSize().y;
    int boxWidth = box.getSize().x;
    text.setPosition(posXY.first + 5, posXY.second + boxHeight / 2 - 18);

    if (!editable && isButton)
    {
        text.setFillColor(sf::Color::White);
    }
}

sf::RectangleShape &TextBox::getBox()
{
    return box;
}
sf::Text &TextBox::getText()
{
    return text;
}

bool &TextBox::getClicked()
{
    return clicked;
}

bool &TextBox::getIsButton()
{
    return isButton;
}

bool &TextBox::getEditable()
{
    return editable;
}
void TextBox::setText(std::string s)
{
    text.setString(s);
}

void TextBox::setClicked(bool tf)
{
    clicked = tf;
}

void TextBox::setEditable(bool tf)
{
    editable = tf;
}
