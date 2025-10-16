int f(int n, int x, int y) {
    return (x + y * 2 + 1) % n;
}

void magic_square(int n, int result[5][5]) {
    int i;
    int j;
    int n1;
    n1 = n;
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            if (i < n1 && j < n1) {
                result[i][j] = f(n1, n1 - j - 1, i) * n1 + f(n1, j, i) + 1;
            } else {
                result[i][j] = 0;
            }
        }
    }
    return;
}
