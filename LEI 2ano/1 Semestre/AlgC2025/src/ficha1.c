int prod (int x, int y) {
    // pre: TRUE
    // pos: r == x * y
    return x * y;
}

int mdc1 (int x, int y) {
    // pre : x > 0 && y > 0
    int r1, r2, n;
    if (x < y) n = x;
    else n = y;
    while (r1 != 0 && r2 != 0) {
        r1 = x % n;
        r2 = y % n;
        n--;
    }
    // pos: x % r == 0 && y % r == 0 && for_all i (i > r => x % i != 0 || y % i != 0)
    return n + 1;
}

int mdc2 (int x, int y) {
    while (y != 0) {
        int r = x % y;
        x = y;
        y = r;
    }
    return x;
}

int sum (int v[], int N) {
    // pre: N >= 0
    int s = 0;
    for (int i = 0; i < N; i++)
    {
        s += v[i];
    }
    // pos: for_all i (0 <= i < N => s += v[i])
    return s;
}

int maxPOrd (int v[], int N) {
    // pre: N >= 0
    int temp = 0, r = 0;
    for (int i = 0; i < N-1; i++)
    {
        if (v[i] > v[i+1]) temp++;
        else temp = 0;
        if (temp > r) r = temp;
    }
    // pos: for_all i (0 <= i < r-1 => v[i] < v[i+1]) && 0 <= r <= N && r < N => v[r-1] >= v[r]
    return r;
}

int isSorted (int v[], int N) {
    // pre: N >= 0
    for (int i = 0; i < N-1; i++)
    {
        if (v[i] > v[i+1]) return 0;
    }
    // pos: for_all i (0 <= i < N-1 => v[i] <= v[i+1]) => r == 1 && exists i (0 <= i < N-1 && v[i] > v[i+1]) => r == 0
    return 1;
}


