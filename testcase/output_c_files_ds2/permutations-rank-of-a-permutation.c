void get_permutation(int rank, int n, int *vec) {
    int i;
    int t;
    int q;
    int r;
    for (i = 0; i < n; i = i + 1) {
        vec[i] = i;
    }
    if (n < 1) {
        return;
    }
    q = rank / n;
    r = rank % n;
    t = vec[r];
    vec[r] = vec[n - 1];
    vec[n - 1] = t;
    get_permutation(q, n - 1, vec);
    return;
}

int get_rank(int n, int *vec) {
    int i;
    int r;
    int s;
    int t;
    int v[5];
    int inv[5];
    for (i = 0; i < n; i = i + 1) {
        v[i] = vec[i];
        inv[vec[i]] = i;
    }
    if (n < 2) {
        return 0;
    }
    s = v[n - 1];
    t = v[n - 1];
    v[n - 1] = v[inv[n - 1]];
    v[inv[n - 1]] = t;
    t = inv[s];
    inv[s] = inv[n - 1];
    inv[n - 1] = t;
    r = s + n * get_rank(n - 1, v);
    return r;
}
