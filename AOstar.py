from collections import defaultdict
from copy import deepcopy

def aostar(graph, heuristic, start="S"):
    solved = defaultdict(bool)
    cost = deepcopy(heuristic)
    parent = defaultdict(lambda: ("", -1))
    best_child_group = defaultdict(list)

    def calculate_group_cost(group):
        return sum(edge_cost + cost[child] for child, edge_cost in group)

    def forward_propagation(node, sorted_groups):
        min_cost = float('inf')
        best_group = None
        for group in sorted_groups:
            for child, _ in group:
                if not solved[child]:
                    ao_star(child)
            group_cost = calculate_group_cost(group)
            if group_cost < min_cost:
                min_cost = group_cost
                best_group = group
        return best_group, min_cost

    def backward_propagation(node):
        while node:
            if node not in best_child_group:
                break
            group = best_child_group[node]
            new_cost = calculate_group_cost(group)
            if new_cost >= cost[node]:
                break
            cost[node] = new_cost
            node = parent[node][0]

    def ao_star(node):
        if solved[node]:
            return cost[node]
        if node not in graph or not graph[node]:
            solved[node] = True
            return cost[node]

        # Sort groups by estimated cost - it explores smaller branches first
        sorted_groups = sorted(graph[node], key=calculate_group_cost)
        best_group, min_cost = forward_propagation(node, sorted_groups)

        if best_group and (cost[node] > min_cost or not solved[node]):
            cost[node] = min_cost
            best_child_group[node] = best_group
            solved[node] = all(solved[child] for child, _ in best_group)
            for child, _ in best_group:
                parent[child] = (node, cost[child])

        backward_propagation(node)
        return cost[node]

    def reconstruct_path(node):
        path = []

        def reconstruct(node):
            if node in path:
                return
            path.append(node)
            best_group = best_child_group[node]
            for child, _ in best_group:
                if solved[child]:
                    reconstruct(child)

        reconstruct(node)
        return path

    ao_star(start)
    path = reconstruct_path(start)
    return cost[start], path  # Return both the cost and the path

# Updated graph structure with proper (child, edge_cost) pairs
graph = {
    'S': [[('B', 1), ('C', 1)]],
    'B': [[('D', 3)], [('E', 2)]],
    'D': [[('K', 3)]],
    'E': [[('F', 1), ('G', 1)], [('H', 2)]],
    'F': [[('L', 1)]],
    'G': [[('M', 2)]],
    'H': [[('I', 1)], [('J', 3)]],
    'I': [[('J', 3)]]
}

heuristic = {
    'S': 5,
    'B': 2,
    'C': 2,
    'D': 3,
    'E': 1,
    'F': 1,
    'G': 2,
    'H': 3,
    'I': 3,
    'J': 0,
    'K': 0,
    'L': 0,
    'M': 0
}

# Run A* search
result, path = aostar(graph, heuristic, "S")
print("Minimum cost from S:", result)
print("Path:", path)
