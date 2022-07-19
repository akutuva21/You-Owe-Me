#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class AdjacencyList
{
    typedef std::pair<std::string, double> Edge;
    
    private:
        // Achyudan : (people : [("jonathan", 10)])
        unordered_map<string, vector<Edge*>> list;
    public:
        AdjacencyList() {};
        auto getList() { return list; }
        void pushback(std::string from, std::string to, double val);
        double getEdge(std::string from, std::string to);
};

double AdjacencyList::getEdge(std::string from, std::string to)
{
    vector<Edge*> edges = list[from];
    for (Edge* edge : edges)
    {
        if (edge->first == to) return edge->second;
    }
    return 0;
}

void AdjacencyList::pushback(std::string from, std::string to, double val)
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
}

class AdjMatrix
{
    private:
        std::vector<std::vector<double>> matrix;
        int num_ppl = 0;
        unordered_map<string, int> people;
    public:
        AdjMatrix() {};
        auto getMatrix() { return matrix; }
        void pushback(std::string from, std::string to, double val);
        double getEdge(std::string from, std::string to);
};

double AdjMatrix::getEdge(std::string from, std::string to)
{
    return matrix[people[from]][people[to]];
}

void AdjMatrix::pushback(std::string from, std::string to, double val)
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
}

int main()
{
    std::cout << "Hello IRS" << std::endl;
    
    // General flow structure
    // need something to read in incoming data as edges and append to list/matrix
    // maybe a density calculator for future reference (https://users.cecs.anu.edu.au/~xlx/teaching/css2013/network-density.html)

    return 0;
}