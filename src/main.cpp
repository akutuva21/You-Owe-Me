// Largely derived from https://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <time.h>

#include "../headers/List.h"
#include "../headers/Matrix.h"

#include "../headers/Interface.h"

using namespace std;

typedef tuple<string, string, double> edge;

AdjList list;
AdjMatrix matrix;

void test()
{
    vector<edge> edges;
    edges.push_back(make_tuple("jonathan", "prayuj", 10.37));
    edges.push_back(make_tuple("prayuj", "achyudhan", 20.34));
    edges.push_back(make_tuple("achyudhan", "jonathan", 5.34));
    edges.push_back(make_tuple("prayuj", "jonathan", 100.33));
    edges.push_back(make_tuple("bob", "achyudhan", 10.12));
    edges.push_back(make_tuple("achyudhan", "joe", 25.45));

    for (auto edge : edges)
    {
        list.pushback(get<0>(edge), get<1>(edge), get<2>(edge));
        matrix.pushback(get<0>(edge), get<1>(edge), get<2>(edge));
    }

    matrix.simplifyMatrix();
    matrix.printSimpleEdges();
}

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

// int main()
// {
//     string input;
//     int inputInt;
//     clock_t t;
//     while (1) {
//         getline(cin, input);
//         try {
//             inputInt = stoi(input);
//         }
//         catch (...) {
//             cout << "Not a valid option! Try again." << endl;
//             cout << "You take the red pill... you stay in Wonderland, and I show you how deep the rabbit hole goes." << endl;
//             continue;
//         }
//         switch(inputInt)
//         {
//             case 1:
//             {
//                 string line;
//                 ifstream file("./hugetransactions.txt");
//                 pair<float, float> time_sums;
//                 while (getline(file, line)) {
//                     auto times = add(line);
//                     time_sums.first += times.first;
//                     time_sums.second += times.second;
//                 }
//                 file.close();
//                 cout << "Reading in 100K Edges for Matrix required " << time_sums.first << " seconds." << endl;
//                 cout << "Reading in 100K Edges for List required " << time_sums.second << " seconds." << endl;
//                 cout << "File Has Been Read!" << endl;
//                 cout << "The density of the directed graph is " << printDensity() << endl;
//                 break;
//             }
//             case 2:
//             {
//                 string line;
//                 getline(cin, line);
//                 while (line != "exit") {
//                     try {
//                         pair<float, float> times = add(line);
//                         cout << "\nPushing back the edge for Matrix required " << times.first << " seconds." << endl;
//                         cout << "Pushing back the edge in List required " << times.second << " seconds." << endl;
//                     }
//                     catch (...) {
//                         cout << "error" << endl;
//                         continue;
//                     }
//                     cout << "Added transaction!\n" << endl;
//                     cout << "The density of the directed graph is " << printDensity() << endl;
//                     getline(cin, line);
//                 }
//                 break;
//             }

//             case 3:
//             {
//                 auto t = clock();
//                 list.simplifyList();
//                 t = clock() - t;
//                 cout << "This operation (Simplify List) took " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
//                 t = clock();
//                 matrix.simplifyMatrix();
//                 t = clock() - t;
//                 cout << "This operation (Simplify Matrix) took " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
//                 break;
//             }

//             case 4:
//             {
//                 //list.printEdgesByWeight();
//                 matrix.printSimpleEdges();
//                 cout << "\nUnfortunately, no one can be told what the Matrix is. You have to see it for yourself." << endl;
//                 break;
//             }

//             case 5: // view leaderboards
//             {
//                 int k = 5;
//                 list.printInitialBalances(k);
//                 break;
//             }

//             case 6:
//             {
//                 auto results = list.getSimpleEdges();
//                 ofstream file("./exported_data.txt");
//                 for (auto edge : results) {
//                     file << "[\"" << get<0>(edge) << "\", \"" << get<1>(edge) << "\", " << get<2>(edge) << "]" << endl;
//                 }
//                 file.close();
//                 break;
//             }

//             case 7: // kill program
//             {
//                 return 0;
//             }

//             case 99:
//             {
//                 auto t = clock();
//                 test();
//                 t = clock() - t;
//                 cout << "This operation (test) took " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
//                 break;
//             }

//             default:
//             {
//                 cout << "Not a valid option! Try again. " << endl;
//                 cout << "You take the blue pill... the story ends, you wake up in your bed and believe whatever you want to believe." << endl;
//                 break;
//             }
//         }

//         cout << endl << endl;
//     }
//     return 0;
// }

const int WINDOW_HEIGHT = 1250;
const int WINDOW_WIDTH = 1250;
void GenerateInterface()
{
    // Load Font
    sf::Font font;
    font.loadFromFile("assets/fonts/Segoe_UI.ttf");
    // Creates window object
    Interface window(WINDOW_WIDTH, WINDOW_HEIGHT, "You Owe Me", font);
    // All objects within the window
    // Logo Background
    // window.AddTextBox("LogoBack", make_pair(0.35, 0), make_pair(0.3, 0.1), "", font, 0, false);
    // Images
    window.AddSprite("IRS Logo", "IRS_Logo", make_pair(0.5, 0.05), make_pair(0.07, 0.075));
    window.AddSprite("WallStreetBets", "WallStreetBets", make_pair(0.12, 0.95), make_pair(0.65, 0.65));
    window.AddSprite("Green Arrow", "Green_Arrow", make_pair(0.535, 0.385), make_pair(0.08, 0.08));
    window.AddSprite("Dollar Sign", "Dollar_Sign", make_pair(0.745, 0.385), make_pair(0.12, 0.12));
    window.AddSprite("Background", "Background", make_pair(0.5, 0.5), make_pair(2.5, 2.5));
    // Load TextBoxes/Buttons
    // Import
    window.AddTextBox("ImportTitle", make_pair(0.05, 0.2), make_pair(0.4, 0.075), "Input Transactions File Path Here:", font);
    window.AddTextBox("Import", make_pair(0.450, 0.2), make_pair(0.425, 0.075), "", font, 3);
    window.AddTextBox("ImportButton", make_pair(0.9, 0.2), make_pair(0.082, 0.075), "Import", font, 3, false, true);
    // Insert Edges
    window.AddTextBox("AddButton", make_pair(0.9, 0.35), make_pair(0.082, 0.075), " Insert", font, 3, false, true);
    window.AddTextBox("AddEdgeTitle", make_pair(0.05, 0.35), make_pair(0.4, 0.075), "Add a New Transaction:", font);
    window.AddTextBox("AddEdge1", make_pair(0.355, 0.35), make_pair(0.15, 0.075), "", font, 3);
    window.AddTextBox("AddEdge2", make_pair(0.565, 0.35), make_pair(0.15, 0.075), "", font, 3);
    window.AddTextBox("AddEdgeAmount", make_pair(0.775, 0.35), make_pair(0.1, 0.075), "", font, 3);
    // Simplify, Leaderboard, Export
    window.AddTextBox("SimplifyButton", make_pair(0.15, 0.5), make_pair(0.1, 0.075), " Simplify", font, 3, false, true);
    window.AddTextBox("LeaderboardButton", make_pair(0.39, 0.5), make_pair(0.22, 0.075), " View Leaderboards", font, 3, false, true);
    window.AddTextBox("Export", make_pair(0.75, 0.5), make_pair(0.1, 0.075), "  Export", font, 3, false, true);

    // Displays window
    window.GenerateWindow();
}

int main()
{
    GenerateInterface();
    return 0;
}
