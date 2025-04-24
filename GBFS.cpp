#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Node {
public:
    string value;
    int heuristic;
    Node* parent;
    vector<pair<Node*, int>> neighbors;
    int distanceFromStart;

    Node(string val, int h) : value(val), heuristic(h), parent(nullptr), distanceFromStart(0) {}
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->heuristic > b->heuristic; // Min-heap based on heuristic
    }
};

void GreedyBestFirstSearch(Node* source, Node* goal) {
    vector<Node*> explored;
    priority_queue<Node*, vector<Node*>, CompareNode> queue;
    vector<Node*> queueContents;

    source->distanceFromStart = 0;
    queue.push(source);
    queueContents.push_back(source);
    vector<Node*> path;

    while (!queue.empty()) {
        path.clear();
        Node* current = queue.top();
        queue.pop();
        queueContents.erase(remove(queueContents.begin(), queueContents.end(), current), queueContents.end());

        cout << " -> " << current->value;
        explored.push_back(current);

        for (Node* node = current; node != nullptr; node = node->parent) {
            path.push_back(node);
        }

        if (current->value == goal->value) {
            goal->parent = current->parent;
            cout << endl << "Path found to: " << current->value << endl;

            // Print the path and total distance
            int totalDistance = current->distanceFromStart;
            cout << "Shortest Path: ";
            reverse(path.begin(), path.end());
            for (Node* n : path) {
                cout << n->value;
                if (n != path.back()) cout << " -> ";
            }
            cout << "\nTotal Distance: " << totalDistance << " km\n";
            return;
        }

        for (auto& e : current->neighbors) {
            Node* neighbor = e.first;
            int distance = e.second;
            bool inQueue = find(queueContents.begin(), queueContents.end(), neighbor) != queueContents.end();
            bool inExplored = find(explored.begin(), explored.end(), neighbor) != explored.end();
            bool inPath = find(path.begin(), path.end(), neighbor) != path.end();

            if (!inQueue && !inExplored && !inPath) {
                neighbor->parent = current;
                neighbor->distanceFromStart = current->distanceFromStart + distance;
                queue.push(neighbor);
                queueContents.push_back(neighbor);
            }
        }
    }

    cout << "\nGoal not reachable.\n";
}

int main() {
    unordered_map<string, Node*> cityMap;

    // Create cities with heuristic values
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

    // Define connections and distances
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

    // User input for cities
    string startCity, goalCity;
    cout << "Enter Start City: ";
    cin >> startCity;
    cout << "Enter Destination City: ";
    cin >> goalCity;

    // Validate input
    if (cityMap.find(startCity) == cityMap.end() || cityMap.find(goalCity) == cityMap.end()) {
        cout << "Invalid city name. Please try again.\n";
        return 1;
    }

    // Run GBFS
    cout << "Finding path from " << startCity << " to " << goalCity << "...\n";
    GreedyBestFirstSearch(cityMap[startCity], cityMap[goalCity]);

    return 0;
}
