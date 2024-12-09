#include <stdio.h>
#include <stdlib.h>

typedef int WEIGHT;

#define NE -1
#define MAX 5

typedef WEIGHT GraphM[MAX][MAX];

#define NE -1

int graphM[MAX][MAX] = {
    { NE,   4,   3,  10,  NE },
    {  4,  NE,   2,  NE,  40 },
    {  3,   2,  NE,  NE,  NE },
    { 10,  NE,  NE,  NE,   2 }, 
    { NE,  40,  NE,   2,  NE }};


typedef struct edge {
    int dest;
    WEIGHT weight;
    struct edge *next;
} *Edge, *GraphL[MAX];

void create_exemploL(GraphL out){
    // Para o vértice 0:
    out[0] = malloc(sizeof(struct edge));
    out[0]->dest = 1;   // 0 -> 2
    out[0]->weight = 4;


    // Para o vértice 1:
    out[1] = malloc(sizeof(struct edge));
    out[1]->dest = 2;   // 1 -> 2
    out[1]->weight = 1;

    // Para o vértice 2:
    out[2] = malloc(sizeof(struct edge));
    out[2]->dest = 3;   // 2 -> 3
    out[2]->weight = 3;

    // Para o vértice 3:
    out[3] = malloc(sizeof(struct edge));
    out[3]->dest = NE;
    out[3]->weight = NE;
}

void printGraphL(GraphL graphL) {
    for (int i = 0; i < MAX; i++)
    {
        Edge x = graphL[i];
        while (x != NULL)
        {
            printf("%d :%d\n", i, x->dest);
            x = x->next;
        }
    }
}

void fromMat(GraphM in, GraphL out) {
    for (int i = 0; i < MAX; i++) {
        out[i] = NULL;
        for (int j = 0; j < MAX; j++) {
            if (in[i][j] != NE) {
                Edge newAresta = malloc(sizeof (struct edge));
                newAresta->dest = j;
                newAresta->weight = in[i][j];
                newAresta->next = out[i];
                out[i] = newAresta;
            }
        }
    }
}

int pesoC (GraphM g, int V[], int k) {
    int result = 0;
    for (int i = 0; i < k - 1; i++)
    {
        int custo = g[V[i]][V[i+1]];
        if (custo == NE) return -1;
        else result += custo;
    }
    return result;
}


void dfs(GraphL g, int o, int comp[], int c) // travessia em profundidade; poderia ser em largura
{
    Edge p;
    comp[o] = c;
    for (p = g[o]; p; p = p->next) {
        if (comp[p->dest] == -1) dfs(g, p->dest, comp, c);
    }
}

void componentes(GraphL g, int n, int comp[])
{
    int i, c = 0;
    // c = índice dos componentes, começando em 0
    for (i = 0; i < n; i++) comp[i] = -1;
    // este array servirá também para controlar a travessia
    // dispensando um array de cores ou 'visitados'
    for (i = 0; i < n; i++)
        if (comp[i] == -1) {
            dfs(g, i, comp, c);
            c++;
        }
}

int main () {
    int v[] = {2,3,6}, comp[MAX];
    GraphL graphL;
    fromMat(graphM, graphL);

    
    
    
    printf("PesoC: %d\n", pesoC(graphM, v, 3));

    
    printf("Componentes: ");
    componentes(graphL, MAX, comp);
    int length = sizeof(comp) / sizeof(comp[0]);
    for (int i = 0; i < MAX; i++)
    {
        printf("%d ", comp[i]);
    }
    printf("\n");

    return 0;
}