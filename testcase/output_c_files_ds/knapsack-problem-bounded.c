int knapsack(int w) {
    int item_weights[22] = {9,13,153,50,15,68,27,39,23,52,11,32,24,48,73,42,43,22,7,18,4,30};
    int item_values[22] = {150,35,200,60,60,45,60,40,30,10,70,30,15,10,40,70,75,80,20,12,50,10};
    int item_counts[22] = {1,1,2,2,2,3,3,3,1,3,1,1,2,2,1,1,1,1,1,2,1,2};
    int n = 22;
    int mm[23][401];
    int m[23][401];
    int s[22];
    int i;
    int j;
    int k;
    int v;
    
    for (i = 0; i <= n; i = i + 1) {
        for (j = 0; j <= w; j = j + 1) {
            mm[i][j] = 0;
        }
    }
    
    for (i = 0; i <= n; i = i + 1) {
        for (j = 0; j <= w; j = j + 1) {
            m[i][j] = mm[i][j];
        }
    }
    
    for (i = 1; i <= n; i = i + 1) {
        for (j = 0; j <= w; j = j + 1) {
            m[i][j] = m[i - 1][j];
            for (k = 1; k <= item_counts[i - 1]; k = k + 1) {
                if (k * item_weights[i - 1] > j) {
                    break;
                }
                v = m[i - 1][j - k * item_weights[i - 1]] + k * item_values[i - 1];
                if (v > m[i][j]) {
                    m[i][j] = v;
                }
            }
        }
    }
    
    for (i = 0; i < n; i = i + 1) {
        s[i] = 0;
    }
    
    i = n;
    j = w;
    while (i > 0) {
        v = m[i][j];
        k = 0;
        while (v != m[i - 1][j] + k * item_values[i - 1]) {
            s[i - 1] = s[i - 1] + 1;
            j = j - item_weights[i - 1];
            k = k + 1;
        }
        i = i - 1;
    }
    
    return;
}
