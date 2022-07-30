#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>
#pragma once

using namespace std;

class AdjList
{
    typedef pair<string, double> Edge;
    
    private:
        // Achyudhan : (people : [("jonathan", 10), ("prayuj", 15)])
        unordered_map<string, vector<Edge*>> list;
        unordered_map<string, double> amount;
        int num_edges = 0;
        set<string> people; // assumes all people have different names
        vector<tuple<string, string, double>> simple_edges;
    public:
        AdjList() {};
        auto getList() { return list; }
        void pushback(string from, string to, double val);
        double getEdge(string from, string to);
        void printList();
        void initalizeAmount();
        unordered_map<string, double> getAmount();
        void setAmount(unordered_map<string, double> amount);
        void printAmounts();
        void simplifyList();
        set<string> getPeople();
        vector<tuple<string, string, double>> getSimpleEdges();
};