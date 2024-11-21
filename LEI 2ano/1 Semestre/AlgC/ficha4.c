#include <stdio.h>
#include <stdlib.h>

#define NV 10
typedef struct aresta {
    int dest; int custo;
    struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];

void fromMat (GrafoM in, GrafoL out){
    for (int i = 0; i < NV; i++)
    {
        LAdj goesIn = out[i];
        for (int j = 0; j < NV; j++)
        {
            if (in[i][j] != 0)
            {
                LAdj temp = malloc(sizeof(struct aresta));
                temp->dest = j;
                temp->custo = in[i][j];
                while (goesIn->prox != NULL)
                {
                    goesIn = goesIn->prox;
                }
                temp = goesIn;
            }
        }
        out[i] = goesIn;
    }
}


void inverte (GrafoL in, GrafoL out){

}

int main(){

    
    
    return 1;
}