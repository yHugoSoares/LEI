#include <stdio.h>
#include <stdlib.h>

typedef int WEIGHT;

#define NE -1
#define MAX 10

typedef WEIGHT GraphM[MAX][MAX];

GraphM graphM ={{  0, NE, NE, NE, NE, NE, NE, NE, NE, NE },
                { NE,  0, NE, NE, NE, NE, NE, 11, NE, NE },
                { NE, NE,  0,  5, NE, NE, NE, NE, NE, NE }, // Edge: 2 -> 3 (weight 5)
                { NE, NE,  5,  0, NE, NE, 12, NE, NE, NE }, // Edge: 3 -> 6 (weight 7)
                { NE, 62, NE, NE,  0, NE, NE, NE, NE,  4 },
                { NE, NE, NE, NE, NE,  0, NE, NE, NE, NE },
                { NE, NE, NE, 12, NE, NE,  0, NE, NE, NE },
                { NE, NE, 32, NE, NE, NE, NE,  0, NE, NE },
                { NE, NE, NE, NE, NE, NE, NE, NE,  0, NE },
                { NE, NE, NE, NE, 20, NE, NE,  8, NE,  0 }};

typedef struct edge {
    int dest;
    WEIGHT weight;
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

    // Para o vértice 4:
    out[4] = malloc(sizeof(struct edge));
    out[4]->dest = 3;   // 4 -> 3
    out[4]->weight = 1;

    // Para o vértice 5:
    out[5] = malloc(sizeof(struct edge));
    out[5]->dest = 4;   // 5 -> 4
    out[5]->weight = 2;

    // Para o vértice 6:
    out[6] = malloc(sizeof(struct edge));
    out[6]->dest = 5;   // 6 -> 5
    out[6]->weight = 3;

    // Para o vértice 7:
    out[7] = malloc(sizeof(struct edge));
    out[7]->dest = NE;
    out[7]->weight = NE;

    // Para o vértice 8:
    out[8] = malloc(sizeof(struct edge));
    out[8]->dest = NE;
    out[8]->weight = NE;

    // Para o vértice 9:
    out[9] = malloc(sizeof(struct edge));
    out[9]->dest = 8;
    out[9]->weight = 4;
}

int pesoC (GraphM g, int V[], int k) {
    int result = 0;
    for (int i = 0; i < k - 1; i++)
    {
        int custo = g[V[i]][V[i+1]];
        if (custo == NE) return -1;
        result += custo;
    }
    return result;
}

void componentes(GraphL g, int n, int comp[]) {
    int v[n], counter;
    for (int i = 0; i < n; i++) v[i] = 0;

    for (int i = 0; i < n; i++)
    {
        int c = i;
        if (v[i] == 0)
        {
            Edge temp = g[i];
            v[i] = 1;
            comp[i] = counter;
            while (temp != NULL && temp->dest != NE)
            {
                v[c] = 1;
                c = temp->dest;
                temp = g[c];
            }
            counter++;
        }
    }
} // Not working

int main () {
    int v[] = {2,3,6}, comp[MAX];
    GraphL graphL;
    create_exemploL(graphL);
    printf("PesoC: %d\n", pesoC(graphM, v, 3));

    
    printf("Componentes:\n");
    componentes(graphL, MAX, comp);
    int length = sizeof(comp) / sizeof(comp[0]);
    for (int i = 0; i < MAX; i++)
    {
        printf("%d ", comp[i]);
    }
    printf("\n");

    return 0;
}