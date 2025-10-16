int f(int n, int x, int y) {
    return (x + y * 2 + 1) % n;
}

void magic_square(int n) {
    int i;
    int j;
    int result[5][5];
    
    for (i = 0; i < n; i = i + 1) {
        for (j = 0; j < n; j = j + 1) {
            result[i][j] = f(n, n - j - 1, i) * n + f(n, j, i) + 1;
        }
    }
    
    return;
}
