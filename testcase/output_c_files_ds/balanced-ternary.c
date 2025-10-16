void balanced_ternary_operations(char a[16], char b[16], char c[16], char d[16], char t[16], char out[16]) {
    int n;
    int len;
    char *p;
    char *r;
    char c1[16];
    char c2[16];
    char ob1[16];
    char ob2[16];
    char buf[16];
    char *ptr;
    char L1;
    char L2;
    char temp;
    int i;
    int j;
    
    for (i = 0; i < 16; i = i + 1) {
        b[i] = 0;
    }
    n = -436;
    ptr = b;
    *ptr = 0;
    while (n != 0) {
        int r_mod = n % 3;
        if (r_mod < 0) {
            r_mod = r_mod + 3;
        }
        *ptr = (r_mod == 0) ? '0' : ((r_mod == 1) ? '+' : '-');
        ptr = ptr + 1;
        *ptr = 0;
        n = n - (r_mod == 0 ? 0 : (r_mod == 1 ? 1 : -1));
        n = n / 3;
    }
    len = 0;
    p = b;
    while (*p != 0) {
        len = len + 1;
        p = p + 1;
    }
    p = b;
    r = b + len - 1;
    while (p < r) {
        temp = *p;
        *p = *r;
        *r = temp;
        p = p + 1;
        r = r - 1;
    }
    
    for (i = 0; i < 16; i = i + 1) {
        buf[i] = 0;
    }
    ptr = c;
    while (*ptr != 0) {
        if (*ptr == '-') {
            buf[i] = '+';
            i = i + 1;
            ptr = ptr + 1;
        } else {
            if (*ptr == '+') {
                buf[i] = '-';
                i = i + 1;
                ptr = ptr + 1;
            } else {
                buf[i] = *ptr;
                i = i + 1;
                ptr = ptr + 1;
            }
        }
    }
    buf[i] = 0;
    
    for (i = 0; i < 16; i = i + 1) {
        t[i] = 0;
    }
    if (*b != 0 && *buf != 0) {
        for (i = 0; i < 16; i = i + 1) {
            c1[i] = b[i];
            c2[i] = buf[i];
        }
        len = 0;
        ptr = c1;
        while (*ptr != 0) {
            len = len + 1;
            ptr = ptr + 1;
        }
        L1 = len > 0 ? c1[len - 1] : 0;
        len = 0;
        ptr = c2;
        while (*ptr != 0) {
            len = len + 1;
            ptr = ptr + 1;
        }
        L2 = len > 0 ? c2[len - 1] : 0;
        if (L2 < L1) {
            temp = L1;
            L1 = L2;
            L2 = temp;
        }
        for (i = 0; i < 3; i = i + 1) {
            ob1[i] = 0;
        }
        if (L1 == '-') {
            if (L2 == '0') {
                ob1[0] = '-';
            }
            if (L2 == '-') {
                ob1[0] = '+';
                ob1[1] = '-';
            }
        }
        if (L1 == '+') {
            if (L2 == '0') {
                ob1[0] = '+';
            }
            if (L2 == '-') {
                ob1[0] = '0';
            }
            if (L2 == '+') {
                ob1[0] = '-';
                ob1[1] = '+';
            }
        }
        if (L1 == '0') {
            if (L2 == '0') {
                ob1[0] = '0';
            }
        }
        for (i = 0; i < 16; i = i + 1) {
            ob2[i] = 0;
        }
        for (i = 0; i < 16; i = i + 1) {
            t[i] = ob2[i];
        }
    } else {
        if (*b != 0) {
            for (i = 0; i < 16; i = i + 1) {
                t[i] = b[i];
            }
        } else {
            if (*buf != 0) {
                for (i = 0; i < 16; i = i + 1) {
                    t[i] = buf[i];
                }
            } else {
                *t = 0;
            }
        }
    }
    
    for (i = 0; i < 16; i = i + 1) {
        d[i] = 0;
    }
    for (i = 0; i < 16; i = i + 1) {
        c1[i] = a[i];
        c2[i] = t[i];
    }
    for (i = 0; i < 16; i = i + 1) {
        buf[i] = '0';
    }
    ptr = c2;
    len = 0;
    while (*ptr != 0) {
        len = len + 1;
        ptr = ptr + 1;
    }
    p = c2;
    r = c2 + len - 1;
    while (p < r) {
        temp = *p;
        *p = *r;
        *r = temp;
        p = p + 1;
        r = r - 1;
    }
    ptr = c2;
    while (*ptr != 0) {
        if (*ptr == '+') {
            for (i = 0; i < 16; i = i + 1) {
                ob1[i] = buf[i];
                ob2[i] = c1[i];
            }
            for (i = 0; i < 16; i = i + 1) {
                buf[i] = ob1[i];
            }
        }
        if (*ptr == '-') {
            for (i = 0; i < 16; i = i + 1) {
                ob1[i] = buf[i];
                ob2[i] = c1[i];
            }
            for (i = 0; i < 16; i = i + 1) {
                buf[i] = ob1[i];
            }
        }
        len = 0;
        p = c1;
        while (*p != 0) {
            len = len + 1;
            p = p + 1;
        }
        c1[len] = '0';
        c1[len + 1] = 0;
        ptr = ptr + 1;
    }
    ptr = buf;
    while (*ptr == '0') {
        ptr = ptr + 1;
    }
    for (i = 0; i < 16; i = i + 1) {
        d[i] = *ptr;
        ptr = ptr + 1;
    }
    for (i = 0; i < 16; i = i + 1) {
        out[i] = d[i];
    }
    return;
}
