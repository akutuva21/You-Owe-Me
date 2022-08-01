#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "ScrollFrame.h"
#include "TextureManager.h"
#include "List.h"
#include "Matrix.h"

using namespace std;

class Interface
{
    int width;
    int height;
    sf::RenderWindow window;
    std::map<std::string, sf::Sprite> sprites;
    std::map<std::string, TextBox> textBoxes;
    ScrollFrame frame;

public:
    // Creates window object
    Interface(int width, int height, std::string title);
    void GenerateWindow();
    void DrawObjects();
    void AddSprite(std::string name, std::string imageName, std::pair<double, double> posScaleXY, std::pair<double, double> sizeScaleXY);
    void AddTextBox(string name, std::pair<double, double> posScaleXY, std::pair<double, double> sizeScaleXY, std::string message, const sf::Font &font, int outline = 0, bool editable = true, bool isB = false);
    void ClearSprites();
};
