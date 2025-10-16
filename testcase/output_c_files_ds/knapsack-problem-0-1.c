void knapsack(int items_weight[22], int items_value[22], int n, int w, int s[22]) {
    int i;
    int j;
    int a;
    int b;
    int mm[23][401];
    int m[23][401];
    
    for (i = 0; i < 23; i = i + 1) {
        for (j = 0; j < 401; j = j + 1) {
            mm[i][j] = 0;
            m[i][j] = 0;
        }
    }
    
    for (i = 1; i <= n; i = i + 1) {
        for (j = 0; j <= w; j = j + 1) {
            if (items_weight[i - 1] > j) {
                m[i][j] = m[i - 1][j];
            } else {
                a = m[i - 1][j];
                b = m[i - 1][j - items_weight[i - 1]] + items_value[i - 1];
                if (a > b) {
                    m[i][j] = a;
                } else {
                    m[i][j] = b;
                }
            }
        }
    }
    
    for (i = 0; i < 22; i = i + 1) {
        s[i] = 0;
    }
    
    i = n;
    j = w;
    for (i = n; i > 0; i = i - 1) {
        if (m[i][j] > m[i - 1][j]) {
            s[i - 1] = 1;
            j = j - items_weight[i - 1];
        }
    }
    
    return;
}
