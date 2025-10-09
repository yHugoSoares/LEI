# ANSWER TO TP1:
#   i.  a) DFS Order: ['A', 'B', 'D', 'H', 'I', 'E', 'J', 'K', 'C', 'F']
#       b) A -> C -> F -> L
#
#   ii. a) BFS Order: ['A', 'B', 'C']
#       b) A -> C -> G
#
#  iii. a) Cost order path: ['A', 'B', 'C']
#       b) A -> C -> G
#
#   iv. a) 
#       b)
#
#

edges = [
    ('A', 'B'), ('A', 'C'), ('B', 'D'), ('B', 'E'), ('C', 'F'), ('C', 'G'), ('D', 'H'),
    ('D', 'I'), ('E', 'J'), ('E', 'K'), ('F', 'L'), ('F', 'M'), ('G', 'N'), ('G', 'O')
]

cost = { 
    ('A', 'B'): 2, ('A', 'C'): 3, ('B', 'D'): 2, ('B', 'E'): 3, ('C', 'F'): 2, ('C', 'G'): 1,
    ('D', 'H'): 1, ('D', 'I'): 2, ('E', 'J'): 2, ('E', 'K'): 4, ('F', 'L'): 2, ('F', 'M'): 2,
    ('G', 'N'): 2, ('G', 'O'): 1
}

def get_neighbors(node):
    neighbors = []
    for edge in edges:
        if edge[0] == node:
            neighbors.append(edge[1])
        elif edge[1] == node:
            neighbors.append(edge[0])
    return neighbors

def get_cost(u, v):
    return cost.get((u, v)) or cost.get((v, u)) or float('inf')


def bfs(start):
    visited = set()
    queue = [start]
    order = []
    while queue:
        node = queue.pop(0)
        if node not in visited:
            visited.add(node)
            order.append(node)
            for neighbor in get_neighbors(node):
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
            for neighbor in reversed(get_neighbors(node)):
                if neighbor not in visited:
                    stack.append(neighbor)
    return order

# Example usage
start_node = 'A'
print("BFS Order:", bfs(start_node))
print("DFS Order:", dfs(start_node))