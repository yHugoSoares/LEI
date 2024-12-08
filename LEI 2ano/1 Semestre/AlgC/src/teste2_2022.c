#include <stdio.h>
#include <stdlib.h>

<<<<<<< HEAD
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
=======
#define N 10

typedef struct avlnode {
int valor; int bal;
struct avlnode *esq, *dir;
} *AVLTree;

// Função para calcular o fator de balanço
int calcularFator(AVLTree t) {
    if (!t) return 0;
    int alturaEsq = t->esq ? altura(t->esq) : 0;
    int alturaDir = t->dir ? altura(t->dir) : 0;
    return alturaEsq - alturaDir;
}

AVLTree build(int a[], int no) {
    int meio = N/2;

    // Criação do nó atual
    AVLTree novo = (AVLTree)malloc(sizeof(struct avlnode));
    novo->valor = a[meio];
    novo->esq = build(a, meio - 1);
    novo->dir = build(a + meio + 1, no - meio - 1);

    novo->bal = calcularFator(novo);

    return novo;
}

int h[] = {10, 15, 11, 16, 22, 35, 20, 21, 23, 34, 37, 80, 43, 22, 25, 24, 28}; 

void bubbleDown(int h[], int no, int i) {
    
    while (i < no)
    {
        if (i*2+2 < no && h[i] < h[i*2+1] && h[i] < h[i*2+2])
        {
            break;
        }
        if (i*2+1 < no && i*2+2 == no) {
            int temp = h[i];
            h[i] = h[i*2+1];
            h[i*2+1] = temp;
            i = i*2+1;
        }
        else if (i*2+2 < no && h[i*2+2] > h[i*2+1]) {
            int temp = h[i];
            h[i] = h[i*2+1];
            h[i*2+1] = temp;
            i = i*2+1;
        }
        else if (i*2+2 < no) {
            int temp = h[i];
            h[i] = h[i*2+2];
            h[i*2+2] = temp;
            i = i*2+2;
        }
    }   
}

int decrease(int x, int y, int h[], int no) {
    if (x > y) return 0;
    int indice = 0;
    for (int i = 0; i < no; i++)
        if (h[i] == x) h[i] = y, indice = i;

    bubbleDown(h, no, indice);
    
    return 1;
}

int image[N][N] =  {{0,0,0,0,0,0},
                    {0,1,0,1,1,0},
                    {0,1,1,1,0,0},
                    {0,1,0,0,1,0},
                    {0,0,1,1,1,0},
                    {0,0,0,0,0,0}};

int DFS(int v[N][N], int image[N][N], int x, int y) {
    int tam = 0;
    v[x][y] = 1;
    
    if (x+1 > N && !v[x+1][y] && image[x+1][y]) tam += DFS(v, image, x+1, y);
    if (x-1 < 0 && !v[x-1][y] && image[x-1][y]) tam += DFS(v, image, x-1, y);
    if (y+1 > N && !v[x][y+1] && image[x][y+1]) tam += DFS(v, image, x, y+1);
    if (y-1 < 0 && !v[x][y-1] && image[x][y-1]) tam += DFS(v, image, x, y-1);
    
    
    return tam+1;
}

int maior(int image[N][N]) {
    int tam = 0, v[N][N] = {0}, x, y;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (image[i][j] && !v[i][j])
            {
                tam = max(DFS(v, image, i, j), tam);
            }
        }
    }
    return tam;
}



int main() {

>>>>>>> d2291afde4f92f0d872f7010f724006e510c552c
}