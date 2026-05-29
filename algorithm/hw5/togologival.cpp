// 22100311_박진우

// Lecture slide Chapter 22 (Elementary Graph Algorithms).
//   - DFS & discovery/finish times: pp. 49-52
//   - Topological Sort: pp. 93-97
// Blog: GeeksforGeeks - Topological Sorting, https://www.geeksforgeeks.org/topological-sorting/
// Reference: Wikipedia - Topological sorting, https://en.wikipedia.org/wiki/Topological_sorting

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

class Graph {
private:
    map<char, vector<char>> adj;   // adjacency list
    vector<char> vertices;          // vertices in insertion order

    map<char, int> startTime;
    map<char, int> finishTime;
    map<char, bool> visited;
    int timer;
    vector<char> topoOrder;         // finished vertices (reverse = topological order)

    void dfsVisit(char u) {
        visited[u] = true;
        startTime[u] = ++timer;

        for (char v : adj[u]) {
            if (!visited[v])
                dfsVisit(v);
        }

        finishTime[u] = ++timer;
        topoOrder.push_back(u);     // record when finished
    }

public:
    Graph() : timer(0) {}

    void addVertex(char v) {
        if (adj.find(v) == adj.end()) {
            adj[v] = vector<char>();
            vertices.push_back(v);
        }
    }

    void addEdge(char from, char to) {
        addVertex(from);
        addVertex(to);
        adj[from].push_back(to);
        // keep neighbors in alphabetical order
        sort(adj[from].begin(), adj[from].end());
    }

    // DFS traversal: start from a given vertex, then cover the rest
    void runDFS(char start) {
        timer = 0;
        topoOrder.clear();
        for (char v : vertices) visited[v] = false;

        // alphabetical order for the overall DFS sweep
        vector<char> ordered = vertices;
        sort(ordered.begin(), ordered.end());

        // start from the requested vertex first
        if (!visited[start])
            dfsVisit(start);

        // continue with any remaining unvisited vertices (alphabetical)
        for (char v : ordered) {
            if (!visited[v])
                dfsVisit(v);
        }
    }

    void printDFSTimes() {
        vector<char> ordered = vertices;
        sort(ordered.begin(), ordered.end());

        cout << "===== DFS Start/Finish Times =====\n";
        cout << "Vertex |  Start  | Finish\n";
        cout << "-------+---------+--------\n";
        for (char v : ordered) {
            cout << "   " << v << "   |"
                 << setw(6) << startTime[v] << "   |"
                 << setw(6) << finishTime[v] << "\n";
        }
        cout << "\n";
    }

    void printTopologicalOrder() {
        cout << "===== Topological Ordering =====\n";
        // topological order = vertices in DECREASING finish time
        vector<char> result(topoOrder.rbegin(), topoOrder.rend());
        for (size_t i = 0; i < result.size(); ++i) {
            cout << result[i];
            if (i + 1 < result.size()) cout << " -> ";
        }
        cout << "\n";
    }

    void printAdjList() {
        vector<char> ordered = vertices;
        sort(ordered.begin(), ordered.end());

        cout << "===== Adjacency List =====\n";
        for (char v : ordered) {
            cout << v << " : ";
            for (size_t i = 0; i < adj[v].size(); ++i) {
                cout << adj[v][i];
                if (i + 1 < adj[v].size()) cout << ", ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

// Run all required steps on one graph, given the DFS start vertex.
void processGraph(Graph& g, const string& title, char startVertex) {
    cout << "##################################################\n";
    cout << "# " << title << "\n";
    cout << "#   (DFS start vertex: " << startVertex << ")\n";
    cout << "##################################################\n\n";

    g.printAdjList();          // 1. Graph Construction (alphabetical adjacency)
    g.runDFS(startVertex);     // 2. DFS traversal
    g.printDFSTimes();         //    start/finish times
    g.printTopologicalOrder(); // 3. Topological sort
    cout << "\n";
}

int main() {
    {
        Graph g;
        for (char c = 'A'; c <= 'H'; ++c)
            g.addVertex(c);

        g.addEdge('A', 'B');
        g.addEdge('C', 'B');
        g.addEdge('C', 'E');
        g.addEdge('C', 'H');
        g.addEdge('D', 'A');
        g.addEdge('D', 'B');
        g.addEdge('E', 'B');
        g.addEdge('E', 'G');
        g.addEdge('F', 'A');
        g.addEdge('F', 'G');
        g.addEdge('H', 'G');

        processGraph(g, "TEST 1: Example DAG from homework figure", 'A');
    }

    {
        Graph g;
        g.addEdge('A', 'B');
        g.addEdge('B', 'C');
        g.addEdge('C', 'D');
        g.addEdge('D', 'E');

        processGraph(g, "TEST 2: Linear chain (A->B->C->D->E)", 'A');
    }

    {
        Graph g;
        for (char c = 'A'; c <= 'F'; ++c)
            g.addVertex(c);

        g.addEdge('A', 'C');
        g.addEdge('A', 'D');
        g.addEdge('B', 'D');
        g.addEdge('C', 'E');
        g.addEdge('D', 'E');
        g.addEdge('D', 'F');
        g.addEdge('E', 'F');

        processGraph(g, "TEST 3: Diamond/merge DAG (6 nodes)", 'A');
    }

    return 0;
}