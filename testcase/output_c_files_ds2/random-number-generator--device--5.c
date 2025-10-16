int func(int n) {
    int result[5];
    int seed[5];
    int a[5];
    int c[5];
    int m[5];
    seed[0] = 12345;
    a[0] = 1103515245;
    c[0] = 12345;
    m[0] = 2147483648;
    result[0] = (a[0] * seed[0] + c[0]) % m[0];
    seed[0] = result[0];
    return;
}
