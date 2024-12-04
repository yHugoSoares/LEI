#include <stdio.h>
#include <stdlib.h>

#define NV 7

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

int ordTop (GrafoL g, int ord[]) {
    int v[NV], counter = 0, x = 0, deg[NV] = {0}, degZero[NV];

    for (int i = 0; i < NV; i++) {
        LAdj temp = g[i];
        while (temp != NULL) {
            deg[temp->dest]++; // Incrementa o grau de entrada do vértice temp->dest
            temp = temp->prox;
        }
    }
    for (int i = 0; i < NV; i++)
    {
        if (deg[i] == 0)
        {
            ord[counter++] = i;
        }
    }
    for (int i = 0; i < NV; i++)
    {
        LAdj temp = g[ord[i]];
        while (temp != NULL)
        {
            deg[temp->dest]--;
            if (deg[temp->dest] == 0) ord[counter++] = temp->dest;      
            temp = temp->prox;
        }
    }

    return 1;
}

int ciclo (GrafoL g, int c[]) {
    int v[NV], p[NV];
    for (int i = 0; i < NV; i++)
    {
        v[i] = -1;
        p[i] = -1;
    }
    
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
                if (c[0] == c[counter])
                {
                    return 1;
                }
            }
            c[counter] = temp->dest;
            v[temp->dest] = -1;
            counter++;
            temp = temp->prox;
        }
    }
    
    return 0;
}

void swap (int v[], int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int minIndPeso (int v[], int pesos[], int tam) {
    int i, r = 0;
    for (i=1; i<tam; i++)
    if (pesos[v[i]] < pesos[v[r]]) r = i;
    return r;
}

int minIndPesoPrism (int v[], int pesos[], int tam) {
    int i, r = 0;
    for (i=1; i<tam; i++)
    if (pesos[v[i]] < pesos[v[r]]) r = i;
    return r;
}

int dijkstraSP (GrafoL g, int or, int pais[], int pesos[]) {
    int r, i, v, cor [NV], orla[NV], tam;
    LAdj x;
    // inicializacoes
    for (i=0; i<NV; i++) {
        pais[i] = -2; cor[i] = 0 ; // nao visitado
    }
    r = 0; orla[0] = or; tam = 1;
    pesos[or] = 0; pais[or] = -1; cor [or] = 1; // na orla
    // ciclo
    while (tam>0) {
        // seleccionar vertice de menor peso
        i = minIndPeso (orla, pesos,tam);
        swap (orla, i, --tam);
        v = orla[tam];
        r++; cor[v] = 2; //visitado
        for (x=g[v]; x!=NULL; x=x->prox){
            if (cor[x->dest] == 0) {
                cor[x->dest] = 1; orla[tam++] = x->dest;
                pais[x->dest] = v;
                pesos[x->dest] = pesos[v] + x->custo;
            }
            else if (cor[x->dest] == 1 && pesos[v] + x->custo < pesos[x->dest]) {
                pais[x->dest] = v;
                pesos[x->dest] = pesos[v] + x->custo;
            }
        }
    }
return r;
}

int excentricidadeV (GrafoL g, int v) {
    int pais[NV], pesos[NV];
    int max = 0;
    int nodes = dijkstraSP(g, v, pais, pesos);
    for (int i = 0; i < NV; i++)
    {
        if (max <= pesos[i])
        {
            max = pesos[i];
        }   
    }
    return max;
}

int dijkstraSP2 (GrafoL g, int or, int pais[], int pesos[], int valor) {
    int r, i, v, cor [NV], orla[NV], tam;
    LAdj x;
    // inicializacoes
    for (i=0; i<NV; i++) {
        pais[i] = -2; cor[i] = 0 ; // nao visitado
    }
    r = 0; orla[0] = or; tam = 1;
    pesos[or] = 0; pais[or] = -1; cor [or] = 1; // na orla
    // ciclo
    while (tam>0) {
        // seleccionar vertice de menor peso
        i = minIndPeso (orla, pesos, tam);
        swap (orla, i, --tam);
        v = orla[tam];
        r++; 
        cor[v] = 2; //visitado
        for (x=g[v]; x!=NULL; x=x->prox){
            if (cor[x->dest] == 0) {
                cor[x->dest] = 1; orla[tam++] = x->dest;
                pais[x->dest] = v;
                pesos[x->dest] = pesos[v] + x->custo;
            }
            else if (cor[x->dest] == 1 && pesos[v] + x->custo < pesos[x->dest]) {
                pais[x->dest] = v;
                pesos[x->dest] = pesos[v] + x->custo;
            }
        }
    }
    for (int i = 0; i < NV; i++)
    {
        if ((pesos[i] >= valor || pesos[i] == 0) && i != or)
        {
            pesos[i] = -1;
        }
    }
    
return r;
}

int PrismSP (GrafoL g, int pais[], int pesos[]) {
    int r, i, v, or, cor [NV], orla[NV], tam;
    LAdj x;
    // inicializacoes
    for (i=0; i<NV; i++) {
        pesos[i] = __INT_MAX__;
        pais[i] = -2;
        cor[i] = 0 ; // nao visitado
    }
    r = 0;
    tam = 1;
    or = 0;
    orla[0] = or;
    pesos[or] = 0; pais[or] = -1; cor [or] = 1; // na orla
    // ciclo
    while (tam>0) {
        // seleccionar vertice de menor peso
        i = minIndPeso (orla, pesos,tam);
        swap (orla, i, --tam);
        v = orla[tam];
        r+=pesos[v];
        cor[v] = 2; //visitado
        for (x=g[v]; x!=NULL; x=x->prox){
            if (cor[x->dest] == 0) {
                cor[x->dest] = 1;
                orla[tam++] = x->dest;
                pais[x->dest] = v;
                pesos[x->dest] = x->custo; // Update weight correctly
            }
            else if (cor[x->dest] == 1 && x->custo < pesos[x->dest]) {
                pais[x->dest] = v;
                pesos[x->dest] = x->custo; // Update weight correctly
            }
        }
    }
    return r;
}


int main() {
    GrafoL out;
    create_exemploL(out);
    int pais[NV], pesos[NV];

    // Teste 1
    PrismSP(out, pais, pesos);
    for (int i = 0; i < NV; i++)
    {
        printf("%d ", pesos[i]);
    }
    printf("\n");

    return 0;
}



// Questions: 
// 1. um veneno estragado mata mais ou menos ? mais ou menos o que ?
// 2. as zebras sao brancas com listras pretas ou pretas com listras brancas ? branca com listras pretas
// 3. se as mulheres estao sempre certas pq e que escolhes o homem errado ? certo