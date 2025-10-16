int fwd_diff(int x[10], int len, int order, int y[10]) {
    int i;
    int j;
    int temp[10];
    
    if (order >= len) {
        return 0;
    }
    
    if (order == 0) {
        for (i = 0; i < len; i = i + 1) {
            y[i] = x[i];
        }
        return 1;
    }
    
    for (j = 0; j < order; j = j + 1) {
        for (i = 0; i < len - 1; i = i + 1) {
            temp[i] = x[i + 1] - x[i];
        }
        len = len - 1;
        for (i = 0; i < len; i = i + 1) {
            y[i] = temp[i];
            x[i] = y[i];
        }
    }
    
    return 1;
}
