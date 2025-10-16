int comb_perm(int out[5], int n, int k) {
    int temp[5];
    temp[0] = 1;
    k = n - k;
    for (int i = 0; i < 5; i = i + 1) {
        if (n > k) {
            temp[0] = temp[0] * n;
            n = n - 1;
        }
    }
    out[0] = temp[0];
    for (int i = 0; i < 5; i = i + 1) {
        if (k > 0) {
            out[0] = out[0] / k;
            k = k - 1;
        }
    }
    return;
}
