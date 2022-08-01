#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#pragma once

using namespace std;

class AdjMatrix
{
    private:
        vector<vector<double>> matrix;
        int num_ppl = 0;
        int num_edges = 0;
        unordered_map<string, int> people;
        unordered_map<int, string> indices;
        vector<double> balances; // stores the total balance to be paid by someone
        vector<tuple<string, string, double>> simple_edges;
        vector<double> initial_balances; // stores the initial total balance to be paid by someone
        
    public:
        AdjMatrix() {};
        auto getMatrix() { return matrix; }
        int getIndexfromName(string name);
        string getNamefromIndex(int index);
        auto getEdge(string from, string to);
        auto getNumEdges() { return num_edges; }

        void pushback(string from, string to, double val);
        void addSimpleEdge(int from, int to, double val);
        void simplifyMatrix();
        
        void initalizeBalances();
        void calculateBalances();

        void printMatrix();
        void printBalances();
        void printInitialBalances(int top_k);
        void printSimpleEdges();

        int minIndex();
        int maxIndex();
        double truncate(double val);

        void minCashFlowRec();
        void minCashFlow();
};