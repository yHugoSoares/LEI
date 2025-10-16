# Classe grafo para representaçao de grafos,
import math
from queue import Queue

import networkx as nx  # biblioteca de tratamento de grafos necessária para desnhar graficamente o grafo
import matplotlib.pyplot as plt  # idem

from Node import Node


# Constructor
# Methods for adding edges
# Methods for removing edges
# Methods for searching a graph
# BFS, DFS, A*, Greedy





class Graph:
    def __init__(self, directed=False):
        self.m_nodes = []  
        self.m_directed = directed
        self.m_graph = {}  
        self.m_h = {}  

    #############
    #    escrever o grafo como string
    #############
    def __str__(self):
        out = ""
        for key in self.m_graph.keys():
            out = out + "node" + str(key) + ": " + str(self.m_graph[key]) + "\n"
        return out

    ################################
    #   encontrar nodo pelo nome
    ################################

    def get_node_by_name(self, name):
        search_node = Node(name)
        for node in self.m_nodes:
            if node == search_node:
                return node
          
        return None

    ##############################3
    #   imprimir arestas
    ############################333333

    def imprime_aresta(self):
        listaA = ""
        lista = self.m_graph.keys()
        for nodo in lista:
            for (nodo2, custo) in self.m_graph[nodo]:
                listaA = listaA + nodo + " ->" + nodo2 + " custo:" + str(custo) + "\n"
        return listaA

    ################
    #   adicionar   aresta no grafo
    ######################

    def add_edge(self, node1, node2, weight):
        n1 = Node(node1)
        n2 = Node(node2)
        if (n1 not in self.m_nodes):
            n1_id = len(self.m_nodes)  # numeração sequencial
            n1.setId(n1_id)
            self.m_nodes.append(n1)
            self.m_graph[node1] = []
        else:
            n1 = self.get_node_by_name(node1)

        if (n2 not in self.m_nodes):
            n2_id = len(self.m_nodes)  # numeração sequencial
            n2.setId(n2_id)
            self.m_nodes.append(n2)
            self.m_graph[node2] = []
        else:
            n2 = self.get_node_by_name(node2)

        self.m_graph[node1].append((node2, weight)) 

        if not self.m_directed:
            self.m_graph[node2].append((node1, weight))

    #############################
    # devolver nodos
    ##########################

    def getNodes(self):
        return self.m_nodes

    #######################
    #    devolver o custo de uma aresta
    ##############3

    def get_arc_cost(self, node1, node2):
        custoT = math.inf
        a = self.m_graph[node1]  # lista de arestas para aquele nodo
        for (nodo, custo) in a:
            if nodo == node2:
                custoT = custo

        return custoT

    ##############################
    #  dado um caminho calcula o seu custo
    ###############################

    def calcula_custo(self, caminho):
        # caminho é uma lista de nodos
        teste = caminho
        custo = 0
        i = 0
        while i + 1 < len(teste):
            custo = custo + self.get_arc_cost(teste[i], teste[i + 1])
            i = i + 1
        return custo

    ################################################################################
    #     procura DFS  -- To Do
    ####################################################################################

    def dfs(self, start):
        visited = set()
        stack = [start]
        order = []
        while stack:
            node = stack.pop()
            if node not in visited:
                visited.add(node)
                order.append(node)
                # Add neighbors in reverse for consistent order
                for neighbor, _ in reversed(self.m_graph[node]):
                    if neighbor not in visited:
                        stack.append(neighbor)
        return order

    #####################################################
    # Procura BFS -- To Do
    ######################################################

    def bfs(self, start):
        visited = set()
        queue = [start]
        order = []
        while queue:
            node = queue.pop(0)
            if node not in visited:
                visited.add(node)
                order.append(node)
                for neighbor, _ in self.m_graph[node]:
                    if neighbor not in visited:
                        queue.append(neighbor)
        return order

  
    ####################
    # funçãop  getneighbours, devolve vizinhos de um nó
    ##############################

    def getNeighbours(self, nodo):
        lista = []
        for (adjacente, peso) in self.m_graph[nodo]:
            lista.append((adjacente, peso))
        return lista

    ###########################
    # desenha grafo  modo grafico
    #########################

    def desenha(self):
        ##criar lista de vertices
        lista_v = self.m_nodes
        lista_a = []
        g = nx.Graph()
        for nodo in lista_v:
            n = nodo.getName()
            g.add_node(n)
            for (adjacente, peso) in self.m_graph[n]:
                lista = (n, adjacente)
                # lista_a.append(lista)
                g.add_edge(n, adjacente, weight=peso)

        pos = nx.spring_layout(g)
        nx.draw_networkx(g, pos, with_labels=True, font_weight='bold')
        labels = nx.get_edge_attributes(g, 'weight')
        nx.draw_networkx_edge_labels(g, pos, edge_labels=labels)

        plt.draw()
        plt.show()

    ####################################33
    #    add_heuristica   -> define heuristica para cada nodo 1 por defeito....
    ################################3

    def add_heuristica(self, n, estima):
        n1 = Node(n)
        if n1 in self.m_nodes:
            self.m_h[n] = estima



    ##########################################
    #    A* - To Do
    ##########################################

    def procura_aStar(self, start, goal):
        open_set = {start}
        closed_set = set()
        g_scores = {start: 0}
        # f_scores stores the total estimated cost from start to goal through a given node.
        # f_score = g_score + h_score (heuristic)
        f_scores = {start: self.getH(start)}
        parents = {start: None}

        while open_set:
            current_node = None
            for node in open_set:
                if current_node is None or f_scores.get(node, float('inf')) < f_scores.get(current_node, float('inf')):
                    current_node = node
                    
            if current_node == goal:
                path = []
                while current_node is not None:
                    path.append(current_node)
                    current_node = parents[current_node]
                path.reverse()
                return path

            # If there are no more nodes to check and we haven't reached the goal, no path exists.
            if current_node is None:
                print("Path does not exist!")
                return None


            open_set.remove(current_node)
            closed_set.add(current_node)


            for neighbor, weight in self.getNeighbours(current_node):
                # If the neighbor has already been evaluated, skip it.
                if neighbor in closed_set:
                    continue
                
                tentative_g_score = g_scores.get(current_node, float('inf')) + weight

                # If this path to the neighbor is better than any previously recorded path...
                if tentative_g_score < g_scores.get(neighbor, float('inf')):
                    # ...update the parent, g_score, and f_score for the neighbor.
                    parents[neighbor] = current_node
                    g_scores[neighbor] = tentative_g_score
                    f_scores[neighbor] = tentative_g_score + self.getH(neighbor)
                    
                    # If the neighbor is not in the open set, add it so it can be evaluated.
                    if neighbor not in open_set:
                        open_set.add(neighbor)

        # If the open set is empty and we haven't found the goal, no path exists.
        print("Path does not exist!")
        return None



    ###################################3
    # devolve heuristica do nodo
    ####################################

    def getH(self, nodo):
        if nodo not in self.m_h.keys():
            return 1000
        else:
            return (self.m_h[nodo])


    ##########################################
    #   Greedy - To Do
    ##########################################

    def greedy(self, start, end):
        open_list = set([start])
        closed_list = set()
        parents = {start: None}

        while open_list:
            # Select node with lowest heuristic value
            current = min(open_list, key=lambda n: self.getH(n))

            if current == end:
                # Reconstruct path
                path = []
                while current is not None:
                    path.append(current)
                    current = parents[current]
                path.reverse()
                return path

            open_list.remove(current)
            closed_list.add(current)

            for neighbor, _ in self.getNeighbours(current):
                if neighbor in closed_list:
                    continue
                if neighbor not in open_list:
                    open_list.add(neighbor)
                    parents[neighbor] = current

        # No path found
        return None



    def update_cost(self, node1, node2, new_cost):
        if node1 in self.m_graph:
            for index, (adjacent, cost) in enumerate(self.m_graph[node1]):
                if adjacent == node2:
                    self.m_graph[node1][index] = (node2, new_cost)
                    break

        if not self.m_directed and node2 in self.m_graph:
            for index, (adjacent, cost) in enumerate(self.m_graph[node2]):
                if adjacent == node1:
                    self.m_graph[node2][index] = (node1, new_cost)
                    break

    def update_heuristic(self, node, new_heuristic):
        if node in self.m_h:
            self.m_h[node] = new_heuristic
        else:
            print(f"Heuristic for node {node} not found.")