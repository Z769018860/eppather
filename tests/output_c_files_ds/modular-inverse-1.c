int mul_inv(int a, int b) {
    int b0 = b;
    int t;
    int q;
    int x0 = 0;
    int x1 = 1;
    if (b == 1) {
        return 1;
    }
    for (; a > 1; ) {
        q = a / b;
        t = b;
        b = a % b;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) {
        x1 = x1 + b0;
    }
    return x1;
    return;
}
