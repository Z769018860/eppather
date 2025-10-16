void count(int sum, int coins[7], unsigned long long result[2]) {
    int n;
    for (n = 0; coins[n] != 0; n = n + 1) {}
    
    int v0[100][100];
    int v1[100][100];
    int idx[100];
    
    for (int i = 0; i < n; i = i + 1) {
        idx[i] = coins[i];
        for (int j = 0; j < coins[i]; j = j + 1) {
            v0[i][j] = 0;
            v1[i][j] = 0;
        }
    }
    
    v0[0][coins[0] - 1] = 1;
    v1[0][coins[0] - 1] = 0;
    
    for (int k = 0; k <= sum; k = k + 1) {
        for (int i = 0; i < n; i = i + 1) {
            if (idx[i] == 0) {
                idx[i] = coins[i] - 1;
            } else {
                idx[i] = idx[i] - 1;
            }
        }
        
        unsigned long long c0 = v0[0][idx[0]];
        unsigned long long c1 = v1[0][idx[0]];
        
        for (int i = 1; i < n; i = i + 1) {
            int pos = idx[i];
            unsigned long long p0 = v0[i][pos];
            unsigned long long p1 = v1[i][pos];
            
            p0 = p0 + c0;
            p1 = p1 + c1;
            if (p0 < c0) {
                p1 = p1 + 1;
            }
            
            v0[i][pos] = p0;
            v1[i][pos] = p1;
            c0 = p0;
            c1 = p1;
        }
    }
    
    result[0] = v0[n - 1][idx[n - 1]];
    result[1] = v1[n - 1][idx[n - 1]];
    return;
}
