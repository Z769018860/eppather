void comb(int m, int n, unsigned char *c) {
    int i;
    int j;
    for (i = 0; i < n; i = i + 1) {
        c[i] = n - i;
    }
    
    while (1) {
        for (i = n - 1; i >= 0; i = i - 1) {
            int temp;
            temp = c[i];
        }
        
        i = 0;
        if (c[i] < m) {
            c[i] = c[i] + 1;
            continue;
        }
        
        for (; c[i] >= m - i; ) {
            i = i + 1;
            if (i >= n) {
                return;
            }
        }
        
        c[i] = c[i] + 1;
        for (j = i; j > 0; j = j - 1) {
            c[j - 1] = c[j] + 1;
        }
    }
    return;
}
