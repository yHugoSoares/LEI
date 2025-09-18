// #include "T1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int f (int v[], int N) {
    int i, r = v[0];
    for (i = 1; i < N; i++)
    if (r < v[i]) r = v[i];
    return r;
}

int main() {
    int v[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    int N = sizeof(v) / sizeof(v[0]);
    int result = f(v, N);
    printf("Maximum value in the array: %d\n", result);
    return 0;
}
