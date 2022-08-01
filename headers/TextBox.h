#include <SFML/Graphics.hpp>
#include <string>

#pragma once

using namespace std;

class TextBox
{
    sf::RectangleShape box;
    sf::Text text;
    string message;
    bool editable;
    bool isButton;
    bool clicked = false;

public:
    TextBox();
    TextBox(pair<int, int> widthHeight, pair<int, int> posXY, string message, const sf::Font &font, int outline = 0, bool editable = true, bool isB = false);
    void setFontType(sf::Font &font);

    sf::RectangleShape &getBox();
    sf::Text &getText();
    bool &getClicked();
    bool &getIsButton();
    bool &getEditable();
    void setText(string s);
    void setBox(float x, float y);
    void setClicked(bool tf);
    void setEditable(bool tf);
};
