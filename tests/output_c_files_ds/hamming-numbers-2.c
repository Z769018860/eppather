int get_ham(int n, int *result) {
    int NK = 3;
    int MAX_HAM = 16777216;
    int MAX_POW = 1024;
    int n_hams = 0;
    int idx[3] = {0, 0, 0};
    int fac[3] = {2, 3, 5};
    int hams[16777216][4];
    int values[3][4];
    double inc[3][1024];
    int i;
    int j;
    int ni;
    int h;
    int tmp;

    for (i = 0; i < NK; i = i + 1) {
        for (j = 0; j < 4; j = j + 1) {
            values[i][j] = 0;
        }
        values[i][i] = 1;
        inc[i][1] = 0;
        for (j = 2; j < MAX_POW; j = j + 1) {
            inc[i][j] = 0;
        }
    }

    n = n - 1;
    while (n_hams < n) {
        ni = 0;
        for (i = 1; i < NK; i = i + 1) {
            if (values[i][3] < values[ni][3]) {
                ni = i;
            }
        }

        for (i = 0; i < 4; i = i + 1) {
            hams[n_hams + 1][i] = values[ni][i];
        }
        n_hams = n_hams + 1;
        h = n_hams;

        for (ni = 0; ni < NK; ni = ni + 1) {
            tmp = 1;
            for (i = 0; i < NK; i = i + 1) {
                if (hams[h][i] != values[ni][i]) {
                    tmp = 0;
                    break;
                }
            }
            if (tmp == 0) {
                continue;
            }
            for (i = 0; i < 4; i = i + 1) {
                values[ni][i] = hams[idx[ni] + 1][i];
            }
            idx[ni] = idx[ni] + 1;
            values[ni][ni] = values[ni][ni] + 1;
            values[ni][3] = 0;
            for (i = 0; i < NK; i = i + 1) {
                values[ni][3] = values[ni][3] + inc[i][values[ni][i]];
            }
        }
    }

    for (i = 0; i < 3; i = i + 1) {
        result[i] = hams[n][i];
    }
    return;
}
