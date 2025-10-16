from Graph import Graph
from Node import Node



def main():
    g = Graph()

    #FichaTP2
    g.add_edge("Gualtar", "SVitor", 8)
    g.add_edge("SVitor", "SVicente", 6)
    g.add_edge("SVicente", "Nogueiro", 8)
    g.add_edge("Gualtar", "EsteSMamede", 6)
    g.add_edge("EsteSMamede", "Sobreposta", 3)
    g.add_edge("Sobreposta", "Nogueiro", 6)
    g.add_edge("EsteSMamede", "Lamacaes", 8)
    g.add_edge("Lamacaes", "Fraiao", 3)
    g.add_edge("Fraiao", "Nogueiro", 6)
    

    #FichaTP2
    g.add_heuristica("Gualtar", 8)
    g.add_heuristica("SVitor", 2)
    g.add_heuristica("SVicente", 6)
    g.add_heuristica("EsteSMamede", 7)
    g.add_heuristica("Sobreposta", 4)
    g.add_heuristica("Lamacaes", 4)
    g.add_heuristica("Fraiao", 3)
    g.add_heuristica("Nogueiro", 0)

    saida = -1
    while saida != 0:
        print("1-Imprimir Grafo")
        print("2-Desenhar Grafo")
        print("3-Imprimir  nodos de Grafo")
        print("4-Imprimir arestas de Grafo")
        print("5-DFS")
        print("6-BFS")
        print("7-A*")
        print("8-Gulosa")
        print("0-Saír")

        saida = int(input("introduza a sua opcao-> "))
        if saida == 0:
            print("saindo.......")
        elif saida == 1:
            print(g.m_graph)
            l = input("prima enter para continuar")
        elif saida == 2:
            g.desenha()
        elif saida == 3:
            print(g.m_graph.keys())
            l = input("prima enter para continuar")
        elif saida == 4:
            print(g.imprime_aresta())
            l = input("prima enter para continuar")
        elif saida == 5:
            inicio = input("Nodo inicial->")
            fim = input("Nodo final->")
            print(g.procura_DFS(inicio, fim, path=[], visited=set()))
            l = input("prima enter para continuar")
        elif saida == 6:
            inicio = input("Nodo inicial->")
            fim = input("Nodo final->")
            print(g.procura_BFS(inicio, fim))
            l = input("prima enter para continuar")
        elif saida == 7:
            inicio = input("Nodo inicial->")
            fim = input("Nodo final->")
            print(g.procura_aStar(inicio, fim))
            l = input("prima enter para continuar")
        elif saida == 8:
            inicio = input("Nodo inicial->")
            fim = input("Nodo final->")
            print(g.greedy(inicio, fim))
            l = input("prima enter para continuar")
        else:
            print("you didn't add anything")
            l = input("prima enter para continuar")


if __name__ == "__main__":
    main()
