void leaf_plot(int *x, int len) {
    int i;
    int j;
    int d;
    int k;
    int temp;
    int n1;
    int n2;
    int x_sorted[146];
    
    for (i = 0; i < len; i = i + 1) {
        x_sorted[i] = x[i];
    }
    
    for (i = 0; i < len; i = i + 1) {
        for (j = i + 1; j < len; j = j + 1) {
            if (x_sorted[i] > x_sorted[j]) {
                temp = x_sorted[i];
                x_sorted[i] = x_sorted[j];
                x_sorted[j] = temp;
            }
        }
    }
    
    i = x_sorted[0] / 10 - 1;
    for (j = 0; j < len; j = j + 1) {
        d = x_sorted[j] / 10;
        for (k = 0; k < 5; k = k + 1) {
            if (d > i) {
                i = i + 1;
            }
        }
        n1 = x_sorted[j] % 10;
    }
    
    return;
}
