int perm_comb(int out[], int n, int k, int is_comb) {
    int i;
    int j;
    int temp;
    out[0] = 1;
    k = n - k;
    
    for (i = n; i > k; i = i - 1) {
        temp = out[0];
        out[0] = 0;
        for (j = 0; j < temp; j = j + 1) {
            out[0] = out[0] + i;
        }
    }
    
    if (is_comb) {
        for (i = k; i > 0; i = i - 1) {
            temp = out[0];
            out[0] = 0;
            for (j = 0; j < temp; j = j + 1) {
                out[0] = out[0] + 1;
            }
        }
    }
    
    return;
}
