#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class AdjMatrix
{
    private:
        vector<vector<double>> matrix;
        int num_ppl = 0;
        int num_edges = 0;
        unordered_map<string, int> people;
    public:
        AdjMatrix() {};
        auto getMatrix() { return matrix; }
        void pushback(string from, string to, double val);
        double getEdge(string from, string to);
        void printMatrix();
        void simplifyMatrix();
};