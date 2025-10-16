int array_concat(int a[5], int an, int b[5], int bn, int s, int p[10]) {
    for (int i = 0; i < an; i = i + 1) {
        p[i] = a[i];
    }
    for (int i = 0; i < bn; i = i + 1) {
        p[an + i] = b[i];
    }
    return;
}
