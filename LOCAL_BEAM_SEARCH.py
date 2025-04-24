import random
import itertools

def calculate_distance(route, distance_matrix):
    """Calculate the total distance of a given route."""
    return sum(distance_matrix[route[i]][route[i + 1]] for i in range(len(route) - 1)) + distance_matrix[route[-1]][route[0]]

def evaluate(route, distance_matrix):
    """Evaluation function: lower distance is better."""
    return -calculate_distance(route, distance_matrix)  # Negative because we want to minimize distance

def generate_neighbors(route):
    """Generate neighbors by swapping two cities in the route."""
    neighbors = []
    for i in range(len(route)):
        for j in range(i + 1, len(route)):
            new_route = list(route)
            new_route[i], new_route[j] = new_route[j], new_route[i]
            neighbors.append(tuple(new_route))
    return neighbors

def generate_initial_states(k, num_cities):
    """Generate k random initial states (random routes)."""
    cities = list(range(num_cities))
    return [tuple(random.sample(cities, len(cities))) for _ in range(k)]

def local_beam_search(k, initial_states, distance_matrix, max_iterations=100):
    """
    Performs local beam search for the Traveling Salesperson Problem (TSP).
    
    Parameters:
    k: Number of states to keep in the beam.
    initial_states: List of k randomly generated initial states.
    distance_matrix: Matrix containing distances between cities.
    max_iterations: Maximum number of iterations to run.
    
    Returns:
    The best route found and the iteration it was found in.
    """
    beam = initial_states  # Start with k random routes
    best_route = None
    best_distance = float('inf')
    best_iteration = -1
    
    print("Initial routes:")
    for route in beam:
        print(route, "Distance:", -evaluate(route, distance_matrix))
    
    for iteration in range(max_iterations):
        print(f"\nIteration {iteration + 1}:")
        all_neighbors = []
        for route in beam:
            neighbors = generate_neighbors(route)
            all_neighbors.extend(neighbors)
        
        all_neighbors.sort(key=lambda r: evaluate(r, distance_matrix), reverse=True)
        beam = all_neighbors[:k]
        
        print("Top candidates after sorting:")
        for i, route in enumerate(beam):
            print(f"Route {i + 1}: {route} Distance: {-evaluate(route, distance_matrix)}")
        
        if -evaluate(beam[0], distance_matrix) < best_distance:
            best_distance = -evaluate(beam[0], distance_matrix)
            best_route = beam[0]
            best_iteration = iteration + 1
        
        if best_iteration == 0:
            print(f"\nOptimal solution found at iteration {best_iteration}!")
            return best_route, best_iteration
    
    print(f"\nBest route after max iterations (Iteration {best_iteration}):")
    return best_route, best_iteration

# Example distance matrix (symmetric, 5 cities)
distance_matrix = [
    [0, 10, 15, 20, 25],
    [10, 0, 35, 25, 30],
    [15, 35, 0, 30, 20],
    [20, 25, 30, 0, 15],
    [25, 30, 20, 15, 0]
]

num_cities = len(distance_matrix)
k = 3
initial_states = generate_initial_states(k, num_cities)

best_route, best_iteration = local_beam_search(k, initial_states, distance_matrix)
print("Best route found:", best_route, "at iteration", best_iteration, "with distance", -evaluate(best_route, distance_matrix))
