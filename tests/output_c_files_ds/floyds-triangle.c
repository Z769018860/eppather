void t(int n) {
    int i;
    int j;
    int c;
    int len;
    int num;
    int k;
    int tmp[32];
    int s[4096];
    int p;
    int col;
    
    i = n * (n - 1) / 2;
    len = 1;
    c = 1;
    for (; c < i; ) {
        c = c * 10;
        len = len + 1;
    }
    c = c - i;
    
    for (k = 0; k < 32; k = k + 1) {
        tmp[k] = 0;
    }
    
    p = 0;
    num = 1;
    for (i = 1; i <= n; i = i + 1) {
        for (j = 1; j <= i; j = j + 1) {
            col = len - (j < c);
            k = len;
            while (1) {
                if (k <= 0) {
                    break;
                }
                k = k - 1;
                if (tmp[k] == 9) {
                    tmp[k] = 0;
                    continue;
                }
                tmp[k] = tmp[k] + 1;
                if (tmp[k] == 33) {
                    tmp[k] = 1;
                }
                break;
            }
            
            for (k = 1 - (j >= c); k < len - (j < c); k = k + 1) {
                s[p] = tmp[k];
                p = p + 1;
            }
            
            if (i - j) {
                s[p] = 32;
            } else {
                s[p] = 10;
            }
            p = p + 1;
            
            if (p + len >= 4096) {
                p = 0;
            }
            num = num + 1;
        }
    }
    return;
}
