#ifndef TEXTBOX_H_
#define TEXTBOX_H_

#include <SFML/Graphics.hpp>
#include <string>

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
    TextBox(pair<int, int> widthHeight, pair<int, int> posXY, std::string message, const sf::Font &font, int outline = 0, bool editable = true, bool isB = false);
    void setFontType(sf::Font &font);

    sf::RectangleShape &getBox();
    sf::Text &getText();
    bool &getClicked();
    bool &getIsButton();
    bool &getEditable();
    void setText(string s);
    void setClicked(bool tf);
    void setEditable(bool tf);
};

#endif // TEXTBOX_H_
