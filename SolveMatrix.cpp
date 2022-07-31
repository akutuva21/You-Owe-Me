#include "SolveMatrix.h"

/// Largely derived from https://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/

int minIndex(vector<double> arr)
{
    int min_index = min_element(arr.begin(),arr.end()) - arr.begin();
    return min_index;
}
 
int maxIndex(vector<double> arr)
{
    int max_index = max_element(arr.begin(),arr.end()) - arr.begin();
    return max_index;
}
 
// amount[p] indicates the net amount to be credited/debited to/from person 'p'
// If amount[p] is positive, then i'th person will amount[i]
// If amount[p] is negative, then i'th person will give  -amount[i]
void minCashFlowRec(AdjMatrix& matrix, vector<double> amount)
{
    // Find the indexes of minimum and maximum values in amount[]
    // amount[maxCredit] indicates the maximum amount to be credited
    // And amount[maxDebit] indicates the maximum amount to be debited
    // There must be positive and negative values in amount[]
    int maxCredit = maxIndex(amount), maxDebit = minIndex(amount);
 
    // If both amounts are 0, then all amounts are settled
    if (amount[maxCredit] == 0 && amount[maxDebit] == 0)
    {
        cout << "All amounts are settled" << endl;
        matrix.setAmount(amount);
        return;
    }
 
    // Determines the sign of how money is transfered
    int minimum = min(-amount[maxDebit], amount[maxCredit]);
    amount[maxCredit] -= minimum;
    amount[maxDebit] += minimum;
    matrix.addSimpleEdge(maxDebit, maxCredit, minimum);
 
    // Recursion terminate as either amount[maxCredit] or amount[maxDebit] becomes 0
    minCashFlowRec(matrix, amount);
}
 
// Given a set of persons as graph[] where graph[i][j] indicates
// the amount that person i needs to pay person j, this function
// finds and prints the minimum cash flow to settle all debts.
void minCashFlow(AdjMatrix& matrix)
{
    // Create an array amount[], initialize all value in it as 0.
    auto graph = matrix.getMatrix();
    int N = graph.size();
    auto amount = matrix.getAmount();
 
    // Calculate the net amount to be paid to person 'p', and
    // stores it in amount[p]. The value of amount[p] can be
    // calculated by subtracting debts of 'p' from credits of 'p'
    for (int p = 0; p < N; p++)
        for (int i = 0; i < N; i++)
            amount[p] += (graph[i][p] -  graph[p][i]);
 
    // cout << "Totals at Start:" << endl;
    matrix.setAmount(amount);
    // matrix.printAmounts();
    // cout << "\n" << endl;
    return minCashFlowRec(matrix, amount);
}