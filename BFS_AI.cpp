#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void BFS(int start, const vector<vector<int>>& graph, vector<bool>& visited) {
    queue<int> frontier;
    frontier.push(start);
    visited[start] = true;

    while (!frontier.empty()) {
        int current = frontier.front();
        frontier.pop();
        cout << current << " ";  // Process the current node

        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) {
                frontier.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

int main() {
    int nodes, edges;
    cout << "Enter the number of nodes: ";
    cin >> nodes;
    cout << "Enter the number of edges: ";
    cin >> edges;

    vector<vector<int>> graph(nodes + 1);  // Adjacency list
    cout << "Enter the edges (u v) for an undirected graph:\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start;
    cout << "Enter the starting node: ";
    cin >> start;

    vector<bool> visited(nodes + 1, false);

    cout << "BFS traversal starting from node " << start << ": ";
    BFS(start, graph, visited);
    cout << endl;

    return 0;
}

