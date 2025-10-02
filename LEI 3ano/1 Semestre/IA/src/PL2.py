# import matplotlib.pyplot as plt
#
# # Define nodes and edges
# nodes = [1, 2, 3, 4, 5]
# edges = [(1, 2), (1, 3), (2, 4), (3, 5), (4, 5)]
#
# # Assign positions to nodes manually for visualization
# positions = {
#     1: (0, 1),
#     2: (-1, 0),
#     3: (1, 0),
#     4: (-1, -1),
#     5: (1, -1)
# }
#
# # Draw edges
# for edge in edges:
#     x_values = [positions[edge[0]][0], positions[edge[1]][0]]
#     y_values = [positions[edge[0]][1], positions[edge[1]][1]]
#     plt.plot(x_values, y_values, color='gray')
#
# # Draw nodes
# for node, pos in positions.items():
#     plt.scatter(pos[0], pos[1], color='lightblue', s=500)
#     plt.text(pos[0], pos[1], str(node), fontsize=12, ha='center', va='center')
#
# plt.axis('off')
# plt.show()
#
# # Native drawing (without libraries) using simple text output
# print("Nodes:", nodes)
# print("Edges:")
# for edge in edges:
#     print(f"{edge[0]} -- {edge[1]}")


# Define nodes and edges
nodes = [1, 2, 3, 4, 5, 6, 7]
edges = [
    (1, 2), (1, 3), (2, 4), (2, 5), (3, 6), (6, 7), (4, 5), (5, 7)
]

# Print nodes table
print("Nodes Table")
print("ID")
for node in nodes:
    print(node)
print()

# Print edges table
print("Edges Table")
print("From\tTo")
for edge in edges:
    print(f"{edge[0]}\t{edge[1]}")
print()

# Build adjacency list
adj = {node: [] for node in nodes}
for u, v in edges:
    adj[u].append(v)
    adj[v].append(u)  # Assuming undirected graph

def bfs(start):
    visited = set()
    queue = [start]
    order = []
    while queue:
        node = queue.pop(0)
        if node not in visited:
            visited.add(node)
            order.append(node)
            for neighbor in adj[node]:
                if neighbor not in visited:
                    queue.append(neighbor)
    return order

def dfs(start):
    visited = set()
    stack = [start]
    order = []
    while stack:
        node = stack.pop()
        if node not in visited:
            visited.add(node)
            order.append(node)
            # Add neighbors in reverse for consistent order
            for neighbor in reversed(adj[node]):
                if neighbor not in visited:
                    stack.append(neighbor)
    return order

print("BFS traversal from node 1:", bfs(1))
print("DFS traversal from node 1:", dfs(1))