#include "List.h"

double AdjList::getEdge(string from, string to)
{
    vector<Edge*> edges = list[from];
    for (Edge* edge : edges)
    {
        if (edge->first == to) return edge->second;
    }
    return 0;
}

void AdjList::pushback(string from, string to, double val)
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
        bool found = false;
        for (Edge* edge : list[from])
        {
            if (edge->first == to)
            {
                edge->second += val;
                found = true;
            }
        }
        if (!found) list[from].push_back(edge);
    }
    num_edges++;
}

void AdjList::printList()
{
    for (auto i = list.begin(); i != list.end(); i++)
    {
        cout << i->first << ": " << endl;
        for (Edge* edge : i->second)
        {
            cout << edge->first << "," << edge->second << endl;
        }
        cout << endl;
    }
}

void AdjList::simplifyList()
{

}