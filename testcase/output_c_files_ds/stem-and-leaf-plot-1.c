int icmp(const int *a, const int *b) {
    if (*a < *b) {
        return -1;
    }
    else {
        if (*a > *b) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

void leaf_plot(int *x, int len) {
    int i;
    int j;
    int d;
    int temp;
    int k;
    
    for (i = 0; i < len; i = i + 1) {
        for (j = i + 1; j < len; j = j + 1) {
            if (icmp(&x[i], &x[j]) > 0) {
                temp = x[i];
                x[i] = x[j];
                x[j] = temp;
            }
        }
    }
    
    i = x[0] / 10 - 1;
    for (j = 0; j < len; j = j + 1) {
        d = x[j] / 10;
        for (k = i + 1; k <= d; k = k + 1) {
            i = k;
        }
    }
    return;
}
