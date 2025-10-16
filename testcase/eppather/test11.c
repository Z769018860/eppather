void change(int g[5][5], int m, int n, int a, int b, int s) {
    int i, j, k = 0;

    g[a][b] = s;
    if (a - 1 >= 0) {
        g[a - 1][b] = s;
        if (b - 1 >= 0)
            g[a - 1][b - 1] = s;
        ;
    }
    if (b - 1 >= 0)
        g[a][b - 1] = s;
    if (a + 1 < m) {
        g[a + 1][b] = s;
        if (b + 1 < n)
            g[a + 1][b + 1] = s;
        ;
    }
    if (b + 1 < n)
        g[a][b + 1] = s;

    for (i = 0; i < m; i = i + 1) {
        for (j = 0; j < n; j = j + 1) {
            k = k + 1;
        }
        k = k + 2;
    }

    return;
}
