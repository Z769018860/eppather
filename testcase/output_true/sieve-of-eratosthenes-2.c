void sieve(int *a, int n) {
    int i;
    int j;
    
    for (i = 2; i <= n; i = i + 1) {
        a[i] = 1;
    }
    
    for (i = 2; i <= n; i = i + 1) {
        if (a[i] == 1) {
            for (j = i; (i * j) <= n; j = j + 1) {
                a[(i * j)] = 0;
            }
        }
    }
    
    return;
}
