#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

class AdjList
{
    typedef pair<string, double> Edge;
    
    private:
        // Achyudhan : (people : [("jonathan", 10), ("prayuj", 15)])
        unordered_map<string, vector<Edge*>> list;
        int num_edges = 0;
    public:
        AdjList() {};
        auto getList() { return list; }
        void pushback(string from, string to, double val);
        double getEdge(string from, string to);
        void printList();
        void simplifyList();
};