#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#pragma once

// TO DO: add a function to track how much is paid to each (maybe could modify existing graph)

using namespace std;

class AdjMatrix
{
    private:
        vector<vector<double>> matrix;
        int num_ppl = 0;
        int num_edges = 0;
        unordered_map<string, int> people;
        unordered_map<int, string> indices;
        vector<double> amount; // stores the total balance to be paid by someone
        vector<tuple<string, string, double>> simple_edges;
        
    public:
        AdjMatrix() {};
        auto getMatrix() { return matrix; }
        int getIndexfromName(string name);
        string getNamefromIndex(int index);
        void pushback(string from, string to, double val);
        auto getEdge(string from, string to);
        void printMatrix();
        void simplifyMatrix();
        void initalizeAmount();
        void setAmount(vector<double> amt);
        vector<double> getAmount();
        void printAmounts();
        void addSimpleEdge(int from, int to, double val);
        void printSimpleEdges();
};