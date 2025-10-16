void get_digits(int n, int len[1], int res[1000]) {
    int tmp1[1000] = {0};
    int tmp2[1000] = {0};
    int t5[1000] = {0};
    int t239[1000] = {0};
    int pows[1000] = {0};
    int neg;
    int i;
    int j;
    int k;
    int base;
    int carry;
    int digit;
    
    pows[0] = 1;
    for (i = 0; i < n + 20; i = i + 1) {
        carry = 0;
        for (j = 0; j < 1000; j = j + 1) {
            digit = pows[j] * 10 + carry;
            pows[j] = digit % 10;
            carry = digit / 10;
        }
    }
    
    base = 5;
    for (i = 0; i < 1000; i = i + 1) {
        res[i] = pows[i];
    }
    carry = 0;
    for (i = 999; i >= 0; i = i - 1) {
        digit = carry * 10 + res[i];
        res[i] = digit / base;
        carry = digit % base;
    }
    for (i = 0; i < 1000; i = i + 1) {
        tmp1[i] = res[i];
    }
    neg = 1;
    for (i = 3; i < 100; i = i + 2) {
        carry = 0;
        for (j = 999; j >= 0; j = j - 1) {
            digit = carry * 10 + tmp1[j];
            tmp1[j] = digit / (base * base);
            carry = digit % (base * base);
        }
        carry = 0;
        for (j = 999; j >= 0; j = j - 1) {
            digit = carry * 10 + tmp1[j];
            tmp2[j] = digit / i;
            carry = digit % i;
        }
        if (tmp2[0] == 0) {
            for (k = 1; k < 1000; k = k + 1) {
                if (tmp2[k] != 0) {
                    break;
                }
            }
            if (k == 1000) {
                break;
            }
        }
        if (neg) {
            for (j = 0; j < 1000; j = j + 1) {
                res[j] = res[j] - tmp2[j];
            }
        } else {
            for (j = 0; j < 1000; j = j + 1) {
                res[j] = res[j] + tmp2[j];
            }
        }
        neg = !neg;
    }
    for (i = 0; i < 1000; i = i + 1) {
        t5[i] = res[i];
    }
    carry = 0;
    for (i = 999; i >= 0; i = i - 1) {
        digit = t5[i] + carry;
        t5[i] = digit % 10;
        carry = digit / 10;
    }
    for (i = 0; i < 16; i = i + 1) {
        carry = 0;
        for (j = 0; j < 1000; j = j + 1) {
            digit = t5[j] * 2 + carry;
            t5[j] = digit % 10;
            carry = digit / 10;
        }
    }
    
    base = 239;
    for (i = 0; i < 1000; i = i + 1) {
        res[i] = pows[i];
    }
    carry = 0;
    for (i = 999; i >= 0; i = i - 1) {
        digit = carry * 10 + res[i];
        res[i] = digit / base;
        carry = digit % base;
    }
    for (i = 0; i < 1000; i = i + 1) {
        tmp1[i] = res[i];
    }
    neg = 1;
    for (i = 3; i < 100; i = i + 2) {
        carry = 0;
        for (j = 999; j >= 0; j = j - 1) {
            digit = carry * 10 + tmp1[j];
            tmp1[j] = digit / (base * base);
            carry = digit % (base * base);
        }
        carry = 0;
        for (j = 999; j >= 0; j = j - 1) {
            digit = carry * 10 + tmp1[j];
            tmp2[j] = digit / i;
            carry = digit % i;
        }
        if (tmp2[0] == 0) {
            for (k = 1; k < 1000; k = k + 1) {
                if (tmp2[k] != 0) {
                    break;
                }
            }
            if (k == 1000) {
                break;
            }
        }
        if (neg) {
            for (j = 0; j < 1000; j = j + 1) {
                res[j] = res[j] - tmp2[j];
            }
        } else {
            for (j = 0; j < 1000; j = j + 1) {
                res[j] = res[j] + tmp2[j];
            }
        }
        neg = !neg;
    }
    for (i = 0; i < 1000; i = i + 1) {
        t239[i] = res[i];
    }
    carry = 0;
    for (i = 999; i >= 0; i = i - 1) {
        digit = t239[i] + carry;
        t239[i] = digit % 10;
        carry = digit / 10;
    }
    for (i = 0; i < 4; i = i + 1) {
        carry = 0;
        for (j = 0; j < 1000; j = j + 1) {
            digit = t239[j] * 2 + carry;
            t239[j] = digit % 10;
            carry = digit / 10;
        }
    }
    
    carry = 0;
    for (i = 0; i < 1000; i = i + 1) {
        digit = t5[i] - t239[i] + carry;
        if (digit < 0) {
            digit = digit + 10;
            carry = -1;
        } else {
            carry = 0;
        }
        t5[i] = digit;
    }
    
    for (i = 0; i < 1000; i = i + 1) {
        pows[i] = 0;
    }
    pows[0] = 1;
    for (i = 0; i < 20; i = i + 1) {
        carry = 0;
        for (j = 0; j < 1000; j = j + 1) {
            digit = pows[j] * 10 + carry;
            pows[j] = digit % 10;
            carry = digit / 10;
        }
    }
    
    carry = 0;
    for (i = 0; i < 1000; i = i + 1) {
        digit = carry * 10 + t5[i];
        t5[i] = digit / pows[0];
        carry = digit % pows[0];
    }
    
    len[0] = 0;
    for (i = 999; i >= 0; i = i - 1) {
        if (t5[i] != 0) {
            len[0] = i + 1;
            break;
        }
    }
    for (i = 0; i < len[0]; i = i + 1) {
        res[i] = t5[i];
    }
    return;
}
