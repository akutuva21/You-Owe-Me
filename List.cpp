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

void AdjList::initializeBalances()
{
    for (auto iter = people.begin(); iter != people.end(); iter++)
    {
        balances[*iter] = 0;
    }
}

void AdjList::setBalances(unordered_map<string, double> balances)
{
    this->balances = balances;
}

unordered_map<string, double> AdjList::getBalances()
{
    return balances;
}

void AdjList::printBalances()
{
    for (auto i = balances.begin(); i != balances.end(); i++)
    {
        cout << i->first << ": " << i->second << endl;
    }
}

void AdjList::simplifyList()
{
    cout << "simplifying adjacency list" << endl;
    initializeBalances();
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
    double min_val = INT_MAX;
    for (auto i = balances.begin(); i != balances.end(); i++)
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
    double max_val = INT_MIN;
    for (auto i = balances.begin(); i != balances.end(); i++)
    {
        if (i->second > max_val)
        {
            max = i->first;
            max_val = i->second;
        }
    }
    return max;
}

void AdjList::calculateBalances()
{
    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        for (auto edge : iter->second)
        {
            balances[iter->first] -= edge->second; // subtracting from the person who owes money
            balances[edge->first] += edge->second; // adding to the person who is owed money
        }
    }
}

double AdjList::truncate(double val)
{
    return (int)(val * 100) / 100.0;
}

// balances[p] indicates the net balances to be credited/debited to/from person 'p'
// If balances[p] is positive, then i'th person will balances[i]
// If balances[p] is negative, then i'th person will give  -balances[i]
void AdjList::minCashFlowRec()
{
    double minimum = -1;
    // Find the indexes of minimum and maximum values in balances[]
    // balances[max_credits] indicates the maximum balances to be credited
    // And balances[max_debits] indicates the maximum balances to be debited
    // There must be positive and negative values in balances[]
    string max_credits = maxIndex();
    string max_debits = minIndex();
 
    // If both amounts are 0, then all amounts are settled
    balances[max_credits] = truncate(balances[max_credits]);
    balances[max_debits] = truncate(balances[max_debits]);

    minimum = min(-balances[max_debits], balances[max_credits]);
    if ((balances[max_credits] == 0 && balances[max_debits] == 0) || (minimum == 0))
    {
        cout << "All amounts are settled" << endl;
        return;
    }
 
    // Determines the sign of how money is transfered
    balances[max_credits] -= minimum;
    balances[max_debits] += minimum;
     
    addSimpleEdge(max_debits, max_credits, minimum);
 
    // Recursion terminate as either balances[max_credits] or balances[max_debits] becomes 0
    minCashFlowRec();
}
 
// Given a set of persons as graph[] where graph[i][j] indicates
// the balances that person i needs to pay person j, this function
// finds and prints the minimum cash flow to settle all debts.
void AdjList::minCashFlow()
{
    // Calculate the net balances to be paid to person 'p', and
    // stores it in balances[p]. The value of balances[p] can be
    // calculated by subtracting debts of 'p' from credits of 'p'
    // cout << "Totals at Start:" << endl;
    calculateBalances();
    // printAmounts(); // prints out all the amounts
    // cout << "\n" << endl;
    minCashFlowRec();
}

AdjList::~AdjList()
{
    for (auto i = list.begin(); i != list.end(); i++)
    {
        for (Edge* edge : i->second)
        {
            delete edge;
        }
    } 
}