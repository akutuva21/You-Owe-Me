// TODO: figure out how to simplify graphs
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <algorithm>

#include "List.h"
#include "Matrix.h"

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
    list.simplifyList();
    list.printEdgesByWeight();
}

void add(string line) {
    size_t pos;
    size_t pos2;
    pos = line.find(" ");
    string from = line.substr(0, pos);
    pos2 = line.find(" ", pos + 1);
    string to = line.substr(pos + 1, pos2 - pos - 1);
    double amount = stod(line.substr(pos2 + 1));
    cout << from << ", " << to << ": " << amount << endl;

    // size_t pos;
    // pos = line.find(" ");
    // string from = line.substr(0, pos);
    // line.erase(0, pos + 1);
    // pos = line.find(" ");
    // string to = line.substr(0, pos);
    // line.erase(0, pos + 1);
    // double amount = stod(line);
    // cout << "hi" << from << "hi" << endl;
    // cout << "hi" << to << "hi" << endl;
    // cout << "hi" << amount << "hi" << endl;

    list.pushback(from, to, amount);
    matrix.pushback(from, to, amount);
}

int main()
{
    string input;
    int inputInt;
    while (1) {
        getline(cin, input);
        try {
            inputInt = stoi(input);
        }
        catch (...) {
            cout << "not a valid option!" << endl;
            continue;
        }
        switch(inputInt)
        {
            case 1:
            {
                string line;
                ifstream file("./hugetransactions.txt");
                while (getline(file, line)) {
                    add(line);
                }
                file.close();
                //matrix.simplifyMatrix();
                // list.simplifyList();
                // list.printEdgesByWeight();
                cout << "File Read!" << endl;
                break;
            }
            case 2:
            {
                string line;
                getline(cin, line);
                while (line != "exit") {
                    try {
                        add(line);
                    }
                    catch (...) {
                        cout << "error" << endl;
                        continue;
                    }
                    cout << "added transaction!" << endl;
                    getline(cin, line);
                }
                break;
            }

            case 3:
            {
                list.simplifyList();
                break;
            }

            case 4:
            {
                list.printEdgesByWeight();
                break;
            }

            case 5:
            {
                break;
            }

            case 6:
            {
                return 0;
            }

            case 99:
            {
                test();
                break;
            }
            
            default:
            {
                cout << "not a valid option!" << endl;
                break;
            }
        }
    }
    return 0;
}
    // prayuj : -110
    // bob : -10
    // jonathan : 95
    // achyudan : 0
    // joe : 25

    // prayuj -> jonathan : 95
    // prayuj -> achyudan : 15
    // bob -> achyudan : 10

    // vector<pair<string, double>> <- heap (['armando', 50], ['achyudhan', 20])
    // (1) -> read from text file (import)
    // (2) -> insert transaction (edge)
    // (3) -> simplify + print new graph (simplify at end)
    // (4) -> calls (3), then sorts it to view leaderboards
    // (5) -> export simplified graph to a text file, launch web browser (maybe)

//int main()
//{
    //while (1)
    //{
        //menu();
    //}
    
    // General flow structure
    // need something to read in incoming data as edges and append to list/matrix
    // maybe a density calculator for future reference (https://users.cecs.anu.edu.au/~xlx/teaching/css2013/network-density.html)

   // return 0;
//}
