import random

def generate_random_graph(filename, num_vertices, max_edges_per_vertex, max_weight):
    with open(filename, 'w') as file:
        for vertex in range(1, num_vertices + 1):
            edges = []
            num_edges = random.randint(1, max_edges_per_vertex)
            for _ in range(num_edges):
                dest_vertex = random.randint(1, num_vertices)
                weight = random.randint(1, max_weight)
                edges.append(f"{dest_vertex};{weight}")
            line = f"{vertex};" + ";".join(edges) + "\n"
            file.write(line)

# Usage example:
generate_random_graph("test.txt", 10, 5, 10)
