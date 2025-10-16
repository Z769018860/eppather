void sieve(int n) {
    int a[11];
    int i;
    int j;
    
    for (i = 0; i < 11; i = i + 1) {
        a[i] = 1;
    }
    
    for (i = 2; i < 11; i = i + 1) {
        if (a[i] == 1) {
            for (j = 2; j < 6; j = j + 1) {
                if (i * j < 11) {
                    a[i * j] = 0;
                }
            }
        }
    }
    
    return;
}
