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
        int num_edges = 0;
        set<string> people; // assumes all people have different names
        vector<tuple<string, string, double>> simple_edges;
    public:
        AdjList() {};
        ~AdjList();
        auto getList() { return list; }
        void pushback(string from, string to, double val);
        double getEdge(string from, string to);
        void printList();
        void initializeBalances();
        unordered_map<string, double> getBalances();
        void setBalances(unordered_map<string, double> balances);
        void printBalances();
        void simplifyList();
        set<string> getPeople();
        vector<tuple<string, string, double>> getSimpleEdges();
        void addSimpleEdge(string from, string to, double val);
        void printSimpleEdges();
        void printEdgesByWeight();
        string minIndex();
        string maxIndex();
        double truncate(double val);

        void calculateBalances();
        void minCashFlowRec();
        void minCashFlow();
};