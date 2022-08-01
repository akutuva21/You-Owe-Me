#include "../headers/List.h"

// returns the weight of the corresponding edge
double AdjList::getEdge(string from, string to)
{
    vector<Edge *> edges = list[from];
    for (Edge *edge : edges)
    {
        if (edge->first == to)
            return edge->second;
    }
    return 0;
}

// pushes back an additional edge to the Adjacency List
void AdjList::pushback(string from, string to, double val)
{
    // Either appends from at the end of to if to LL exists or creates new linked list, setting to as the head
    Edge *edge = new Edge(to, val);
    if (list.find(from) == list.end())
    {
        vector<Edge *> edges = {edge};
        list[from] = edges;
    }
    else
    {
        bool found = false;
        for (Edge *edge : list[from])
        {
            if (edge->first == to)
            {
                edge->second += val;
                found = true;
            }
        }
        if (!found)
            list[from].push_back(edge);
    }
    people.insert(from); // too lazy to figure this out so appending regardless of whether it's already in there
    people.insert(to);
    num_edges++;
}

// prints the contents of the Adjacency List
void AdjList::printList()
{
    for (auto i = list.begin(); i != list.end(); i++)
    {
        cout << i->first << ": " << endl;
        for (Edge *edge : i->second)
        {
            cout << edge->first << "," << edge->second << endl;
        }
        cout << endl;
    }
}

// sets all balances to be 0 for all people in the Adjacency List
void AdjList::initializeBalances()
{
    for (auto iter = people.begin(); iter != people.end(); iter++)
    {
        balances[*iter] = 0;
    }
}

// getter function for balances
unordered_map<string, double> AdjList::getBalances()
{
    return balances;
}

// prints all the balances for all people in the Adjacency List
void AdjList::printBalances()
{
    for (auto i = balances.begin(); i != balances.end(); i++)
    {
        cout << i->first << ": " << i->second << endl;
    }
}

// driver code to conduct the simplification of the Adjacency List
void AdjList::simplifyList()
{
    cout << "simplifying adjacency list" << endl;
    initializeBalances();
    minFlow();
}

// getter function for the number of people
set<string> AdjList::getPeople()
{
    return people;
}

// getter function for the addition of a "simple edge" (edge after simplification done)
void AdjList::addSimpleEdge(string from, string to, double val)
{
    simple_edges.push_back(make_tuple(from, to, val));
}

// prints the contents of the simple edges vector
void AdjList::printSimpleEdges()
{
    for (auto i = simple_edges.begin(); i != simple_edges.end(); i++)
    {
        cout << get<0>(*i) << " pays " << get<2>(*i) << " to " << get<1>(*i) << endl;
    }
}

// getter function for simple edges vector
vector<tuple<string, string, double>> AdjList::getSimpleEdges()
{
    return simple_edges;
}

// prints all of the simple edges by weight after sorting by weight
void AdjList::printEdgesByWeight()
{
    sort(simple_edges.begin(), simple_edges.end(), [](auto const &t1, auto const &t2)
         { return get<2>(t1) > get<2>(t2); });

    printSimpleEdges();
}

// prints all the initial balances (top k creditors and debtors) after sorting by balance
void AdjList::printInitialBalances(int k)
{
    auto elems = getLeaderboards();

    cout << "These are the top " << k << " people who are owed money:" << endl;
    for (int i = 0; i < k; i++)
    {
        cout << elems[i].first << " is owed $" << elems[i].second << endl;
    }
    cout << "\n";

    cout << "These are the top " << k << " people who owe money:" << endl;
    for (int i = elems.size() - 1; i > elems.size() - 1 - k; i--)
    {
        cout << elems[i].first << " owes $" << 0 - elems[i].second << endl;
    }
}

// getter function for sorted initial balances
vector<pair<string, double>> AdjList::getLeaderboards()
{
    vector<pair<string, double>> elems(initial_balances.begin(), initial_balances.end());
    sort(elems.begin(), elems.end(), [](auto const &t1, auto const &t2)
         { return t1.second > t2.second; });
    return elems;
}

// finds the name of the person owing the most money
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

// finds the name of the person owed the most money
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

// calculates the aggregate balances for each person prior to simplification
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
    initial_balances = balances;
}

// truncates a decimal to 2 decimal places
double AdjList::truncate(double val)
{
    return (int)(val * 100) / 100.0;
}

// recursive helper function to find the minimum cash flow required to make all balances 0
// developed based on algorithm from https://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/
void AdjList::minFlowHelper()
{
    double minimum = -1;
    string max_credits = maxIndex();
    string max_debits = minIndex();

    balances[max_credits] = truncate(balances[max_credits]);
    balances[max_debits] = truncate(balances[max_debits]);

    minimum = min(-balances[max_debits], balances[max_credits]);
    // Recursion terminate as either balances[max_credits] or balances[max_debits] becomes 0 or if the money transfered between is 0
    if ((balances[max_credits] == 0 && balances[max_debits] == 0) || (minimum == 0))
    {
        cout << "All amounts are settled" << endl;
        return;
    }

    // The person owed the most money is paid and vice-versa
    balances[max_credits] -= minimum;
    balances[max_debits] += minimum;
    addSimpleEdge(max_debits, max_credits, minimum);

    // Recursion terminate as either amount[maxCredit] or amount[maxDebit] becomes 0
    minFlowHelper();
}

// Finds and prints the minimum cash flow to settle all debts.
void AdjList::minFlow()
{
    // Calculates the net aggregate balances for each person
    // cout << "Totals at Start:" << endl;
    calculateBalances();
    // printAmounts(); // prints out all the amounts
    // Recursively lowers balances until all balances are 0
    minFlowHelper();
}

// destructor function for the Adjacency List
AdjList::~AdjList()
{
    for (auto i = list.begin(); i != list.end(); i++)
    {
        for (Edge *edge : i->second)
        {
            delete edge;
        }
    }
}