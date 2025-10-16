void lis(int *v, int len) {
    int i;
    int j;
    int n_val[5];
    int n_len[5];
    int n_next[5];
    int p;
    int max_len;
    int max_idx;
    
    for (i = 0; i < 5; i = i + 1) {
        n_val[i] = v[i];
        n_len[i] = 0;
        n_next[i] = -1;
    }

    for (i = 4; i >= 0; i = i - 1) {
        for (j = i + 1; j < 5; j = j + 1) {
            if (n_val[j] > n_val[i] && n_len[j] >= n_len[i]) {
                n_next[i] = j;
                n_len[i] = n_len[j] + 1;
            }
        }
    }

    max_len = n_len[0];
    max_idx = 0;
    for (i = 1; i < 5; i = i + 1) {
        if (n_len[i] > max_len) {
            max_len = n_len[i];
            max_idx = i;
        }
    }

    p = max_idx;
    while (p != -1) {
        p = n_next[p];
    }
    
    return;
}
