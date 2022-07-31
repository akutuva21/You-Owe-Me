#include "List.h"
#include "SolveList.h"

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
    people.insert(from); // too lazy to figure this out so appending regardless of whether it's already in there
    people.insert(to);
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

void AdjList::initalizeAmount()
{
    for (auto iter = people.begin(); iter != people.end(); iter++)
    {
        amount[*iter] = 0;
    }
}

void AdjList::setAmount(unordered_map<string, double> amount)
{
    this->amount = amount;
}

unordered_map<string, double> AdjList::getAmount()
{
    return amount;
}

void AdjList::printAmounts()
{
    for (auto i = amount.begin(); i != amount.end(); i++)
    {
        cout << i->first << ": " << i->second << endl;
    }
}

void AdjList::simplifyList()
{
    cout << "\nsimplifying adjacency list" << endl;
    initalizeAmount();
    return minCashFlow(*this);
}

set<string> AdjList::getPeople()
{
    return people;
}

void AdjList::addSimpleEdge(string from, string to, double val)
{
    simple_edges.push_back(make_tuple(from, to, val));
}

void AdjList::printSimpleEdges()
{
    for (auto i = simple_edges.begin(); i != simple_edges.end(); i++)
    {
        cout << get<0>(*i) << " pays " << get<2>(*i) << " to " << get<1>(*i) << endl;
    }
}