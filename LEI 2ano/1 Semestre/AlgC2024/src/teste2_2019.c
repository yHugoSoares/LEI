#include <stdio.h>
#include <stdlib.h>

void bubbleUp(int i, int h[]) {
    int p = (i - 1) / 2;
    while (i > 0 && h[i] > h[p]) {
        int t = h[i];
        h[i] = h[p];
        h[p] = t;
        i = p;
        p = (i - 1) / 2;
    }
}

// Função para empurrar o elemento na posição i para baixo na min-heap
void bubbleDown(int i, int h[], int N) {
    int smallest = i; // Índice do menor valor (inicia como o próprio i)
    int left = 2 * i + 1; // Índice do filho esquerdo
    int right = 2 * i + 2; // Índice do filho direito

    // Verifica se o filho esquerdo existe e é menor que o elemento atual
    if (left < N && h[left] < h[smallest]) {
        smallest = left;
    }

    // Verifica se o filho direito existe e é menor que o menor encontrado até agora
    if (right < N && h[right] < h[smallest]) {
        smallest = right;
    }

    // Se o menor valor não estiver em i, troca os elementos e continua
    if (smallest != i) {
        int temp = h[i];
        h[i] = h[smallest];
        h[smallest] = temp;

        // Chama recursivamente para garantir que a propriedade seja satisfeita
        bubbleDown(smallest, h, N);
    }
}

void ordenar (int v[], int N) {
    for (int i = N - 1; i >= 0; i--)
    {
        bubbleUp(i, v);
    }
}

int kmaior (int v[], int N, int k) {
    ordenar(v, N);
    return v[k];
}

#define HSize 17

int hash (int x) {
    return x % HSize;
}

#define N 6
typedef struct edge {
    int dest;
    int cost;
    struct edge *next;
} *Edge, *GraphL[N];


typedef int GMat [N][N];

GMat g1 =
    // 0 1 2 3 4 5
   {{-1, 6, 7,-1, 3,-1}, // 0
    { 6,-1,-1, 5, 4, 2}, // 1
    { 7,-1,-1,-1, 8,-1}, // 2
    {-1, 5,-1,-1,-1, 2}, // 3
    { 3, 4, 8,-1,-1, 3}, // 4
    {-1, 2,-1, 2, 3,-1}};// 5

int simplePath (GraphL g, int v[], int k) {
    Edge x = g[v[0]];
    int counter = 1;

    while (x != NULL)
    {
        if (x->dest != v[counter])
        {
            return 0;
        }
        counter++;
    }
    return 1;
}

int main () {
    
}