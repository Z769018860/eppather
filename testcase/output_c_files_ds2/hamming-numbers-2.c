int get_ham(int n, int fac0, int fac1, int fac2, int max_ham, int max_pow) {
    int hams_e[5][3] = {0};
    double hams_v[5] = {0};
    int idx[3] = {0};
    int n_hams = 0;
    int values_e[3][3] = {0};
    double values_v[3] = {0};
    double inc[3][1024] = {0};
    int i;
    int j;
    int ni;
    int h;

    for (i = 0; i < 3; i = i + 1) {
        values_e[i][i] = 1;
        inc[i][1] = 0;
        values_v[i] = 0;
        for (j = 2; j < 1024; j = j + 1) {
            inc[i][j] = 0;
        }
    }

    n = n - 1;
    while (n_hams < n) {
        for (ni = 0, i = 1; i < 3; i = i + 1) {
            if (values_v[i] < values_v[ni]) {
                ni = i;
            }
        }

        for (i = 0; i < 3; i = i + 1) {
            hams_e[n_hams + 1][i] = values_e[ni][i];
        }
        hams_v[n_hams + 1] = values_v[ni];
        n_hams = n_hams + 1;
        h = n_hams;

        for (ni = 0; ni < 3; ni = ni + 1) {
            int eq = 1;
            for (i = 0; i < 3; i = i + 1) {
                if (values_e[ni][i] != hams_e[h][i]) {
                    eq = 0;
                    break;
                }
            }
            if (!eq) {
                continue;
            }
            for (i = 0; i < 3; i = i + 1) {
                values_e[ni][i] = hams_e[idx[ni] + 1][i];
            }
            idx[ni] = idx[ni] + 1;
            values_e[ni][ni] = values_e[ni][ni] + 1;
            values_v[ni] = 0;
            for (i = 0; i < 3; i = i + 1) {
                values_v[ni] = values_v[ni] + inc[i][values_e[ni][i]];
            }
        }
    }

    return 0;
}
