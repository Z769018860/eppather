int* knapsack(int* items_weight, int* items_value, int n, int w) {
    int mm[6][401];
    int m[6][401];
    int s[5];
    int i;
    int j;
    int a;
    int b;
    
    for (i = 0; i < 6; i = i + 1) {
        for (j = 0; j < 401; j = j + 1) {
            mm[i][j] = 0;
        }
    }
    
    for (i = 0; i < 6; i = i + 1) {
        for (j = 0; j < 401; j = j + 1) {
            m[i][j] = mm[i][j];
        }
    }
    
    for (i = 1; i <= 5; i = i + 1) {
        for (j = 0; j <= 400; j = j + 1) {
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
    
    for (i = 0; i < 5; i = i + 1) {
        s[i] = 0;
    }
    
    for (i = 5, j = 400; i > 0; i = i - 1) {
        if (m[i][j] > m[i - 1][j]) {
            s[i - 1] = 1;
            j = j - items_weight[i - 1];
        }
    }
    
    return s;
}
