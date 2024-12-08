#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int h[] = {10, 15, 11, 16, 22, 35, 20, 21, 23, 34, 37, 80, 43, 22, 25, 24, 28}; 
// 1. Analisando o exemplo acima, determine express ̃oes gerais que permitam calcular:
// (a) O  ́ındice onde se encontra a sub- ́arvore esquerda do nodo da posi ̧c ̃ao i.
// (b) O  ́ındice onde se encontra a sub- ́arvore direita do nodo da posi ̧c ̃ao i.
// (c) O  ́ındice onde se encontra o pai do nodo da posi ̧c ̃ao i.
// (d) O  ́ındice onde se encontra a primeira folha, i.e., o primeiro nodo que n ̃ao tem
// sucessores.

// (a) (i * 2) + 1
// (b) (i * 2) + 2
// (c) (i - 1) / 2
// (d) n / 2

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

#define Max 100
typedef struct pQueue {
int valores [Max];
int tamanho;
} PriorityQueue;

void empty(PriorityQueue *q) {
    while (q->tamanho > 0) {
        q->tamanho--;
        q->valores[q->tamanho] = 0;
    }
}

int isEmpty (PriorityQueue *q){
    return q->tamanho == 0;
}

int add (int x, PriorityQueue *q) {
    if (q->tamanho == Max) return 0;
    q->valores[q->tamanho] = x;
    bubbleUp(q->tamanho, q->valores);
    q->tamanho++;
    return 1;
}

int remove (PriorityQueue *q, int *rem) {
    if (q->tamanho == 0) return 0;
    *rem = q->valores[0];
    q->valores[0] = q->valores[q->tamanho - 1];
    q->tamanho--;
    bubbleDown(0, q->valores, q->tamanho);
    return 1;
}

void heapifyUp (int v[], int N) {
    // with bubbleUp
    for (int i = 0; i < N; i++) {
        bubbleUp(i, v);
    }
}

void heapifyDown (int v[], int N) {
    // with bubbleDown
    for (int i = N - 1; i >= 0; i--) {
        bubbleDown(i, v, N);
    }
}


int main() {

}