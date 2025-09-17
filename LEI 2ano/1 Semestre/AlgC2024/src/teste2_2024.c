#include <stdio.h>
#include <stdlib.h>

#define H 20000

int checkBSTAux(int t[], int N, int counter) {
    if (counter >= N) return 1;
    
    int esq = counter*2+1, dir = counter*2+2;
    
    if ((esq == H && t[dir] > t[counter]) || (t[esq] < t[counter] && dir == H)) return 1;
    if (esq > N || (esq == H && dir == H)) return 1;
    if (!(t[counter] >= t[esq] && t[counter] <= t[dir])) return 0;

    checkBSTAux(t, N, esq);
    checkBSTAux(t, N, dir);
    return 1;
}

int checkBST (int t[], int N) {
    int r = checkBSTAux(t, N, 0);

    return r;
}

int altura (int t[], int N, int i) {
    int left = 2*i+1, right = 2*i+2;

    if (i >= N || t[i] == H) return 0;
    return 1 + max(altura(t, N, left), altura(t, N, right));
}

int checkAVLAux (int t[], int N, int i) {
    int left = 2*i+1, right = 2*i+2;
    if (i >= N || t[i] == H) return 1;
    if (abs(altura(t, N, left) - altura(t, N, right)) <= 1) return min(checkAVLAux(t, N, left), checkAVLAux(t, N, right));
    return 0;
}

int checkAVL (int t[], int N) {
    if (checkAVLAux(t, N, 0)) return checkBST(t, N);

    return 0;
}

#define MAX 10

typedef struct edge {
    int dest;
    struct edge *next;
} *Edge, *GrafoL[MAX];

int is_clique (GrafoL g, int NV, int v[], int k) {
    int r = 0;
    for (int i = 0; i < k; i++)
    {
        Edge x = g[v[i]];
        for (int j = 0; j < k; j++)
        {
            if (x->dest == v[j]){
                r++;
                x = x->next;
            }
        }
    }
    return r == (k * (k-1));
} // Tempo de Execucao (k - 1) * k