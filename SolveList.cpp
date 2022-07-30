#include "SolveList.h"

/// Largely derived from https://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/

string minIndex(unordered_map<string, double> amount)
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
 
string maxIndex(unordered_map<string, double> amount)
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

unordered_map<string, double> calculateAmount(AdjList adjlist)
{
    auto list = adjlist.getList();
    auto amount = adjlist.getAmount();
    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        for (auto edge : iter->second)
        {
            amount[iter->first] -= edge->second; // subtracting from the person who owes money
            amount[edge->first] += edge->second; // adding to the person who is owed money
        }
    }
    return amount;
}
 
// amount[p] indicates the net amount to be credited/debited to/from person 'p'
// If amount[p] is positive, then i'th person will amount[i]
// If amount[p] is negative, then i'th person will give  -amount[i]
void minCashFlowRec(AdjList list, unordered_map<string, double> amount)
{
    // Find the indexes of minimum and maximum values in amount[]
    // amount[maxCredit] indicates the maximum amount to be credited
    // And amount[maxDebit] indicates the maximum amount to be debited
    // There must be positive and negative values in amount[]
    string maxCredit = maxIndex(amount), maxDebit = minIndex(amount);
 
    // If both amounts are 0, then all amounts are settled
    if (amount[maxCredit] == 0 && amount[maxDebit] == 0)
    {
        cout << "All amounts are settled" << endl;
        list.setAmount(amount);
        return;
    }
 
    // Determines the sign of how money is transfered
    int minimum = min(-amount[maxDebit], amount[maxCredit]);
    amount[maxCredit] -= minimum;
    amount[maxDebit] += minimum;
 
    // Prints who pays who
    cout << maxDebit << " pays " << minimum
         << " to " << maxCredit << endl;
 
    // Recursion terminate as either amount[maxCredit] or amount[maxDebit] becomes 0
    minCashFlowRec(list, amount);
}
 
// Given a set of persons as graph[] where graph[i][j] indicates
// the amount that person i needs to pay person j, this function
// finds and prints the minimum cash flow to settle all debts.
void minCashFlow(AdjList list)
{
    // Calculate the net amount to be paid to person 'p', and
    // stores it in amount[p]. The value of amount[p] can be
    // calculated by subtracting debts of 'p' from credits of 'p'
    cout << "Totals at Start:" << endl;
    auto amount = calculateAmount(list);
    list.setAmount(amount);
    list.printAmounts();
    cout << "\n" << endl;
    return minCashFlowRec(list, amount);
}