void comb(int m, int n, unsigned char* c) {
    int i;
    int j;
    int k;
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

        for (j = 0; j < n; j = j + 1) {
            if (c[j] >= m - j) {
                j = j + 1;
                if (j >= n) {
                    return;
                }
            } else {
                break;
            }
        }

        for (k = j; k > 0; k = k - 1) {
            c[k - 1] = c[k] + 1;
        }
        c[j] = c[j] + 1;
    }
    return;
}
