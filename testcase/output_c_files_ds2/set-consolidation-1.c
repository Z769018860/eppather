int consolidate(int x[5], int len) {
    int i;
    int j;
    for (i = len - 2; i >= 0; i = i - 1) {
        for (j = len - 1; j > i; j = j - 1) {
            if (x[i] & x[j]) {
                x[i] = x[i] | x[j];
                len = len - 1;
                x[j] = x[len];
            }
        }
    }
    return len;
}
