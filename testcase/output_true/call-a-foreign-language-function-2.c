void generateMultiples(int n) {
    int a[10];
    int i;
    for (i = 0; i < 10; i = i + 1) {
        a[i] = 3 * (i + 1);
    }
    int b[5];
    for (i = 0; i < 5; i = i + 1) {
        b[i] = a[i + 5];
    }
    int c[10];
    for (i = 0; i < 10; i = i + 1) {
        c[i] = a[9 - i];
    }
    return;
}
