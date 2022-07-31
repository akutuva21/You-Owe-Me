// TODO: figure out how to simplify graphs
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

#include "List.h"
#include "Matrix.h"

using namespace std;

typedef tuple<string, string, int> edge;

// void test(AdjList& list, AdjMatrix& matrix)
// {
//     vector<edge> edges;
//     edges.push_back(make_tuple("jonathan", "prayuj", 10));
//     edges.push_back(make_tuple("prayuj", "achyudhan", 20));
//     edges.push_back(make_tuple("achyudhan", "jonathan", 5));
//     edges.push_back(make_tuple("prayuj", "jonathan", 100));
//     edges.push_back(make_tuple("bob", "achyudhan", 10));
//     edges.push_back(make_tuple("achyudhan", "joe", 25));

//     for (auto edge : edges)
//     {
//         list.pushback(get<0>(edge), get<1>(edge), get<2>(edge));
//         matrix.pushback(get<0>(edge), get<1>(edge), get<2>(edge));
//     }
// }

void menu()
{

    AdjList list;
    AdjMatrix matrix;

    int input;
    cin >> input;
    switch(input)
    {
        case 1:
        {
            string line;
            ifstream file("./hugetransactions.txt");
            while (getline(file, line)) {
                size_t pos;
                pos = line.find(' ');
                string from = line.substr(0, pos);
                line.erase(0, pos + 1);
                pos = line.find(' ');
                string to = line.substr(0, pos);
                line.erase(0, pos + 1);
                double amount = stod(line);
                list.pushback(from, to, amount);
                matrix.pushback(from, to, amount);
            }
            file.close();
            break;
        }
        case 2:
        {
            break;
        }

        case 3:
        {
            break;
        }

        case 4:
        {
            break;
        }

        case 5:
        {
            break;
        }
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
}

int main()
{

    menu();
    
    // General flow structure
    // need something to read in incoming data as edges and append to list/matrix
    // maybe a density calculator for future reference (https://users.cecs.anu.edu.au/~xlx/teaching/css2013/network-density.html)

    return 0;
}
