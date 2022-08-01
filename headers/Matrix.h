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
        vector<vector<double>> matrix; // adjacency matrix
        int num_ppl = 0; // number of people in the graph (equivalent to the number of rows/columns in the matrix)
        int num_edges = 0; // number of edges in the graph
        unordered_map<string, int> people; // map of people to their indices in the matrix
        unordered_map<int, string> indices; // map of indices to their people in the matrix
        vector<double> balances; // stores the total balance to be paid by someone
        vector<tuple<string, string, double>> simple_edges; // stores the simple edges (after simplification)
        vector<double> initial_balances; // stores the initial total balance to be paid by someone
        
    public:
        AdjMatrix() {}; // default constructor
        auto getMatrix() { return matrix; } // getter function for the matrix
        int getIndexfromName(string name); // getter function for the index of a person in the matrix
        string getNamefromIndex(int index); // getter function for the name of a person in the matrix
        auto getEdge(string from, string to); // getter function for the edge between two people
        auto getNumEdges() { return num_edges; } // getter function for the number of edges in the graph

        void pushback(string from, string to, double val); // adds an edge to the Adjacency Matrix
        void addSimpleEdge(int from, int to, double val); // adds a simple edge to the Adjacency Matrix
        void simplifyMatrix(); // simplifies the Adjacency Matrix
        
        void initalizeBalances(); // sets all balances to be 0 for all people in the Adjacency Matrix
        void calculateBalances(); // calculates the balances for all people in the Adjacency Matrix

        void printMatrix(); // prints the contents of the Adjacency Matrix
        void printBalances(); // prints all the balances for all people in the Adjacency Matrix
        void printInitialBalances(); // prints the initial balances for all people in the Adjacency Matrix
        void printSimpleEdges(); // prints the contents of the simple edges vector

        int minIndex(); // returns the index of the person with the minimum balance
        int maxIndex(); // returns the index of the person with the maximum balance
        double truncate(double val); // truncates a double to two decimal places

        void minFlowHelper(); // recursive function to calculate the minimum cash flow
        void minFlow(); // calculates the minimum cash flow
};