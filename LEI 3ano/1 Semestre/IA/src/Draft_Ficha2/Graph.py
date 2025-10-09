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

    def a_star(self, start, goal):
    
        open_set = set([start])
        closed_set = set()
        g_scores = {node: float('inf') for node in self.m_graph}
        g_scores[start] = 0
        f_scores = {node: float('inf') for node in self.m_graph}
        f_scores[start] = self.getH(start)
        parents = {start: None}

        while open_set:
            current = min(open_set, key=lambda n: f_scores[n])

            if current == goal:
                path = []
                while current is not None:
                    path.append(current)
                    current = parents[current]
                path.reverse()
                return path

            open_set.remove(current)
            closed_set.add(current)

            for neighbor, weight in self.getNeighbours(current):
                if neighbor in closed_set:
                    continue
                tentative_g_score = g_scores[current] + weight

                if neighbor not in open_set:
                    open_set.add(neighbor)
                elif tentative_g_score >= g_scores[neighbor]:
                    continue

                parents[neighbor] = current
                g_scores[neighbor] = tentative_g_score
                f_scores[neighbor] = g_scores[neighbor] + self.getH(neighbor)

        return None  # No path found
        


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

