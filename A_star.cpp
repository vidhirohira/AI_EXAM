#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

class Node {
public:
    string value;
    int heuristic;
    int pathCost;
    int totalCost;
    Node* parent;
    vector<pair<Node*, int>> neighbors;

    Node(string val, int h) : value(val), heuristic(h), pathCost(0), totalCost(0), parent(nullptr) {}
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->totalCost > b->totalCost;  // Min-heap based on f(n) = g(n) + h(n)
    }
};

void printPath(Node* goal) {
    vector<Node*> path;
    int totalDistance = 0;

    for (Node* node = goal; node != nullptr; node = node->parent) {
        path.push_back(node);
    }
    reverse(path.begin(), path.end());

    cout << "Optimal Path: ";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i]->value;
        if (i != path.size() - 1) {
            cout << " -> ";
        }
    }

    for (size_t i = 1; i < path.size(); i++) {
        for (auto& neighbor : path[i - 1]->neighbors) {
            if (neighbor.first == path[i]) {
                totalDistance += neighbor.second;
                break;
            }
        }
    }

    cout << "\nTotal Distance: " << totalDistance << " km\n";
}

void AStarSearch(Node* source, Node* goal) {
    priority_queue<Node*, vector<Node*>, CompareNode> pq;
    unordered_map<string, int> visited;  

    source->pathCost = 0;
    source->totalCost = source->heuristic;
    pq.push(source);

    while (!pq.empty()) {
        Node* current = pq.top();
        pq.pop();

        if (visited.count(current->value) && visited[current->value] <= current->pathCost) {
            continue;
        }
        visited[current->value] = current->pathCost;

        if (current->value == goal->value) {
            printPath(current);
            return;
        }

        for (auto& neighbor : current->neighbors) {
            Node* next = neighbor.first;
            int cost = neighbor.second;
            int newCost = current->pathCost + cost;

            if (!visited.count(next->value) || newCost < visited[next->value]) {
                next->pathCost = newCost;
                next->totalCost = newCost + next->heuristic;
                next->parent = current;
                pq.push(next);
            }
        }
    }

    cout << "No path found!\n";
}

int main() {
    unordered_map<string, Node*> cityMap;

    cityMap["Arad"] = new Node("Arad", 366);
    cityMap["Zerind"] = new Node("Zerind", 374);
    cityMap["Oradea"] = new Node("Oradea", 380);
    cityMap["Sibiu"] = new Node("Sibiu", 253);
    cityMap["Fagaras"] = new Node("Fagaras", 176);
    cityMap["Rimnicu Vilcea"] = new Node("Rimnicu Vilcea", 193);
    cityMap["Pitesti"] = new Node("Pitesti", 100);
    cityMap["Timisoara"] = new Node("Timisoara", 329);
    cityMap["Lugoj"] = new Node("Lugoj", 244);
    cityMap["Mehadia"] = new Node("Mehadia", 241);
    cityMap["Drobeta"] = new Node("Drobeta", 242);
    cityMap["Craiova"] = new Node("Craiova", 160);
    cityMap["Bucharest"] = new Node("Bucharest", 0);
    cityMap["Giurgiu"] = new Node("Giurgiu", 77);

    cityMap["Arad"]->neighbors = {{cityMap["Zerind"], 75}, {cityMap["Sibiu"], 140}, {cityMap["Timisoara"], 118}};
    cityMap["Zerind"]->neighbors = {{cityMap["Arad"], 75}, {cityMap["Oradea"], 71}};
    cityMap["Oradea"]->neighbors = {{cityMap["Zerind"], 71}, {cityMap["Sibiu"], 151}};
    cityMap["Sibiu"]->neighbors = {{cityMap["Arad"], 140}, {cityMap["Fagaras"], 99}, {cityMap["Oradea"], 151}, {cityMap["Rimnicu Vilcea"], 80}};
    cityMap["Fagaras"]->neighbors = {{cityMap["Sibiu"], 99}, {cityMap["Bucharest"], 211}};
    cityMap["Rimnicu Vilcea"]->neighbors = {{cityMap["Sibiu"], 80}, {cityMap["Pitesti"], 97}, {cityMap["Craiova"], 146}};
    cityMap["Pitesti"]->neighbors = {{cityMap["Rimnicu Vilcea"], 97}, {cityMap["Bucharest"], 101}, {cityMap["Craiova"], 138}};
    cityMap["Timisoara"]->neighbors = {{cityMap["Arad"], 118}, {cityMap["Lugoj"], 111}};
    cityMap["Lugoj"]->neighbors = {{cityMap["Timisoara"], 111}, {cityMap["Mehadia"], 70}};
    cityMap["Mehadia"]->neighbors = {{cityMap["Lugoj"], 70}, {cityMap["Drobeta"], 75}};
    cityMap["Drobeta"]->neighbors = {{cityMap["Mehadia"], 75}, {cityMap["Craiova"], 120}};
    cityMap["Craiova"]->neighbors = {{cityMap["Drobeta"], 120}, {cityMap["Rimnicu Vilcea"], 146}, {cityMap["Pitesti"], 138}};
    cityMap["Bucharest"]->neighbors = {{cityMap["Pitesti"], 101}, {cityMap["Giurgiu"], 90}, {cityMap["Fagaras"], 211}};
    cityMap["Giurgiu"]->neighbors = {{cityMap["Bucharest"], 90}};

    string startCity, goalCity;
    cout << "Enter starting city: ";
    cin >> startCity;
    cout << "Enter goal city: ";
    cin >> goalCity;

    if (cityMap.find(startCity) == cityMap.end() || cityMap.find(goalCity) == cityMap.end()) {
        cout << "Invalid city names! Please enter valid cities from the map.\n";
        return 1;
    }

    cout << "\nSearching for shortest path from " << startCity << " to " << goalCity << " using A*...\n";
    AStarSearch(cityMap[startCity], cityMap[goalCity]);

    return 0;
}
