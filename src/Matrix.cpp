#include "../headers/Matrix.h"

// returns the index of the person with the given name in the matrix
int AdjMatrix::getIndexfromName(string name)
{
    return people[name];
}

// returns the name of the person with the given index in the matrix
string AdjMatrix::getNamefromIndex(int index)
{
    return indices[index];
}

// returns the weight of the directed edge between two people in the matrix
auto AdjMatrix::getEdge(string from, string to)
{
    return matrix[people[from]][people[to]];
}

// adds an edge to the Adjacency Matrix
void AdjMatrix::pushback(string from, string to, double val)
{
    vector<string> temp{from, to};
    for (string person : temp)
    {
        if (people.find(person) == people.end()) // if the person is not in the matrix
        {
            people[person] = num_ppl;
            indices[num_ppl] = person;
            num_ppl++;

            // create a new column
            for (vector<double> &row : matrix)
            {
                row.push_back(0);
            }
            // 1 + 2 + 3 + ... V

            // create a new row
            vector<double> new_row(num_ppl, 0);
            matrix.push_back(new_row);
        }
    }

    matrix[people[from]][people[to]] += val; // if edge already exists, add to it
    num_edges++;                             // increments number of edges
}

// prints the contents of the Adjacency Matrix - debugging purposes
void AdjMatrix::printMatrix()
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// sets all balances to be 0 for all people in the Adjacency Matrix - O(1)
void AdjMatrix::initalizeBalances()
{
    balances = vector<double>(num_ppl, 0);
}

// prints the initial balances of all people in the Adjacency Matrix - debugging purposes
void AdjMatrix::printInitialBalances()
{
    sort(initial_balances.begin(), initial_balances.end());
    for (int i = 0; i < initial_balances.size(); i++)
    {
        cout << initial_balances[i] << " ";
    }
    cout << endl;
}

// prints the balances of all people in the Adjacency Matrix - debugging purposes
void AdjMatrix::printBalances()
{
    for (int i = 0; i < balances.size(); i++)
    {
        cout << getNamefromIndex(i) << ": " << balances[i] << endl;
    }
}

// driver code to simplify the matrix
void AdjMatrix::simplifyMatrix()
{
    simple_edges.clear();
    initalizeBalances();
    minFlow();
}

// adds a simple edge based on the given parameters to the matrix - O(1)
void AdjMatrix::addSimpleEdge(int from, int to, double val)
{
    simple_edges.push_back(make_tuple(getNamefromIndex(from), getNamefromIndex(to), val));
}

// prints all the simple edges in the matrix - debugging purposes
void AdjMatrix::printSimpleEdges()
{
    for (auto i = simple_edges.begin(); i != simple_edges.end(); i++)
    {
        cout << get<0>(*i) << " pays " << get<2>(*i) << " to " << get<1>(*i) << endl;
    }
}

// returns the index of the individual owing the most money in the matrix
int AdjMatrix::minIndex()
{
    int min = 0;
    for (int i = 1; i < balances.size(); i++)
    {
        if (balances[i] < balances[min])
        {
            min = i;
        }
    }
    return min;
}

// returns the index of the individual owed the most money in the matrix
int AdjMatrix::maxIndex()
{
    int max = 0;
    for (int i = 1; i < balances.size(); i++)
    {
        if (balances[i] > balances[max])
        {
            max = i;
        }
    }
    return max;
}

// calculates the aggregate balances for each person prior to simplification
void AdjMatrix::calculateBalances()
{
    for (int p = 0; p < matrix.size(); p++)
        for (int i = 0; i < matrix.size(); i++)
            balances[p] += (matrix[i][p] - matrix[p][i]); // adding from people owed money and subtracting from the person owing money
}

// truncates a decimal to 2 decimal places
double AdjMatrix::truncate(double val)
{
    return (int)(val * 100) / 100.0;
}

// recursive helper function to find the minimum cash flow required to make all balances 0
// developed based on algorithm from https://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/
void AdjMatrix::minFlowHelper()
{
    double minimum = -1;
    int maxCredit = maxIndex();
    int maxDebit = minIndex();

    // truncates the value of amount[maxCredit] and amount[maxDebit] to 2 decimal places
    // balances[maxCredit] = truncate(balances[maxCredit]);
    // balances[maxDebit] = truncate(balances[maxDebit]);

    // If both amounts are 0, then all amounts are settled
    minimum = min(truncate(-balances[maxDebit]), truncate(balances[maxCredit]));

    // Recursion terminate as either balances[max_credits] or balances[max_debits] becomes 0 or if the money transfered between is 0
    if ((balances[maxCredit] == 0 && balances[maxDebit] == 0) || (minimum == 0))
    {
        return;
    }

    // The person owed the most money is paid and vice-versa
    balances[maxCredit] -= minimum;
    balances[maxDebit] += minimum;
    addSimpleEdge(maxDebit, maxCredit, minimum);

    // Recursion terminate as either amount[maxCredit] or amount[maxDebit] becomes 0
    minFlowHelper();
}

// Finds and prints the minimum cash flow to settle all debts.
void AdjMatrix::minFlow()
{
    calculateBalances();
    // Recursively lowers balances until all balances are 0
    minFlowHelper();
}
