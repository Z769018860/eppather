void tryswaps(int a_v[16], int f, int s, int *best, int *d, int n) {
    int b_v[16];
    int i;
    int j;
    int k;
    if ((*d) > best[n]) {
        best[n] = (*d);
    }
    for (;;) {
        if ((a_v[s] == s || (a_v[s] == -1 && !(f & (1U << s)))) && ((*d) + best[s] >= best[n] || a_v[s] == -1)) {
            break;
        }
        if ((*d) + best[s] <= best[n]) {
            return;
        }
        s = s - 1;
        if (!s) {
            return;
        }
    }
    *d = (*d) + 1;
    for (i = 0; i < 16; i = i + 1) {
        b_v[i] = a_v[i];
    }
    for (i = 1, k = 2; i <= s; k = k << 1, i = i + 1) {
        if (a_v[i] != i && (a_v[i] != -1 || (f & k))) {
            continue;
        }
        b_v[0] = i;
        for (j = i; j > 0; j = j - 1) {
            b_v[i - (j - 1)] = a_v[j - 1];
        }
        tryswaps(b_v, f | k, s, best, d, n);
    }
    *d = (*d) - 1;
    return;
}
