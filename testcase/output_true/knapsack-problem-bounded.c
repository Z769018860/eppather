int* knapsack(int w) {
    int n = 22;
    int weights[22] = {9, 13, 153, 50, 15, 68, 27, 39, 23, 52, 11, 32, 24, 48, 73, 42, 43, 22, 7, 18, 4, 30};
    int values[22] = {150, 35, 200, 60, 60, 45, 60, 40, 30, 10, 70, 30, 15, 10, 40, 70, 75, 80, 20, 12, 50, 10};
    int counts[22] = {1, 1, 2, 2, 2, 3, 3, 3, 1, 3, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 1, 2};
    
    int mm[25346];
    int m[23][1156];
    int s[22];
    int i;
    int j;
    int k;
    int v;
    
    for (i = 0; i < 25346; i = i + 1) {
        mm[i] = 0;
    }
    
    for (i = 0; i < 23; i = i + 1) {
        for (j = 0; j < 1156; j = j + 1) {
            m[i][j] = 0;
        }
    }
    
    for (i = 1; i <= n; i = i + 1) {
        for (j = 0; j <= w; j = j + 1) {
            m[i][j] = m[i - 1][j];
            for (k = 1; k <= counts[i - 1]; k = k + 1) {
                if (k * weights[i - 1] > j) {
                    break;
                }
                v = m[i - 1][j - k * weights[i - 1]] + k * values[i - 1];
                if (v > m[i][j]) {
                    m[i][j] = v;
                }
            }
        }
    }
    
    for (i = 0; i < 22; i = i + 1) {
        s[i] = 0;
    }
    
    j = w;
    for (i = n; i > 0; i = i - 1) {
        v = m[i][j];
        for (k = 0; v != m[i - 1][j] + k * values[i - 1]; k = k + 1) {
            s[i - 1] = s[i - 1] + 1;
            j = j - weights[i - 1];
        }
    }
    
    return s;
}
