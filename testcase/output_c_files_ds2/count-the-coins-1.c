void count(int sum, int coins[5], int result[2]) {
    int n;
    for (n = 0; n < 5; n = n + 1) {
        if (coins[n] == 0) {
            break;
        }
    }

    int v[5][5][2];
    int idx[5];
    int i;
    int k;

    for (i = 0; i < n; i = i + 1) {
        idx[i] = coins[i];
        for (k = 0; k < 5; k = k + 1) {
            v[i][k][0] = 0;
            v[i][k][1] = 0;
        }
    }

    v[0][coins[0] - 1][0] = 1;
    v[0][coins[0] - 1][1] = 0;

    for (k = 0; k <= sum; k = k + 1) {
        for (i = 0; i < n; i = i + 1) {
            if (idx[i] == 0) {
                idx[i] = coins[i] - 1;
            } else {
                idx[i] = idx[i] - 1;
            }
        }

        int c0 = v[0][idx[0]][0];
        int c1 = v[0][idx[0]][1];

        for (i = 1; i < n; i = i + 1) {
            int p0 = v[i][idx[i]][0];
            int p1 = v[i][idx[i]][1];

            v[i][idx[i]][0] = p0 + c0;
            v[i][idx[i]][1] = p1 + c1;
            if (v[i][idx[i]][0] < c0) {
                v[i][idx[i]][1] = v[i][idx[i]][1] + 1;
            }
            c0 = v[i][idx[i]][0];
            c1 = v[i][idx[i]][1];
        }
    }

    result[0] = v[n - 1][idx[n - 1]][0];
    result[1] = v[n - 1][idx[n - 1]][1];
    return;
}
