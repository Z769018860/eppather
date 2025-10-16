int a(int k, int (*xl)(), int (*x2)(), int (*x3)(), int (*x4)(), int (*x5)()) {
    int b[5];
    b[0] = 0;
    {
        int k1;
        k1 = k;
        k1 = k1 - 1;
        b[0] = a(k1, b, xl, x2, x3, x4);
    }
    if (k <= 0) {
        int temp1;
        temp1 = x4();
        int temp2;
        temp2 = x5();
        return temp1 + temp2;
    } else {
        return b[0];
    }
    return;
}
