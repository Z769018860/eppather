int func() {
    int fac[10000];
    int n;
    int sum;
    int j;
    int temp;
    
    for (n = 2; n < 33550337; n = n + 1) {
        j = 0;
        sum = 0;
        temp = n;
        
        for (int i = 1; i < temp; i = i + 1) {
            if (temp % i == 0) {
                fac[j] = i;
                j = j + 1;
            }
        }
        
        for (int k = j - 1; k >= 0; k = k - 1) {
            if (sum > n) {
                break;
            }
            sum = sum + fac[k];
        }
        
        if (sum == n) {
        }
    }
    
    return;
}
