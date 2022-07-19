// TODO: figure out how to simplify graphs

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

class AdjacencyList
{
    typedef pair<string, double> Edge;
    
    private:
        // Achyudhan : (people : [("jonathan", 10), ("prayuj", 15)])
        unordered_map<string, vector<Edge*>> list;
        int num_edges = 0;
    public:
        AdjacencyList() {};
        auto getList() { return list; }
        void pushback(string from, string to, double val);
        double getEdge(string from, string to);
};

double AdjacencyList::getEdge(string from, string to)
{
    vector<Edge*> edges = list[from];
    for (Edge* edge : edges)
    {
        if (edge->first == to) return edge->second;
    }
    return 0;
}

void AdjacencyList::pushback(string from, string to, double val)
{
    // Either appends from at the end of to if to LL exists or creates new linked list, setting to as the head
    Edge* edge = new Edge(to, val);
    if (list.find(from) == list.end()) 
    {
        vector<Edge*> edges = {edge};
        list[from] = edges;
    }
    else
    {
        list[from].push_back(edge);
    }
    num_edges++;
}

class AdjMatrix
{
    private:
        vector<vector<double>> matrix;
        int num_ppl = 0;
        int num_edges = 0;
        unordered_map<string, int> people;
    public:
        AdjMatrix() {};
        auto getMatrix() { return matrix; }
        void pushback(string from, string to, double val);
        double getEdge(string from, string to);
};

double AdjMatrix::getEdge(string from, string to)
{
    return matrix[people[from]][people[to]];
}

void AdjMatrix::pushback(string from, string to, double val)
{
    if (people.find(from) == people.end()) 
    {
        people[from] = num_ppl;
        num_ppl++;

        // create a new column
        for (vector<double> row : matrix) {
            row.push_back(0);
        }

        // create a new row
        vector<double> new_row(num_ppl, 0);
        matrix.push_back(new_row);
    }
    matrix[people[from]][people[to]] += val;
    num_edges++;
}

void menu()
{
    int input;
    cin >> input;
    switch(input)
    {
        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;
    }

    // vector<pair<string, double>> <- heap (['armando', 50], ['achyudhan', 20])
    // (1) -> read from text file (import)
    // (2) -> insert transaction (edge)
    // (3) -> simplify + print new graph (simplify at end)
    // (4) -> calls (3), then sorts it to view leaderboards
    // (5) -> export simplified graph to a text file, launch web browser (maybe)
    cout << "Hello IRS" << endl;
}

int main()
{

    menu();
    
    // General flow structure
    // need something to read in incoming data as edges and append to list/matrix
    // maybe a density calculator for future reference (https://users.cecs.anu.edu.au/~xlx/teaching/css2013/network-density.html)

    return 0;
}