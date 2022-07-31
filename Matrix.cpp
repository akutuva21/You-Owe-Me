#include "Matrix.h"
#include "SolveMatrix.h"

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

void AdjMatrix::simplifyMatrix()
{
    cout << "\nsimplifying matrix" << endl;
    initalizeAmount();
    return minCashFlow(*this);
}

void AdjMatrix::initalizeAmount()
{
    amount = vector<double>(num_ppl, 0);
}

vector<double> AdjMatrix::getAmount()
{
    return amount;
}

void AdjMatrix::printAmounts()
{
    for (int i = 0; i < amount.size(); i++)
    {
        cout << getNamefromIndex(i) << ": " << amount[i] << endl;
    }
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
    int min_index = min_element(amount.begin(),amount.end()) - amount.begin();
    return min_index;
}
 
int AdjMatrix::maxIndex()
{
    int max_index = max_element(amount.begin(),amount.end()) - amount.begin();
    return max_index;
}
 
// amount[p] indicates the net amount to be credited/debited to/from person 'p'
// If amount[p] is positive, then i'th person will amount[i]
// If amount[p] is negative, then i'th person will give  -amount[i]
void AdjMatrix::minCashFlowRec()
{
    // Find the indexes of minimum and maximum values in amount[]
    // amount[maxCredit] indicates the maximum amount to be credited
    // And amount[maxDebit] indicates the maximum amount to be debited
    // There must be positive and negative values in amount[]
    int maxCredit = maxIndex(), maxDebit = minIndex();
 
    // If both amounts are 0, then all amounts are settled
    if (amount[maxCredit] == 0 && amount[maxDebit] == 0)
    {
        cout << "All amounts are settled" << endl;
        return;
    }
 
    // Determines the sign of how money is transfered
    int minimum = min(-amount[maxDebit], amount[maxCredit]);
    amount[maxCredit] -= minimum;
    amount[maxDebit] += minimum;
    addSimpleEdge(maxDebit, maxCredit, minimum);
 
    // Recursion terminate as either amount[maxCredit] or amount[maxDebit] becomes 0
    minCashFlowRec();
}
 
// Given a set of persons as graph[] where graph[i][j] indicates
// the amount that person i needs to pay person j, this function
// finds and prints the minimum cash flow to settle all debts.
void AdjMatrix::minCashFlow()
{
    // Create an array amount[], initialize all value in it as 0.
    int size = matrix.size();
 
    // Calculate the net amount to be paid to person 'p', and
    // stores it in amount[p]. The value of amount[p] can be
    // calculated by subtracting debts of 'p' from credits of 'p'
    for (int p = 0; p < matrix.size(); p++)
        for (int i = 0; i < matrix.size(); i++)
            amount[p] += (matrix[i][p] -  matrix[p][i]);
 
    // cout << "Totals at Start:" << endl;
    // matrix.printAmounts();
    // cout << "\n" << endl;
    return minCashFlowRec();
}