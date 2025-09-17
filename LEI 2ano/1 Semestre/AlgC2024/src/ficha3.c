#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int max(int a, int b) {
    return (a > b) ? a : b;
}

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

int removeHeaps (PriorityQueue *q, int *rem) {
    if (q->tamanho == 0) return 0;
    *rem = q->valores[0];
    q->valores[0] = q->valores[q->tamanho - 1];
    q->tamanho--;
    bubbleDown(0, q->valores, q->tamanho);
    return 1;
}

void heapifyUp (int v[], int N) {
    // with bubbleUp
    for (int i = 1; i < N; i++) {
        bubbleUp(i, v);
    }
} // Complexidade N * log(N)

void heapifyDown (int v[], int N) {
    // with bubbleDown
    for (int i = N - 1; i >= 0; i--) {
        bubbleDown(i, v, N);
    }
} // Complexidade N

#define NE -1

int alturaAux (int a[], int N, int i) {
    if (i >= N || a[i] == NE) return 0;
    int left = 2 * i + 1, right = 2 * i + 2;
    
    
    return 1 + max(alturaAux(a, N, left), alturaAux(a, N, right));
}

int altura (int a[], int N) {
    return alturaAux(a, N, 0);
}


#define Size 10
typedef struct nodo {
    char *chave;
    int ocorr;
    struct nodo *prox;
} Nodo, *THash [Size];

unsigned hash(char *str){
    unsigned hash = 5381;
    int c;
    while (c = *str++) hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

void initEmpty (THash t) {
    for (int i = 0; i < Size; i++) {
        t[i] = NULL;
    }
}

void addHash (char *s, THash t) {
    int h = hash(s);
    int pos = h % Size;

    Nodo *n = t[pos];
    while (n != NULL) {
        if (strcmp(n->chave, s) == 0) {
            n->ocorr++;
            return;   
        }
        n = n->prox;
    }
}

int lookupHash (char *s, THash t) {
    int h = hash(s);
    int pos = h % Size;
    if (t[pos]->chave == s) return t[pos]->ocorr;
    return 0;
}

int removeHash (char *s, THash t) {
    int h = hash(s);
    int pos = h % Size;
    if (t[pos]->chave == s) t[pos]->ocorr--;
    return 1;
}

int main() {

}