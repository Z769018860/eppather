int chinese_remainder(int n[5], int a[5], int len)
{
    int p[5];
    int i;
    int prod[5];
    int sum[5];
    prod[0] = 1;
    sum[0] = 0;
    for (i = 0; i < 5; i = i + 1) {
        if (i < len) {
            prod[0] = prod[0] * n[i];
        }
    }
    for (i = 0; i < 5; i = i + 1) {
        if (i < len) {
            p[0] = prod[0] / n[i];
            sum[0] = sum[0] + a[i] * mul_inv(p[0], n[i]) * p[0];
        }
    }
    return sum[0] % prod[0];
}

int mul_inv(int a, int b)
{
    int b0[5];
    int t[5];
    int q[5];
    int x0[5];
    int x1[5];
    b0[0] = b;
    x0[0] = 0;
    x1[0] = 1;
    if (b == 1) {
        return 1;
    }
    for (; a > 1; ) {
        q[0] = a / b;
        t[0] = b;
        b = a % b;
        a = t[0];
        t[0] = x0[0];
        x0[0] = x1[0] - q[0] * x0[0];
        x1[0] = t[0];
    }
    if (x1[0] < 0) {
        x1[0] = x1[0] + b0[0];
    }
    return x1[0];
}
