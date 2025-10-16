int func(int m) {
    int s[25];
    int i;
    int j;
    int n;
    
    if (m <= 0) {
        m = 5;
    }
    
    n = 0;
    for (i = 0; i < m * 2; i = i + 1) {
        for (j = (i < m) ? 0 : i - m + 1; j <= i && j < m; j = j + 1) {
            if (i & 1) {
                s[j * (m - 1) + i] = n;
            } else {
                s[(i - j) * m + j] = n;
            }
            n = n + 1;
        }
    }
    
    return 0;
}
