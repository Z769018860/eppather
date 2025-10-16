void t(int n) {
    int i[5];
    int j[5];
    int c[5];
    int len[5];
    int num[5];
    
    i[0] = n * (n - 1) / 2;
    for (len[0] = 1, c[0] = 1; c[0] < i[0]; c[0] = c[0] * 10, len[0] = len[0] + 1) {
    }
    c[0] = c[0] - i[0];
    
    for (num[0] = 1, i[0] = 1; i[0] <= n; i[0] = i[0] + 1) {
        for (j[0] = 1; j[0] <= i[0]; j[0] = j[0] + 1) {
            num[0] = num[0] + 1;
        }
    }
    
    return;
}
