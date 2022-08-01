#include "../headers/Interface.h"

#include <iostream>
#include <string>

// creates window object

Interface::Interface(int width, int height, string title, const sf::Font &font)
{
    this->height = height;
    this->width = width;
    window.create(sf::VideoMode(width, height), title);
    TextBox obj(make_pair(0.2, 0.2), make_pair(0.2, 0.2), "xd", font, 1, false, false);
    vector<TextBox> scrollTextBoxes;
    frame = ScrollFrame(width, height * 20, scrollTextBoxes);
}

// run window loop
void Interface::GenerateWindow()
{
    while (window.isOpen())
    {
        // Get mouse pos
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            // Scroll Frame
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                if (frame.getScrollBar().getGlobalBounds().contains(worldPos))
                    frame.setMouseDown(true);
            }
            if (event.type == sf::Event::MouseButtonReleased)
                frame.setMouseDown(false);

            // Buttons and Text Box Click
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    for (auto &item : textBoxes)
                    {
                        if (textBoxes[item.first].getBox().getGlobalBounds().contains(worldPos) && textBoxes[item.first].getIsButton())
                        {
                            if (item.first == "ImportButton")
                            {
                                string filePath = textBoxes["Import"].getText().getString();
                            }
                            // Call function
                            if (item.first == "AddButton")
                            {
                                string input = textBoxes["AddEdge1"].getText().getString() + " " + textBoxes["AddEdge2"].getText().getString() + " " + textBoxes["AddEdgeAmount"].getText().getString();
                                cout << input << endl;
                            }
                            // Call function
                            if (item.first == "SimplifyButton")
                            {
                            }
                            // Call function
                            if (item.first == "LeaderboardButton")
                            {
                            }
                            // Call function
                            if (item.first == "Export")
                            {
                            }
                            // Call function
                        }
                        else if (textBoxes[item.first].getBox().getGlobalBounds().contains(worldPos))
                            textBoxes[item.first].setClicked(true);
                        else
                            textBoxes[item.first].setClicked(false);
                    }
                }
            }
            // Text Box Input
            if (event.type == sf::Event::TextEntered)
                for (auto &item : textBoxes)
                {
                    if (textBoxes[item.first].getEditable() && textBoxes[item.first].getClicked())
                    {
                        if (event.text.unicode == 8)
                        {
                            string curr = textBoxes[item.first].getText().getString();
                            textBoxes[item.first].setText(curr.substr(0, curr.length() - 1));
                        }
                        else if (event.text.unicode < 128)
                        {
                            string curr = textBoxes[item.first].getText().getString();
                            textBoxes[item.first].setText(curr += (char)(event.text.unicode));
                        }
                    }
                }

            // Text Box Submit
            if (frame.getMouseDown())
            {
                frame.Scroll(worldPos);
            }
            window.clear(sf::Color(255, 255, 255, 255));
            DrawObjects();
            window.display();
        }
    }
}
// draws all objects to screen
void Interface::DrawObjects()
{
    for (pair<string, sf::Sprite> item : sprites)
        window.draw(item.second);
    for (pair<string, TextBox> item : textBoxes)
    {
        window.draw(item.second.getBox());
        window.draw(item.second.getText());
    }

    window.draw(frame.getFrame());
    window.draw(frame.getScrollBar());
}

// adds sprite (image)
void Interface::AddSprite(string name, string imageName, pair<double, double> posScaleXY, pair<double, double> sizeScaleXY)
{
    if (sprites.find(name) == sprites.end())
    {
        sf::Sprite newSprite(TextureManager::GetTexture(imageName));
        newSprite.setScale(sf::Vector2f(sizeScaleXY.first * (double)width / 1000, sizeScaleXY.second * (double)height / 1000));
        int spriteWidth = newSprite.getGlobalBounds().width;
        int spriteHeight = newSprite.getGlobalBounds().height;
        // Scales image based on window size and corrects offset
        newSprite.setPosition(posScaleXY.first * width - spriteWidth / 2, posScaleXY.second * height - spriteHeight / 2);
        sprites[name] = newSprite;
    }
};

// adds components of textbox
void Interface::AddTextBox(string name, pair<double, double> posScaleXY, pair<double, double> sizeScaleXY, string message, const sf::Font &font, int outline, bool editable, bool isB)
{
    if (textBoxes.find(name) == textBoxes.end())
    {
        TextBox newTextBox(make_pair(width * posScaleXY.first, height * posScaleXY.second), make_pair(width * sizeScaleXY.first, height * sizeScaleXY.second), message, font, outline, editable, isB);
        // Scales Box based on window size and corrects offset
        textBoxes[name] = newTextBox;
    }
}
