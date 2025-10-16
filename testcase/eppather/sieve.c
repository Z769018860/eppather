void sieveOfEratosthenes(int n) {
    int prime[n];
    int i,p;
    
    for (i = 0; i < n; i = i + 1) {
        prime[i] = 1;
    }
    prime[0] = prime[1] = 0;

    for (p = 2; p * p <= n; p = p + 1) {
        if (prime[p] == 1) {
            for (i = p * p; i <= n; i = i + p) {
                prime[i] = 0;
            }
            ;
        }
        ;
    }
    return;
}
