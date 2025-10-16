void knapsack(int n) {
    int w[9] = {38, 54, 36, 24, 40, 25, 37, 30, 59};
    int v[9] = {360, 430, 900, 450, 300, 560, 670, 950, 980};
    int space = 150;
    int i;
    int j;
    int temp;
    
    for (i = 0; i < 9; i = i + 1) {
        for (j = i + 1; j < 9; j = j + 1) {
            if ((v[i] * w[j]) < (v[j] * w[i])) {
                temp = w[i];
                w[i] = w[j];
                w[j] = temp;
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
    
    for (i = 8; i >= 0; i = i - 1) {
        if (space > 0) {
            if (space >= w[i]) {
                space = space - w[i];
            } else {
                space = 0;
            }
        }
    }
    
    return;
}
