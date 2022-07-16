#include <iostream>
#include <forward_list>
#include <vector>
#include <string>

class Container // potentially useless, maybe not needed
{
    private:
        unsigned int num_ppl;
        std::vector<std::string> people;
    public:
        Container() {};
        auto getPeople() { return people; }
};

class AdjacencyList : public Container
{
    private:
        std::vector<std::forward_list<std::pair<std::string, double>>> list; // vector of linked lists containing doubles
        // Not sure whether this idea is faster/better than just using a map tbh
    public:
        AdjacencyList() {};
        auto getList() { return list; }
        void pushback(std::string from, std::string to, double val);
        double getEdge(std::string from, std::string to);
};

double AdjacencyList::getEdge(std::string from, std::string to)
{
    auto list = getList();
    // should generally iterate through each container
    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        if (iter->front().first == from)
        {
            for (auto iter2 = iter->begin(); iter2 != iter->end(); iter2++)
            {
                if (iter2->first == to)
                {
                    return iter2->second;
                }
            }
        }
    }
    return 0;
}

void AdjacencyList::pushback(std::string from, std::string to, double val)
{
    // Either appends from at the end of to if to LL exists or creates new linked list, setting to as the head
}

class AdjMatrix : public Container
{
    private:
        std::vector<std::vector<double>> matrix;
    public:
        AdjMatrix() {};
        auto getMatrix() { return matrix; }
        void pushback(std::string from, std::string to, double val);
        double getEdge(std::string from, std::string to);
};

double AdjMatrix::getEdge(std::string from, std::string to)
{
    auto m = getMatrix();
    auto people = getPeople();
    int from_index, to_index;
    for (int i = 0; i < people.size(); i++)
    {
        if (people[i] == from) from_index = i;
        if (people[i] == to) to_index = i; 
    }
    return m[from_index][to_index];
}

void AdjMatrix::pushback(std::string from, std::string to, double val)
{
    auto m = getMatrix();
    auto people = getPeople();
    int from_index, to_index;
    for (int i = 0; i < people.size(); i++)
    {
        if (people[i] == from) from_index = i;
        if (people[i] == to) to_index = i; 
    }
    if (m[from_index][to_index])
    {
        m[from_index][to_index] += val;
    }
    else
    {
        // create new person and append to people vector
        // create new row and/or column (maybe helper function needed)
    }
}

int main()
{
    std::cout << "Hello World" << std::endl;
    
    // General flow structure
    // need something to read in incoming data as edges and append to list/matrix
    // maybe a density calculator for future reference (https://users.cecs.anu.edu.au/~xlx/teaching/css2013/network-density.html)

    return 0;
}