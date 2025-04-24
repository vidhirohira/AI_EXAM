#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void DFS(int start, const vector<vector<int>>& graph, vector<bool>& visited) {
    stack<int> s;
    s.push(start);
    
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        
        if (!visited[current]) {
            visited[current] = true;
            cout << current << " ";  // Process the current node
        }
        
        // Push unvisited neighbors onto the stack
        for (auto it = graph[current].rbegin(); it != graph[current].rend(); ++it) {
            if (!visited[*it]) {
                s.push(*it);
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

    cout << "DFS traversal starting from node " << start << ": ";
    DFS(start, graph, visited);
    cout << endl;
    
    return 0;
}
