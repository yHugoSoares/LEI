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

void printComponentes(int c[]) {
    printf("Componentes: ");
    for (int i = 0; i < NV; i++)
    {
        printf("%d ", c[i]);
    }
    printf("\n");
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
    for (int i = 0; i < NV; i++)
    {
        LAdj x = g[i];
        while (x != NULL)
        {
            if (cor[i] == cor[x->dest]) return 0;
            x = x->prox;
        }
    }
    return 1;
}

int homomorfOK (GrafoL g, GrafoL h, int f[]) {
    for (int i = 0; i < NV; i++)
    {
        LAdj gLAdj = g[i];
        int origem = f[i];
        while (gLAdj != NULL)
        {
            int destino = f[gLAdj->dest];
            LAdj hLAdj = h[origem];

            int found = 0;
            while (hLAdj != NULL)
            {
                if (hLAdj->dest == destino)
                {
                    found = 1;
                    break;
                }
                hLAdj = hLAdj->prox;
            }
            if (!found) return 0;

            gLAdj = gLAdj->prox;
        }
    }
    return 1;
}

int DFRec (GrafoL g, int or, int v[], int p[], int l[]) {
    int i;
    LAdj a;
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
    p[or] = -1;
    l[or] = 0;
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
    v[or] = 1;
    l[or]=0;
    p[or]=-1; //redundante
    i=1;
    while (front != end) {
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
    return DF(g, or, v, p, l);
}

void dfs(GrafoL g, int o, int c[], int x) // travessia em profundidade; poderia ser em largura
{
    LAdj p;
    c[o] = x;
    for (p = g[o]; p; p = p->prox) {
        if (c[p->dest] == -1) dfs(g, p->dest, c, x);
    }
}

void componentes(GrafoL g, int c[])
{
    int i, x = 0;

    for (i = 0; i < NV; i++) c[i] = -1;

    for (i = 0; i < NV; i++)
        if (c[i] == -1) {
            dfs(g, i, c, x);
            x++;
        }
}

int main() {
    GrafoL out, out2;
    int c[NV] = {0};

    fromMat(exemploM, out);
    inverte(out, out2);
    componentes(out, c);

    printGraph(out);
    printf("Maior: %d\n", inDegree(out));
    printComponentes(c);
    
}