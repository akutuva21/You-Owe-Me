#include <SFML/Graphics.hpp>
#include <string>

class TextBox
{
    sf::RectangleShape box;
    sf::Text text;
    std::string message;
    bool editable;
    bool isButton;
    bool clicked = false;

public:
    TextBox();
    TextBox(std::pair<int, int> widthHeight, std::pair<int, int> posXY, std::string message, const sf::Font &font, int outline = 0, bool editable = true, bool isB = false);
    void setFontType(sf::Font &font);

    sf::RectangleShape &getBox();
    sf::Text &getText();
    bool &getClicked();
    bool &getIsButton();
    bool &getEditable();
    void setText(std::string s);
    void setBox(float x, float y);
    void setClicked(bool tf);
    void setEditable(bool tf);
};
