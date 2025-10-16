void powerset(int v[5][5], int n, int up[5][5]) {
    int me[5][5];
    int i;
    int j;

    if (n == 0) {
        for (i = 0; i < 5; i = i + 1) {
            for (j = 0; j < 5; j = j + 1) {
                if (up[i][j] != 0) {
                    for (j = 0; j < 5; j = j + 1) {
                        me[0][j] = up[i][j];
                    }
                }
            }
        }
    } else {
        for (i = 0; i < 5; i = i + 1) {
            me[0][i] = v[0][i];
        }
        for (i = 0; i < 5; i = i + 1) {
            me[1][i] = up[0][i];
        }
        for (i = 0; i < 5; i = i + 1) {
            powerset(v + 1, n - 1, up);
        }
        for (i = 0; i < 5; i = i + 1) {
            powerset(v + 1, n - 1, me);
        }
    }
    return;
}
