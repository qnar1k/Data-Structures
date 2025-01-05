#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <string>

using namespace std;

// Graph class with adjacency list and hash table
class Graph {
private:
    unordered_map<string, unordered_set<string>> adjList; // Adjacency list (hash table)

public:
    void addNode(const string& node) {
        adjList[node];  // Creates an empty set for this node
    }

    void addEdge(const string& from, const string& to) {
        adjList[from].insert(to);  // Add 'to' to the adjacency list of 'from'
        adjList[to].insert(from);  // Add 'from' to the adjacency list of 'to' (undirected)
    }

    void printGraph() {
        for (auto& pair : adjList) {
            cout << pair.first << ": ";
            for (auto& neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    bool hasNode(const string& node) {
        return adjList.find(node) != adjList.end();
    }

    bool hasEdge(const string& from, const string& to) {
        return adjList[from].find(to) != adjList[from].end();
    }

    void removeNode(const string& node) {
        adjList.erase(node);  // Remove the node
        for (auto& pair : adjList) {
            pair.second.erase(node);  // Remove any edges from this node to others
        }
    }

    void removeEdge(const string& from, const string& to) {
        adjList[from].erase(to);
        adjList[to].erase(from);
    }
};

int main() {
    Graph g;

    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addNode("D");

    g.addEdge("A", "B");
    g.addEdge("A", "C");
    g.addEdge("B", "D");

    cout << "Graph structure:\n";
    g.printGraph();

    cout << "Is there an edge between A and B? " << (g.hasEdge("A", "B") ? "Yes" : "No") << endl;
    cout << "Is there an edge between A and D? " << (g.hasEdge("A", "D") ? "Yes" : "No") << endl;

    cout << "Removing node B...\n";
    g.removeNode("B");
    g.printGraph();

    cout << "Removing edge between A and C...\n";
    g.removeEdge("A", "C");
    g.printGraph();

    return 0;
}
