import heapq

class Node:
    def __init__(self, value, heuristic):
        self.value = value
        self.heuristic = heuristic
        self.parent = None
        self.neighbors = []
        self.distance_from_start = 0

    def __lt__(self, other):
        return self.heuristic < other.heuristic

def greedy_best_first_search(source, goal):
    explored = set()
    queue = []
    queue_contents = set()

    source.distance_from_start = 0
    heapq.heappush(queue, source)
    queue_contents.add(source)

    while queue:
        current = heapq.heappop(queue)
        queue_contents.remove(current)
        print(f" -> {current.value}", end='')
        explored.add(current)

        if current.value == goal.value:
            print(f"\nPath found to: {current.value}")
            path = []
            total_distance = current.distance_from_start
            while current:
                path.append(current)
                current = current.parent
            path.reverse()
            print("Shortest Path:", ' -> '.join([node.value for node in path]))
            print("Total Distance:", total_distance, "km")
            return

        for neighbor, distance in current.neighbors:
            if neighbor not in explored and neighbor not in queue_contents:
                neighbor.parent = current
                neighbor.distance_from_start = current.distance_from_start + distance
                heapq.heappush(queue, neighbor)
                queue_contents.add(neighbor)

    print("\nGoal not reachable.")

# Create city nodes with heuristics
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
    "Giurgiu": Node("Giurgiu", 77)
}

# Add neighbors with distances
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

# Input and execution
start_city = input("Enter Start City: ")
goal_city = input("Enter Destination City: ")

if start_city not in city_map or goal_city not in city_map:
    print("Invalid city name. Please try again.")
else:
    print(f"Finding path from {start_city} to {goal_city}...")
    greedy_best_first_search(city_map[start_city], city_map[goal_city])
