#include "Matrix.h"

double AdjMatrix::getEdge(string from, string to)
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
    
}