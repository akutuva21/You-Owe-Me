#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#pragma once

// TO DO: add a function to track matrix changes for the simplified graph maybe

using namespace std;

class AdjMatrix
{
    private:
        vector<vector<double>> matrix;
        int num_ppl = 0;
        int num_edges = 0;
        unordered_map<string, int> people;
        vector<double> amount; // stores the total balance to be paid by someone
        
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
};