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
    cout << "simplifying adjacency list" << endl;
    initalizeAmount();
    minCashFlow();
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

vector<tuple<string, string, double>> AdjList::getSimpleEdges()
{
    return simple_edges;
}

void AdjList::printEdgesByWeight()
{
    sort(simple_edges.begin(), simple_edges.end(), [](auto const &t1, auto const &t2) {
        return get<2>(t1) > get<2>(t2);
    });
    
    printSimpleEdges();
}

string AdjList::minIndex()
{
    string min = "";
    double min_val = 0;
    for (auto i = amount.begin(); i != amount.end(); i++)
    {
        if (i->second < min_val)
        {
            min = i->first;
            min_val = i->second;
        }
    }
    return min;
}
 
string AdjList::maxIndex()
{
    string max = "";
    double max_val = 0;
    for (auto i = amount.begin(); i != amount.end(); i++)
    {
        if (i->second > max_val)
        {
            max = i->first;
            max_val = i->second;
        }
    }
    return max;    
}

void AdjList::calculateAmount()
{
    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        for (auto edge : iter->second)
        {
            amount[iter->first] -= edge->second; // subtracting from the person who owes money
            amount[edge->first] += edge->second; // adding to the person who is owed money
        }
    }
}
 
// amount[p] indicates the net amount to be credited/debited to/from person 'p'
// If amount[p] is positive, then i'th person will amount[i]
// If amount[p] is negative, then i'th person will give  -amount[i]
void AdjList::minCashFlowRec()
{
    // Find the indexes of minimum and maximum values in amount[]
    // amount[maxCredit] indicates the maximum amount to be credited
    // And amount[maxDebit] indicates the maximum amount to be debited
    // There must be positive and negative values in amount[]
    string maxCredit = maxIndex(), maxDebit = minIndex();
 
    // If both amounts are 0, then all amounts are settled
    if (amount[maxCredit] == 0 && amount[maxDebit] == 0)
    {
        cout << "All amounts are settled" << endl;
        return;
    }
 
    // Determines the sign of how money is transfered
    double minimum = min(-amount[maxDebit], amount[maxCredit]);
    amount[maxCredit] -= minimum;
    amount[maxDebit] += minimum;
     
    addSimpleEdge(maxDebit, maxCredit, minimum);
 
    // Recursion terminate as either amount[maxCredit] or amount[maxDebit] becomes 0
    minCashFlowRec();
}
 
// Given a set of persons as graph[] where graph[i][j] indicates
// the amount that person i needs to pay person j, this function
// finds and prints the minimum cash flow to settle all debts.
void AdjList::minCashFlow()
{
    // Calculate the net amount to be paid to person 'p', and
    // stores it in amount[p]. The value of amount[p] can be
    // calculated by subtracting debts of 'p' from credits of 'p'
    // cout << "Totals at Start:" << endl;
    calculateAmount();
    // printAmounts(); // prints out all the amounts
    // cout << "\n" << endl;
    minCashFlowRec();
}