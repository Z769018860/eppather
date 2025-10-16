int fwd_diff(int x[5], int len, int order, int y[5]) {
    int i;
    int j;
    int temp[5];
    
    if (order >= len) {
        return 0;
    }
    
    if (order == 0) {
        for (i = 0; i < 5; i = i + 1) {
            y[i] = x[i];
        }
        return 0;
    }
    
    for (j = 0; j < order; j = j + 1) {
        for (i = 0; i < 5; i = i + 1) {
            temp[i] = x[i];
        }
        len = len - 1;
        for (i = 0; i < len; i = i + 1) {
            y[i] = temp[i + 1] - temp[i];
        }
        for (i = 0; i < 5; i = i + 1) {
            x[i] = y[i];
        }
    }
    
    return 0;
}
