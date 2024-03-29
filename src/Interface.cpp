#include "../headers/Interface.h"

// creates window object
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>

AdjList list;
AdjMatrix matrix;

pair<float, float> add(string line)
{
    pair<float, float> times;
    size_t pos;
    size_t pos2;
    pos = line.find(" ");
    string from = line.substr(0, pos);
    pos2 = line.find(" ", pos + 1);
    string to = line.substr(pos + 1, pos2 - pos - 1);
    double amount = stod(line.substr(pos2 + 1));

    clock_t t;
    t = clock();
    matrix.pushback(from, to, amount);
    t = clock() - t;
    times.first = ((float)t) / CLOCKS_PER_SEC;
    t = clock();
    list.pushback(from, to, amount);
    t = clock() - t;
    times.second = ((float)t) / CLOCKS_PER_SEC;

    return times;
}

double printDensity()
{
    int num_people = matrix.getMatrix().size();
    int num_edges = matrix.getNumEdges();

    return (double)num_edges / (double)((double)num_people * ((double)num_people - 1));
}

double truncate(double x)
{
    return (int)(x * 100) / 100.0;
}

Interface::Interface(int width, int height, string title)
{
    this->height = height;
    this->width = width;
    window.create(sf::VideoMode(width, height), title);
    vector<TextBox> scrollTextBoxes;
    frame = ScrollFrame(width, 10000, scrollTextBoxes);
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
                                textBoxes["Import"].setText("");
                                string line;
                                ifstream file(filePath);
                                pair<float, float> time_sums;
                                int num_edges = 0;
                                while (getline(file, line))
                                {
                                    auto times = add(line);
                                    time_sums.first += times.first;
                                    time_sums.second += times.second;
                                    num_edges++;
                                }
                                file.close();

                                string read_edges_matrix = "Reading in " + to_string(num_edges) + " Edges for Matrix required " + to_string(time_sums.first) + " seconds.";
                                frame.newRow(read_edges_matrix);
                                string read_edges_list = "Reading in " + to_string(num_edges) + " Edges for List required " + to_string(time_sums.second) + " seconds.";
                                frame.newRow(read_edges_list);
                                frame.newRow("File has been read!");
                            }

                            if (item.first == "AddButton")
                            {
                                string input = textBoxes["AddEdge1"].getText().getString() + " " + textBoxes["AddEdge2"].getText().getString() + " " + textBoxes["AddEdgeAmount"].getText().getString();
                                textBoxes["AddEdge1"].setText("");
                                textBoxes["AddEdge2"].setText("");
                                textBoxes["AddEdgeAmount"].setText("");
                                try
                                {
                                    pair<float, float> times = add(input);
                                    string push_back_matrix = "Pushing back the edge for Matrix required " + to_string(times.first) + " seconds.";
                                    frame.newRow(push_back_matrix);
                                    string push_back_list = "Pushing back the edge for List required " + to_string(times.second) + " seconds.";
                                    frame.newRow(push_back_list);
                                }
                                catch (...)
                                {
                                    cout << "error" << endl;
                                }
                            }

                            if (item.first == "SimplifyButton")
                            {
                                auto t = clock();
                                list.simplifyList();
                                t = clock() - t;
                                string simplifyList = "The Simplify List operation took " + to_string(((float)t) / CLOCKS_PER_SEC) + " seconds.";
                                frame.newRow(simplifyList);
                                t = clock();
                                matrix.simplifyMatrix();
                                t = clock() - t;
                                string simplifyMatrix = "The Simplify Matrix operation took " + to_string(((float)t) / CLOCKS_PER_SEC) + " seconds.";
                                frame.newRow(simplifyMatrix);
                                frame.newRow("Simplification complete: New List has " + to_string(list.getSimpleEdges().size()) + " edges.");
                            }

                            if (item.first == "LeaderboardButton")
                            {
                                int k = 5;
                                vector<pair<string, double>> leaderboards = list.sortInitialBalances();
                                string s = "These are the top " + to_string(k) + " people who are owed money:";
                                frame.newRow(s);
                                for (int i = 0; i < min(k, (int)leaderboards.size()); i++)
                                {
                                    if (leaderboards[i].second > 0)
                                    {
                                        string amount = to_string(leaderboards[i].second);
                                        frame.newRow(leaderboards[i].first + " is owed $" + amount.substr(0, amount.find(".") + 3) + ".");
                                    }
                                }

                                frame.newRow("These are the top " + to_string(k) + " people who owe money:");
                                for (int i = leaderboards.size() - 1; i > max((int)leaderboards.size() - 1 - k, -1); i--)
                                {
                                    if (leaderboards[i].second < 0)
                                    {
                                        string amount = to_string(0 - leaderboards[i].second);
                                        frame.newRow(leaderboards[i].first + " owes $" + amount.substr(0, amount.find(".") + 3) + ".");
                                    }
                                }
                            }

                            if (item.first == "Export")
                            {
                                frame.newRow("Simplified Transactions:");
                                auto results = list.getSimpleEdges();
                                ofstream file("../text/exported_data.txt");
                                for (auto edge : results)
                                {
                                    file << "[\"" << get<0>(edge) << "\", \"" << get<1>(edge) << "\", " << get<2>(edge) << "]" << endl;
                                    string amount = to_string(get<2>(edge));
                                    frame.newRow(get<0>(edge) + " pays " + get<1>(edge) + " $" + amount.substr(0, amount.find(".") + 3));
                                }

                                file.close();
                                system("C:/Windows/py.exe ../scripts/parse.py");
                                system("C:/Windows/py.exe ../scripts/visualize.py");
                            }
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
            {
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
    for (auto &item : frame.getRows())
    {
        if (item.getBox().getPosition().y >= 550)
        {
            window.draw(item.getBox());
            window.draw(item.getText());
        }
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
}

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