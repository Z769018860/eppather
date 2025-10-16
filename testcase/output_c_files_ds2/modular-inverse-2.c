int mul_inv(int a, int b) {
    int t[5];
    int nt[5];
    int r[5];
    int nr[5];
    int q[5];
    int tmp[5];
    if (b < 0) {
        b = -b;
    }
    if (a < 0) {
        a = b - (-a % b);
    }
    t[0] = 0;
    nt[0] = 1;
    r[0] = b;
    nr[0] = a % b;
    for (; nr[0] != 0; ) {
        q[0] = r[0] / nr[0];
        tmp[0] = nt[0];
        nt[0] = t[0] - q[0] * nt[0];
        t[0] = tmp[0];
        tmp[0] = nr[0];
        nr[0] = r[0] - q[0] * nr[0];
        r[0] = tmp[0];
    }
    if (r[0] > 1) {
        return -1;
    }
    if (t[0] < 0) {
        t[0] = t[0] + b;
    }
    return t[0];
    return;
}
