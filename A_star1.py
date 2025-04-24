import heapq

class Node:
    def __init__(self, value, heuristic):
        self.value = value
        self.heuristic = heuristic
        self.path_cost = 0
        self.total_cost = 0
        self.parent = None
        self.neighbors = []  # List of tuples (neighbor_node, distance)

    def __lt__(self, other):
        return self.total_cost < other.total_cost


def print_path(goal):
    path = []
    total_distance = 0
    node = goal

    while node:
        path.append(node)
        node = node.parent

    path.reverse()

    print("Optimal Path:", " -> ".join(n.value for n in path))

    for i in range(1, len(path)):
        for neighbor, distance in path[i-1].neighbors:
            if neighbor == path[i]:
                total_distance += distance
                break

    print("Total Distance:", total_distance, "km")


def a_star_search(source, goal):
    open_list = []
    visited = {}

    source.path_cost = 0
    source.total_cost = source.heuristic
    heapq.heappush(open_list, source)

    while open_list:
        current = heapq.heappop(open_list)

        if current.value in visited and visited[current.value] <= current.path_cost:
            continue
        visited[current.value] = current.path_cost

        if current.value == goal.value:
            print_path(current)
            return

        for neighbor, cost in current.neighbors:
            new_cost = current.path_cost + cost
            if neighbor.value not in visited or new_cost < visited[neighbor.value]:
                neighbor.path_cost = new_cost
                neighbor.total_cost = new_cost + neighbor.heuristic
                neighbor.parent = current
                heapq.heappush(open_list, neighbor)

    print("No path found!")


def build_romania_map():
    city_map = {
        "Arad": Node("Arad", 366),
        "Zerind": Node("Zerind", 374),
        "Oradea": Node("Oradea", 380),
        "Sibiu": Node("Sibiu", 253),
        "Fagaras": Node("Fagaras", 176),
        "Rimnicu Vilcea": Node("Rimnicu Vilcea", 193),
        "Pitesti": Node("Pitesti", 100),
        "Timisoara": Node("Timisoara", 329),
        "Lugoj": Node("Lugoj", 244),
        "Mehadia": Node("Mehadia", 241),
        "Drobeta": Node("Drobeta", 242),
        "Craiova": Node("Craiova", 160),
        "Bucharest": Node("Bucharest", 0),
        "Giurgiu": Node("Giurgiu", 77),
    }

    city_map["Arad"].neighbors = [(city_map["Zerind"], 75), (city_map["Sibiu"], 140), (city_map["Timisoara"], 118)]
    city_map["Zerind"].neighbors = [(city_map["Arad"], 75), (city_map["Oradea"], 71)]
    city_map["Oradea"].neighbors = [(city_map["Zerind"], 71), (city_map["Sibiu"], 151)]
    city_map["Sibiu"].neighbors = [(city_map["Arad"], 140), (city_map["Fagaras"], 99), (city_map["Oradea"], 151), (city_map["Rimnicu Vilcea"], 80)]
    city_map["Fagaras"].neighbors = [(city_map["Sibiu"], 99), (city_map["Bucharest"], 211)]
    city_map["Rimnicu Vilcea"].neighbors = [(city_map["Sibiu"], 80), (city_map["Pitesti"], 97), (city_map["Craiova"], 146)]
    city_map["Pitesti"].neighbors = [(city_map["Rimnicu Vilcea"], 97), (city_map["Bucharest"], 101), (city_map["Craiova"], 138)]
    city_map["Timisoara"].neighbors = [(city_map["Arad"], 118), (city_map["Lugoj"], 111)]
    city_map["Lugoj"].neighbors = [(city_map["Timisoara"], 111), (city_map["Mehadia"], 70)]
    city_map["Mehadia"].neighbors = [(city_map["Lugoj"], 70), (city_map["Drobeta"], 75)]
    city_map["Drobeta"].neighbors = [(city_map["Mehadia"], 75), (city_map["Craiova"], 120)]
    city_map["Craiova"].neighbors = [(city_map["Drobeta"], 120), (city_map["Rimnicu Vilcea"], 146), (city_map["Pitesti"], 138)]
    city_map["Bucharest"].neighbors = [(city_map["Pitesti"], 101), (city_map["Giurgiu"], 90), (city_map["Fagaras"], 211)]
    city_map["Giurgiu"].neighbors = [(city_map["Bucharest"], 90)]

    return city_map


if __name__ == "__main__":
    city_map = build_romania_map()

    start_city = input("Enter starting city: ").strip()
    goal_city = input("Enter goal city: ").strip()

    if start_city not in city_map or goal_city not in city_map:
        print("Invalid city names! Please enter valid cities from the map.")
    else:
        print(f"\nSearching for shortest path from {start_city} to {goal_city} using A*...\n")
        a_star_search(city_map[start_city], city_map[goal_city])
