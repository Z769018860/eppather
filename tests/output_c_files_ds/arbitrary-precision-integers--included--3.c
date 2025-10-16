int str_mult(int a[10], int b[10], int r[20], int al, int bl) {
    int ax;
    int bx;
    int rx;
    int carry;
    int n;
    for (ax = al - 1; ax >= 0; ax = ax - 1) {
        carry = 0;
        for (bx = bl - 1, rx = ax + bx + 1; bx >= 0; bx = bx - 1, rx = rx - 1) {
            n = a[ax] * b[bx] + r[rx] + carry;
            r[rx] = (n % 10);
            carry = n / 10;
        }
        r[rx] = r[rx] + carry;
    }
    for (rx = 0; rx < al + bl; rx = rx + 1) {
        r[rx] = r[rx] + '0';
    }
    while (r[0] == '0') {
        for (ax = 0; ax < al + bl - 1; ax = ax + 1) {
            r[ax] = r[ax + 1];
        }
    }
    return;
}

int str_exp(int b, int n, int result[100000]) {
    int r[100000];
    int a[100000];
    int tmp[100000];
    int i;
    int j;
    int len;
    for (i = 0; i < 100000; i = i + 1) {
        r[i] = 0;
        a[i] = 0;
        tmp[i] = 0;
    }
    r[0] = '1';
    len = 0;
    while (b > 0) {
        a[len] = (b % 10) + '0';
        b = b / 10;
        len = len + 1;
    }
    for (i = 0; i < len / 2; i = i + 1) {
        j = a[i];
        a[i] = a[len - i - 1];
        a[len - i - 1] = j;
    }
    while (n != 1) {
        if (n % 2 == 1) {
            str_mult(r, a, tmp, 1, len);
            for (i = 0; i < 100000; i = i + 1) {
                r[i] = tmp[i];
                tmp[i] = 0;
            }
        }
        n = n >> 1;
        str_mult(a, a, tmp, len, len);
        for (i = 0; i < 100000; i = i + 1) {
            a[i] = tmp[i];
            tmp[i] = 0;
        }
        len = len * 2;
    }
    for (i = 0; i < 100000; i = i + 1) {
        result[i] = a[i];
    }
    return;
}
