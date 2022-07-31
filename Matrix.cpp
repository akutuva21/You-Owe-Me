#include "Matrix.h"

int AdjMatrix::getIndexfromName(string name)
{
    return people[name];
}

string AdjMatrix::getNamefromIndex(int index)
{
    return indices[index];
}

auto AdjMatrix::getEdge(string from, string to)
{
    return matrix[people[from]][people[to]];
}

void AdjMatrix::pushback(string from, string to, double val)
{
    vector<string> temp;
    temp.push_back(from);
    temp.push_back(to);
    for (string person : temp)
    {
        if (people.find(person) == people.end()) 
        {
            people[person] = num_ppl;
            indices[num_ppl] = person;
            num_ppl++;

            // create a new column
            for (vector<double> &row : matrix) {
                row.push_back(0);
            }

            // create a new row
            vector<double> new_row(num_ppl, 0);
            matrix.push_back(new_row);
        }
    }

    matrix[people[from]][people[to]] += val;
    num_edges++;
}

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

void AdjMatrix::initalizeBalances()
{
    balances = vector<double>(num_ppl, 0);
}

vector<double> AdjMatrix::getBalances()
{
    return balances;
}

void AdjMatrix::printBalances()
{
    for (int i = 0; i < balances.size(); i++)
    {
        cout << getNamefromIndex(i) << ": " << balances[i] << endl;
    }
}

void AdjMatrix::simplifyMatrix()
{
    cout << "\nSimplifying Matrix..." << endl;
    cout << "Goodbye, Mr. Anderson...\n" << endl;
    initalizeBalances();
    minCashFlow();
}

void AdjMatrix::addSimpleEdge(int from, int to, double val)
{
    simple_edges.push_back(make_tuple(getNamefromIndex(from), getNamefromIndex(to), val));
}

void AdjMatrix::printSimpleEdges()
{
    for (auto i = simple_edges.begin(); i != simple_edges.end(); i++)
    {
        cout << get<0>(*i) << " pays " << get<2>(*i) << " to " << get<1>(*i) << endl;
    }
}

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

void AdjMatrix::calculateBalances()
{
    // Calculate the net amount to be paid to person 'p', and
    // stores it in amount[p]. The value of amount[p] can be
    // calculated by subtracting debts of 'p' from credits of 'p'
    for (int p = 0; p < matrix.size(); p++)
        for (int i = 0; i < matrix.size(); i++)
            balances[p] += (matrix[i][p] -  matrix[p][i]);
}

double AdjMatrix::truncate(double val)
{
    return (int)(val * 100) / 100.0;
}
 
// amount[p] indicates the net amount to be credited/debited to/from person 'p'
// If amount[p] is positive, then i'th person will amount[i]
// If amount[p] is negative, then i'th person will give  -amount[i]
void AdjMatrix::minCashFlowRec()
{
    double minimum = -1;
    // Find the indexes of minimum and maximum values in amount[]
    // amount[maxCredit] indicates the maximum amount to be credited
    // And amount[maxDebit] indicates the maximum amount to be debited
    // There must be positive and negative values in amount[]
    int maxCredit = maxIndex(), maxDebit = minIndex();
 
    // truncates the value of amount[maxCredit] and amount[maxDebit] to 2 decimal places
    balances[maxCredit] = truncate(balances[maxCredit]);
    balances[maxDebit] = truncate(balances[maxDebit]);
    
    // If both amounts are 0, then all amounts are settled
    minimum = min(truncate(-balances[maxDebit]), truncate(balances[maxCredit]));
    if ((balances[maxCredit] == 0 && balances[maxDebit] == 0) || (minimum == 0))
    {
        cout << "All amounts are settled" << endl;
        cout << "There is no spoon...\n" << endl;
        return;
    }
 
    // Determines the sign of how money is transfered
    balances[maxCredit] -= minimum;
    balances[maxDebit] += minimum;
    addSimpleEdge(maxDebit, maxCredit, minimum);
 
    // Recursion terminate as either amount[maxCredit] or amount[maxDebit] becomes 0
    minCashFlowRec();
}
 
// Given a set of persons as graph[] where graph[i][j] indicates
// the amount that person i needs to pay person j, this function
// finds and prints the minimum cash flow to settle all debts.
void AdjMatrix::minCashFlow()
{ 
    // cout << "Totals at Start:" << endl;
    // matrix.printAmounts();
    // cout << "\n" << endl;
    calculateBalances();
    minCashFlowRec();
}