void catalan_numbers(int n1) {
    int k[5];
    int n[5];
    unsigned long long int num[5];
    unsigned long long int den[5];
    int catalan[5];
    
    for (n[0] = 2; n[0] <= n1; n[0] = n[0] + 1) {
        num[0] = 1;
        den[0] = 1;
        for (k[0] = 2; k[0] <= n[0]; k[0] = k[0] + 1) {
            num[0] = num[0] * (n[0] + k[0]);
            den[0] = den[0] * k[0];
            catalan[0] = num[0] / den[0];
        }
    }
    return;
}
