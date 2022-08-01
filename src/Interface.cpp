#include "../headers/Interface.h"

// creates window object
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
    times.first = ((float) t) / CLOCKS_PER_SEC;
    t = clock();
    list.pushback(from, to, amount);
    t = clock() - t;
    times.second = ((float) t) / CLOCKS_PER_SEC;

    return times;
}

double printDensity()
{
    int num_people = matrix.getMatrix().size();
    int num_edges = matrix.getNumEdges();

    return (double)num_edges / (double)((double)num_people * ((double)num_people - 1));
}

Interface::Interface(int width, int height, string title, const sf::Font &font)
{
    TextBox random(std::make_pair(0.2, 0.2), std::make_pair(150, 30), "xdxdxdxdxdxd", font, 3);
    TextBox random2(std::make_pair(0.2, 0.2), std::make_pair(150, 30), "xdxdxdxdxdxd", font, 3);
    TextBox random3(std::make_pair(0.2, 0.2), std::make_pair(150, 30), "xdxdxdxdxdxd", font, 3);
    TextBox random4(std::make_pair(0.2, 0.2), std::make_pair(150, 30), "xdxdxdxdxdxd", font, 3);
    TextBox random5(std::make_pair(0.2, 0.2), std::make_pair(150, 30), "xdxdxdxdxdxd", font, 3);
    std::vector<TextBox> scrollTextBoxes;
    scrollTextBoxes.push_back(random);
    scrollTextBoxes.push_back(random2);
    scrollTextBoxes.push_back(random3);
    scrollTextBoxes.push_back(random4);
    scrollTextBoxes.push_back(random5);
    this->height = height;
    this->width = width;
    window.create(sf::VideoMode(width, height), title);
    TextBox obj(make_pair(0.2, 0.2), make_pair(0.2, 0.2), "xd", font, 1, false, false);
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
                                cout << "import" << endl;
                                string filePath = textBoxes["Import"].getText().getString();

                                string line;
                                //ifstream file("./hugetransactions.txt");
                                ifstream file(filePath);
                                pair<float, float> time_sums;
                                while (getline(file, line)) {
                                    auto times = add(line);
                                    time_sums.first += times.first;
                                    time_sums.second += times.second;
                                }
                                file.close();
                                cout << "Reading in 100K Edges for Matrix required " << time_sums.first << " seconds." << endl;
                                cout << "Reading in 100K Edges for List required " << time_sums.second << " seconds." << endl;
                                cout << "File Has Been Read!" << endl;
                                cout << "The density of the directed graph is " << printDensity() << endl;
                            }
                            // Call function
                            if (item.first == "AddButton")
                            {
                                cout << "Add" << endl;
                                string line = textBoxes["AddEdge1"].getText().getString() + " " + textBoxes["AddEdge2"].getText().getString() + " " + textBoxes["AddEdgeAmount"].getText().getString();
                                while (line != "exit") {
                                    try {
                                        pair<float, float> times = add(line);
                                        cout << "\nPushing back the edge for Matrix required " << times.first << " seconds." << endl;
                                        cout << "Pushing back the edge in List required " << times.second << " seconds." << endl;
                                    }
                                    catch (...) {
                                        cout << "error" << endl;
                                        continue;
                                    }
                                    cout << "Added transaction!\n" << endl;
                                    cout << "The density of the directed graph is " << printDensity() << endl;
                                    getline(cin, line);
                                }
                            }
                            // Call function
                            if (item.first == "SimplifyButton")
                            {
                                cout << "simplify" << endl;
                                auto t = clock();
                                list.simplifyList();
                                t = clock() - t;
                                cout << "This operation (Simplify List) took " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
                                t = clock();
                                matrix.simplifyMatrix();
                                t = clock() - t;
                                cout << "This operation (Simplify Matrix) took " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
                                cout << "Printing Simplified Edges by Weight:" << endl;
                                list.printEdgesByWeight();
                                ///matrix.printSimpleEdges();
                                cout << "\nUnfortunately, no one can be told what the Matrix is. You have to see it for yourself." << endl;
                            }
                            // Call function
                            if (item.first == "LeaderboardButton")
                            {
                                cout << "leaderboard" << endl;
                                int k = 5;
                                list.printInitialBalances(k);
                            }
                            // Call function
                            if (item.first == "Export")
                            {
                                cout << "export" << endl;
                                auto results = list.getSimpleEdges();
                                ofstream file("./exported_data.txt");
                                for (auto edge : results) {
                                    file << "[\"" << get<0>(edge) << "\", \"" << get<1>(edge) << "\", " << get<2>(edge) << "]" << endl;
                                }
                                file.close();
                            }
                        }
                    }
                }
            }
            if (event.type == sf::Event::TextEntered) {
                for (auto &item : textBoxes)
                {
                    if (textBoxes[item.first].getEditable() && textBoxes[item.first].getClicked())
                    {
                        if (event.text.unicode == 8)
                        {
                            std::string curr = textBoxes[item.first].getText().getString();
                            textBoxes[item.first].setText(curr.substr(0, curr.length() - 1));
                        }
                        else if (event.text.unicode < 128)
                        {
                            std::string curr = textBoxes[item.first].getText().getString();
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
    for (std::pair<std::string, sf::Sprite> item : sprites)
    {
         window.draw(item.second);
    }
    for (std::pair<std::string, TextBox> item : textBoxes)
    {
        window.draw(item.second.getBox());
        window.draw(item.second.getText());
    }
    for (auto &item : frame.getRows())
    {
        if (item.getBox().getPosition().y >= 400)
        {
            window.draw(item.getBox());
            window.draw(item.getText());
        }
    }

    window.draw(frame.getFrame());
    window.draw(frame.getScrollBar());
}// adds sprite (image)

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
