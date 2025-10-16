void bernoulli(int rop_num, int rop_den, int n) {
    int a_num[100];
    int a_den[100];
    int m;
    int j;
    int temp_num;
    int temp_den;
    int gcd;
    
    for (m = 0; m <= n; m = m + 1) {
        a_num[m] = 1;
        a_den[m] = m + 1;
        for (j = m; j > 0; j = j - 1) {
            temp_num = a_num[j] * a_den[j - 1] - a_num[j - 1] * a_den[j];
            temp_den = a_den[j] * a_den[j - 1];
            a_num[j - 1] = temp_num;
            a_den[j - 1] = temp_den;
            
            temp_num = a_num[j - 1] * j;
            temp_den = a_den[j - 1];
            a_num[j - 1] = temp_num;
            a_den[j - 1] = temp_den;
            
            gcd = 1;
            for (int k = 2; k <= a_num[j - 1] && k <= a_den[j - 1]; k = k + 1) {
                if (a_num[j - 1] % k == 0 && a_den[j - 1] % k == 0) {
                    gcd = k;
                }
            }
            a_num[j - 1] = a_num[j - 1] / gcd;
            a_den[j - 1] = a_den[j - 1] / gcd;
        }
    }
    
    rop_num = a_num[0];
    rop_den = a_den[0];
    return;
}
