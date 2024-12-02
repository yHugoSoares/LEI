#include <stdio.h>
#include <stdlib.h>

#define NV 10

typedef struct aresta {
    int dest;
    int custo;
    struct aresta *prox;
} *LAdj, *GrafoL[NV];

typedef int GrafoM[NV][NV];

GrafoM exemploM = {
        {0, 1, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 3, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 12, 0},
        {0, 0, 0, 0, 0, 5, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 6, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 0, 0},
        {0, 0, 0, 2, 0, 0, 0, 0, 8, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 9},
        {1, 0, 0, 0, 2, 0, 0, 0, 0, 0},
        {0, 0, 3, 0, 0, 5, 0, 0, 2, 0}
    };

void create_exemploL(GrafoL out){
    // Para o vértice 0:
    out[0] = malloc(sizeof(struct aresta));
    out[0]->dest = 2;   // 0 -> 2
    out[0]->custo = 4;
    out[0]->prox = malloc(sizeof(struct aresta));
    out[0]->prox->dest = 1;   // 0 -> 1
    out[0]->prox->custo = 2;
    out[0]->prox->prox = NULL;

    // Para o vértice 1:
    out[1] = malloc(sizeof(struct aresta));
    out[1]->dest = 2;   // 1 -> 2
    out[1]->custo = 1;
    out[1]->prox = NULL;

    // Para o vértice 2:
    out[2] = malloc(sizeof(struct aresta));
    out[2]->dest = 3;   // 2 -> 3
    out[2]->custo = 3;
    out[2]->prox = NULL;

    // Para o vértice 3:
    out[3] = NULL; // Sem arestas saindo de 3

    // Para o vértice 4:
    out[4] = malloc(sizeof(struct aresta));
    out[4]->dest = 3;   // 4 -> 3
    out[4]->custo = 1;
    out[4]->prox = NULL;

    // Para o vértice 5:
    out[5] = malloc(sizeof(struct aresta));
    out[5]->dest = 4;   // 5 -> 4
    out[5]->custo = 2;
    out[5]->prox = NULL;

    // Para o vértice 6:
    out[6] = malloc(sizeof(struct aresta));
    out[6]->dest = 5;   // 6 -> 5
    out[6]->custo = 3;
    out[6]->prox = malloc(sizeof(struct aresta));
    out[6]->prox->dest = 2;   // 6 -> 2
    out[6]->prox->custo = 1;
    out[6]->prox->prox = NULL;
}

void fromMat(GrafoM in, GrafoL out) {
    for (int i = 0; i < NV; i++) {
        out[i] = NULL;
        for (int j = 0; j < NV; j++) {
            if (in[i][j] != 0) {
                LAdj newAresta = malloc(sizeof(struct aresta));
                newAresta->dest = j;
                newAresta->custo = in[i][j];
                newAresta->prox = out[i];
                out[i] = newAresta;
            }
        }
    }
}

void inverte(GrafoL in, GrafoL out) {
    for (int i = 0; i < NV; i++)
    {
        out[i] = NULL;
        LAdj temp = in[i];
        while (temp != NULL)
        {
            LAdj newAresta = malloc(sizeof(struct aresta));
            newAresta->dest = i;
            newAresta->custo = temp->custo;
            newAresta->prox = out[temp->dest];
            
            out[temp->dest] = newAresta;
            temp = temp->prox;

        }
    }
}

int inDegree(GrafoL out) {
    int degrees[NV] = {0}; // Inicializa os graus de entrada de todos os vértices com 0

    for (int i = 0; i < NV; i++) {
        LAdj temp = out[i];
        while (temp != NULL) {
            degrees[temp->dest]++; // Incrementa o grau de entrada do vértice temp->dest
            temp = temp->prox;
        }
    }

    // Encontra o maior grau de entrada
    int maxDegree = 0;
    for (int i = 0; i < NV; i++) {
        if (degrees[i] > maxDegree) {
            maxDegree = degrees[i];
        }
    }

    return maxDegree;
}

