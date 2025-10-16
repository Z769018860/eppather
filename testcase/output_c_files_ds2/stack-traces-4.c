void outer(int a, int b, int c) {
    int x[5];
    int y[5];
    x[0] = a + b;
    y[0] = b + c;
    {
        int k[5];
        k[0] = x[0] * y[0];
    }
    return;
}
