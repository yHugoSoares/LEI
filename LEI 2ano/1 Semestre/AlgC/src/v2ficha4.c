#include <stdio.h>
#include <stdlib.h>

#define NV 10

typedef struct aresta {
    int dest;
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL[NV];

typedef int GrafoM[NV][NV];

GrafoM exemploM = { {0, 1, 2, 0, 0, 0, 2, 0, 0, 3},
                    {0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 4, 0, 0, 0, 7, 0},
                    {0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
                    {0, 0, 0, 0, 0, 0, 3, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 7, 0, 0},
                    {0, 0, 0, 2, 0, 0, 0, 0, 8, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
                    {1, 0, 0, 0, 2, 0, 1, 0, 0, 0},
                    {0, 0, 3, 0, 0, 5, 0, 0, 2, 0} };


void fromMat(GrafoM in, GrafoL out) {
    for (int i = 0; i < NV; i++) {
        out[i] = NULL;
        for (int j = 0; j < NV; j++)
            if (in[i][j] != 0) {
                LAdj temp = malloc(sizeof (struct aresta));
                temp->dest = j;
                temp->custo = in[i][j];
                temp->prox = out[i];
                out[i] = temp;
            }
    }
}



int main() {
    GrafoL out;

    fromMat(exemploM, out);

    for (int i = 0; i < NV; i++)
    {
        for (LAdj j = out[i]; j != NULL; j = j->prox)
            printf("%d -> %d (cost: %d) ", i, j->dest, j->custo);
        printf("\n");
    }

}