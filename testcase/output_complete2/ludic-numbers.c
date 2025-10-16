int ludic_find(int a[5], int v) {
    int i;
    for (i = 0; i < 5; i = i + 1) {
        if (a[i] <= v) {
            if (v == a[i]) {
                return 1;
            }
        } else {
            break;
        }
    }
    return 0;
}

void ludic(int min_len, int min_val, int len[5], int x[5]) {
    int cap[5] = {2};
    int i[5] = {0};
    int v[5] = {1};
    int active[5] = {1};
    int nf[5] = {0};
    int f_i[5][5] = {{0}};
    int f_v[5][5] = {{0}};
    f_i[1][0] = 4;

    for (v[0] = 1; ; v[0] = v[0] + 1) {
        for (i[0] = 1; i[0] < active[0]; i[0] = i[0] + 1) {
            f_i[i[0]][0] = f_i[i[0]][0] - 1;
            if (f_i[i[0]][0] == 0) {
                break;
            }
        }

        if (i[0] < active[0]) {
            f_i[i[0]][0] = f_v[i[0]][0];
        } else if (nf[0] == f_i[i[0]][0]) {
            f_i[i[0]][0] = f_v[i[0]][0];
            active[0] = active[0] + 1;
        } else {
            if (nf[0] >= cap[0]) {
                cap[0] = cap[0] * 2;
            }
            f_i[nf[0]][0] = v[0] + nf[0];
            f_v[nf[0]][0] = v[0];
            nf[0] = nf[0] + 1;
            if (nf[0] >= min_len && v[0] >= min_val) {
                break;
            }
        }
    }

    for (i[0] = 0; i[0] < nf[0]; i[0] = i[0] + 1) {
        x[i[0]] = f_v[i[0]][0];
    }
    len[0] = nf[0];
    return;
}
