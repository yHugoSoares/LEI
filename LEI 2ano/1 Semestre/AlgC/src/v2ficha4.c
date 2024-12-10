#include <stdio.h>
#include <stdlib.h>

#define NV 5

typedef struct aresta {
    int dest;
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL[NV];

typedef int GrafoM[NV][NV];

GrafoM exemploM = 
   {{0, 2, 0, 6, 0},
    {2, 0, 3, 8, 5},
    {0, 3, 0, 0, 7},
    {6, 8, 0, 0, 9},
    {0, 5, 7, 9, 0}};

void printGraph(GrafoL g) {
    for (int i = 0; i < NV; i++) {
        for (LAdj p = g[i]; p != NULL; p = p->prox) {
            printf("%d -> %d (custo: %d) ", i, p->dest, p->custo);
        }
        printf("\n");
    }
}

void fromMat (GrafoM in, GrafoL out) {
    for (int i = 0; i < NV; i++) out[i] = NULL;
    for (int i = 0; i < NV; i++)
    {
        for (int j = 0; j < NV; j++)
        {
            LAdj x = malloc(sizeof(struct aresta));
            if (in[i][j] != 0)
            {
                x->dest = j;
                x->custo = in[i][j];
                x->prox = out[i];
                out[i] = x;
            }   
        }
    }
}

void inverte (const GrafoL in, GrafoL out) {
    for (int i = 0; i < NV; i++) out[i] = NULL;
    for (int i = 0; i < NV; i++)
    {
        LAdj inLAdj = in[i];
        while (inLAdj != NULL)
        {
            LAdj novo = malloc(sizeof(struct aresta));

            novo->custo = inLAdj->custo;
            novo->dest = i;
            novo->prox = out[inLAdj->dest];
            out[inLAdj->dest] = novo;

            inLAdj = inLAdj->prox;
        }
    }
}

int inDegree (GrafoL g) {
    int a[NV] = {0};

    for (int i = 0; i < NV; i++)
    {
        LAdj x = g[i];
        while (x != NULL)
        {
            a[x->dest]++;
            x = x->prox;
        }
    }

    int maior = 0;
    for (int i = 0; i < NV; i++)
    {
        if (maior < a[i]) maior = a[i];
    }
    return maior;
}

int colorOK (GrafoL g, int cor[]) {
    
}


int main() {
    GrafoL out, out2;

    fromMat(exemploM, out);
    inverte(out, out2);

    printGraph(out);
    printf("Maior: %d\n", inDegree(out));
}