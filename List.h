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
        unordered_map<string, vector<Edge*>> list;
        unordered_map<string, double> balances;
        unordered_map<string, double> initial_balances;
        int num_edges = 0;
        set<string> people; // assumes all people have different names
        vector<tuple<string, string, double>> simple_edges;
    public:
        AdjList() {};
        ~AdjList();

        auto getList() { return list; }
        double getEdge(string from, string to);
        vector<tuple<string, string, double>> getSimpleEdges();
        unordered_map<string, double> getBalances();
        set<string> getPeople();

        void pushback(string from, string to, double val);
        void addSimpleEdge(string from, string to, double val);
        void simplifyList();

        void initializeBalances();
        void calculateBalances();

        void printList();
        void printBalances();
        void printInitialBalances(int k);
        void printSimpleEdges();
        void printEdgesByWeight();

        string minIndex();
        string maxIndex();
        double truncate(double val);

        void minCashFlowRec();
        void minCashFlow();
};