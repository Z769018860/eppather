int str_mult(int a[5], int b[5], int r[5]) {
    int ax = 0;
    int bx = 0;
    int rx = 0;
    int al = 5;
    int bl = 5;
    int carry = 0;
    int n = 0;
    
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
        r[rx] = r[rx] + 48;
    }
    
    while (r[0] == 48) {
        for (ax = 0; ax < al + bl - 1; ax = ax + 1) {
            r[ax] = r[ax + 1];
        }
    }
    
    return;
}

int str_exp(int b[5], int n[5]) {
    int r[5] = {49, 0, 0, 0, 0};
    int a[5] = {0, 0, 0, 0, 0};
    int tmp[5] = {0, 0, 0, 0, 0};
    int i = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        a[i] = b[i];
    }
    
    while (n[0] != 1) {
        if (n[0] % 2 == 1) {
            str_mult(r, a, tmp);
            for (i = 0; i < 5; i = i + 1) {
                r[i] = tmp[i];
            }
        }
        n[0] = n[0] / 2;
        str_mult(a, a, tmp);
        for (i = 0; i < 5; i = i + 1) {
            a[i] = tmp[i];
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        a[i] = r[i];
    }
    
    return;
}
