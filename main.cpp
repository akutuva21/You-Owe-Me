// TODO: figure out how to simplify graphs
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

#include "List.h"
#include "Matrix.h"

using namespace std;

void menu()
{
    // int input;
    // cin >> input;
    // switch(input)
    // {
    //     case 1:
    //         break;

    //     case 2:
    //         break;

    //     case 3:
    //         break;

    //     case 4:
    //         break;

    //     case 5:
    //         break;
    // }

    AdjList list;
    AdjMatrix matrix;

    list.pushback("jonathan", "prayuj", 10);
    list.pushback("prayuj", "achyudhan", 20);
    list.pushback("achyudhan", "jonathan", 5);
    list.pushback("prayuj", "jonathan", 100);
    list.pushback("bob", "achyudan", 10);
    list.pushback("achyudan", "joe", 25);

    matrix.pushback("jonathan", "prayuj", 10);
    matrix.pushback("prayuj", "achyudan", 20);
    matrix.pushback("achyudan", "jonathan", 5);
    matrix.pushback("prayuj", "jonathan", 100);
    matrix.pushback("bob", "achyudan", 10);
    matrix.pushback("achyudan", "joe", 25);

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
    // cout << "Hello IRS" << endl;
}

int main()
{

    menu();
    
    // General flow structure
    // need something to read in incoming data as edges and append to list/matrix
    // maybe a density calculator for future reference (https://users.cecs.anu.edu.au/~xlx/teaching/css2013/network-density.html)

    return 0;
}