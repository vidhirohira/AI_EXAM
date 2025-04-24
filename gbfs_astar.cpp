#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

struct Edge {
    string destination;
    int cost;
};

struct Node {
    string city;
    int cost;       // g(n)
    int heuristic;  // h(n)
    int f;          // f(n) = g(n) + h(n)

    bool operator>(const Node& other) const {
        return f > other.f; // Min-heap based on f(n)
    }
};

// Graph and heuristic map
unordered_map<string, vector<Edge>> graph;
unordered_map<string, int> heuristic;

// Function to input graph and heuristic from user
void inputGraph(string &startCity, string &goalCity) {
    int numEdges;
    cout << "Enter number of edges: ";
    cin >> numEdges;

    string city1, city2;
    int cost;
    cout << "Enter each edge in the format: City1 City2 Cost\n";
    for (int i = 0; i < numEdges; i++) {
        cin >> city1 >> city2 >> cost;
        graph[city1].push_back({city2, cost});
        graph[city2].push_back({city1, cost}); // Assuming undirected graph
    }

    int numCities;
    cout << "Enter number of cities with heuristics: ";
    cin >> numCities;

    string city;
    int h;
    cout << "Enter each city heuristic in the format: City Heuristic\n";
    for (int i = 0; i < numCities; i++) {
        cin >> city >> h;
        heuristic[city] = h;
    }

    cout << "Enter start city: ";
    cin >> startCity;
    cout << "Enter goal city: ";
    cin >> goalCity;
}

// Function to reconstruct and display the path and cost
void reconstructPath(unordered_map<string, string>& parent, string start, string goal, bool showCost) {
    stack<string> path;
    string current = goal;
    int totalCost = 0;

    while (current != start) {
        path.push(current);
        string prev = parent[current];

        for (const auto& edge : graph[prev]) {
            if (edge.destination == current) {
                totalCost += edge.cost;
                break;
            }
        }
        current = prev;
    }
    path.push(start);

    cout << "Path: ";
    while (!path.empty()) {
        cout << path.top();
        path.pop();
        if (!path.empty()) cout << " -> ";
    }
    if (showCost) {
        cout << "\nTotal Cost: " << totalCost;
    }
    cout << endl;
}

// Greedy Best-First Search
void greedyBFS(string start, string goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<string, bool> visited;
    unordered_map<string, string> parent;

    pq.push({start, 0, heuristic[start], heuristic[start]});
    parent[start] = "";

    cout << "\nGreedy Best-First Search:\n";

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        cout << "Visiting: " << current.city << endl;

        if (current.city == goal) {
            cout << "Goal Reached.\n";
            reconstructPath(parent, start, goal, true);
            return;
        }

        visited[current.city] = true;

        for (const auto& neighbor : graph[current.city]) {
            if (!visited[neighbor.destination]) {
                pq.push({neighbor.destination, 0, heuristic[neighbor.destination], heuristic[neighbor.destination]});
                parent[neighbor.destination] = current.city;
            }
        }
    }

    cout << "No path found.\n";
}

// A* Search
void aStar(string start, string goal) {
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    unordered_map<string, int> costSoFar;
    unordered_map<string, bool> visited;
    unordered_map<string, string> parent;

    pq.push({start, 0, heuristic[start], heuristic[start]});
    costSoFar[start] = 0;
    parent[start] = "";

    cout << "\nA* Search:\n";

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        cout << "Visiting: " << current.city << " (Cost: " << costSoFar[current.city] << ")" << endl;

        if (current.city == goal) {
            cout << "Goal Reached.\n";
            reconstructPath(parent, start, goal, true);
            return;
        }

        visited[current.city] = true;

        for (const auto& neighbor : graph[current.city]) {
            int newCost = costSoFar[current.city] + neighbor.cost;

            if (!costSoFar.count(neighbor.destination) || newCost < costSoFar[neighbor.destination]) {
                costSoFar[neighbor.destination] = newCost;
                int f = newCost + heuristic[neighbor.destination];
                pq.push({neighbor.destination, newCost, heuristic[neighbor.destination], f});
                parent[neighbor.destination] = current.city;
            }
        }
    }

    cout << "No path found.\n";
}

// Main function
int main() {
    string startCity, goalCity;
    inputGraph(startCity, goalCity);

    greedyBFS(startCity, goalCity);
    aStar(startCity, goalCity);

    return 0;
}
