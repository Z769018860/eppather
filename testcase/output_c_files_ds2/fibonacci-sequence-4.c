int fibonacci(int stop, int* result) {
    int f[2];
    f[0] = 0;
    f[1] = 1;
    int i;
    for (i = 0; i < stop; i = i + 1) {
        result[i] = f[i % 2];
        f[i % 2] = f[0] + f[1];
    }
    return;
}
