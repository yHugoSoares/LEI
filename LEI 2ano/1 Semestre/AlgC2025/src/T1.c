#include "T1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int f (int v[], int N) {
  int i, r = 0;
  for (i = 0; i < N; i++)
    if (r > v[i]) r = v[i];
  return r;
}