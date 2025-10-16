int func() {
    int N = 15;
    int k;
    int n;
    unsigned long long int num;
    unsigned long long int den;
    int catalan;
    int result[15];
    result[0] = 1;
    
    for (n = 2; n <= N; n = n + 1) {
        num = 1;
        den = 1;
        for (k = 2; k <= n; k = k + 1) {
            num = num * (n + k);
            den = den * k;
            catalan = num / den;
        }
        result[n - 1] = catalan;
    }
    
    return;
}