int colorOK (GrafoL g, int cor[]) {
    for (int i = 0; i < NV; i++)
    {
        LAdj temp = g[i];
        while (temp != NULL) {
            if (cor[i] == cor[temp->dest]) {
                return 0;
            }
            temp = temp->prox;
        }
    }
    return 1;
}

int homomorfOK (GrafoL g, GrafoL h, int f[]) {
    for (int i = 0; i < NV; i++)
    {
        LAdj temp = g[i];
        while (temp != NULL)
        {
            int origem = f[i];
            int destino = f[temp->dest];

            LAdj htemp = h[origem];
            int found = 0;
            while (htemp != NULL)
            {
                if (htemp->dest == destino)
                {
                    found = 1;
                }
                htemp = htemp->prox;
            }
            
            if (!found)
            {
                return 0;
            }
            
            temp = temp->prox;
        }
    }
    return 1;
}

int DF (GrafoL g, int or, int v[], int p[], int l[]) {
    int i;
    for (i=0; i<NV; i++) {
        v[i]=0;
        p[i] = -1;
        l[i] = -1;
    }
    p[or] = -1; l[or] = 0;
    return DFRec (g,or,v,p,l);
}

int DFRec (GrafoL g, int or, int v[], int p[], int l[]) {
    int i; LAdj a;
    i=1;
    v[or]=-1;
    for (a=g[or]; a!=NULL; a=a->prox)
    if (!v[a->dest]){
        p[a->dest] = or;
        l[a->dest] = 1+l[or];
        i+=DFRec(g,a->dest,v,p,l);
    }
    v[or]=1;
    return i;
}

int BF (GrafoL g, int or, int v[], int p[], int l[]) {
    int i, x; LAdj a;
    int q[NV], front, end;
    for (i=0; i<NV; i++) {
        v[i]=0;
        p[i] = -1;
        l[i] = -1;
    }
    front = end = 0;
    q[end++] = or; //enqueue
    v[or] = 1; l[or]=0; p[or]=-1; //redundante
    i=1;
    while (front != end){
        x = q[front++]; //dequeue
        for (a=g[x]; a!=NULL; a=a->prox)
        if (!v[a->dest]) {
            i++;
            v[a->dest]=1;
            p[a->dest]=x;
            l[a->dest]=1+l[x];
            q[end++]=a->dest; //enqueue
        }   
    }
    return i;
}

int maisLonga (GrafoL g, int or, int p[]) {
    int v[NV], l[NV];
    DF(g, or, v, p, l);

    int maxDistance = -1;
    int furthestVertex = -1;

    for (int i = 0; i < NV; i++)
    {
        if (v[i] && l[i] > maxDistance)
        {
            maxDistance = l[i];
            furthestVertex = i;
        }
    }
    
    return maxDistance;
}

int ciclo (GrafoL g, int c[]) {
    int v[NV], p[NV], l[NV];
    for (int i = 0; i < NV; i++)
    {
        c[0] = i;
        LAdj temp = g[i];
        while (temp != NULL)
        {
            int counter = 1;
            if (v[temp->dest] == -1)
            {
                c[counter] = temp->dest;
                return c;
            }
            c[counter] = temp->dest;
            v[temp->dest] = -1;
            counter++;
            temp = temp->prox;
        }
    }
    
    return 0;
}

int ciclo2 (GrafoL g, int c[]) {
    int v[NV], p[NV], l[NV];
    for (int i = 0; i < NV; i++)
    {
        v[i] = 0;
        p[i] = -1;
    }

    for (int i = 0; i < NV; i++)
    {
        if (!v[i])
        {
            if (cicloRec(g, i, c, v, p))
            {
                return 1;
            }
            
        }
        
    }
    
    
    return 0;
}


int main() {

    return 0;
}



// Questions: 
// 1. um veneno estragado mata mais ou menos ? mais ou menos o que ?
// 2. as zebras sao brancas com listras pretas ou pretas com listras brancas ? branca com listras pretas
// 3. se as mulheres estao sempre certas pq e que escolhes o homem errado ? certo