#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <cmath>
#include <climits>

#pragma once

using namespace std;

class AdjList
{
    typedef pair<string, double> Edge;

    private:
        // Achyudhan : (people : [("jonathan", 10), ("prayuj", 15)])
        unordered_map<string, vector<Edge *>> list; // unordered map of people and their edges
        unordered_map<string, double> balances; // unordered map of people and their balances
        unordered_map<string, double> initial_balances; // unordered map of people and their initial balances
        int num_edges = 0; // number of edges in the graph
        set<string> people; // set of all vertex name (people names - assumed to be unique)
        vector<tuple<string, string, double>> simple_edges; // vector of simple edges (after simplification)

    public:
        AdjList(){}; // default constructor
        ~AdjList(); // destructor

        auto getList() { return list; } // getter function for the list
        double getEdge(string from, string to); // getter function for the edge between two people
        vector<tuple<string, string, double>> getSimpleEdges(); // getter function for the simple edges
        unordered_map<string, double> getBalances(); // getter function for the balances
        set<string> getPeople(); // getter function for the people
        vector<pair<string, double>> getLeaderboards(); // getter function for the leaderboards

        void pushback(string from, string to, double val); // adds an edge to the Adjacency List
        void addSimpleEdge(string from, string to, double val); // adds a simple edge to the Adjacency List
        void simplifyList(); // simplifies the Adjacency List

        void initializeBalances(); // sets all balances to be 0 for all people in the Adjacency List
        void calculateBalances(); // calculates the balances for all people in the Adjacency List

        void printList(); // prints the contents of the Adjacency List
        void printBalances(); // prints all the balances for all people in the Adjacency List
        void printInitialBalances(int k); // prints the initial balances for all people in the Adjacency List
        void printSimpleEdges(); // prints the contents of the simple edges vector
        void printEdgesByWeight(); // prints the contents of the edges by weight vector

        string minIndex(); // returns the name of the person with the minimum balance
        string maxIndex(); // returns the name of the person with the maximum balance
        double truncate(double val); // truncates a double to two decimal places

        void minFlowHelper(); // recursive function to calculate the minimum cash flow
        void minFlow(); // calculates the minimum cash flow
};