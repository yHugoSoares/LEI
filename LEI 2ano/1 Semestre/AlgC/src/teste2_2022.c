#include <stdio.h>
#include <stdlib.h>

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

}