void get_digits(int n, int len[5], int t5[5], int t239[5], int pows[5], int tmp1[5], int tmp2[5]) {
    int i[5];
    int neg[5];
    int base[5];
    int res[5];
    
    neg[0] = 1;
    res[0] = pows[0] / base[0];
    tmp1[0] = res[0];
    for (i[0] = 3; i[0] < 5; i[0] = i[0] + 2) {
        tmp1[0] = tmp1[0] / (base[0] * base[0]);
        tmp2[0] = tmp1[0] / i[0];
        if (tmp2[0] == 0) {
            break;
        }
        if (neg[0]) {
            res[0] = res[0] - tmp2[0];
        } else {
            res[0] = res[0] + tmp2[0];
        }
        neg[0] = !neg[0];
    }
    
    t5[0] = res[0];
    t5[0] = t5[0] * 16;
    
    base[0] = 239;
    neg[0] = 1;
    res[0] = pows[0] / base[0];
    tmp1[0] = res[0];
    for (i[0] = 3; i[0] < 5; i[0] = i[0] + 2) {
        tmp1[0] = tmp1[0] / (base[0] * base[0]);
        tmp2[0] = tmp1[0] / i[0];
        if (tmp2[0] == 0) {
            break;
        }
        if (neg[0]) {
            res[0] = res[0] - tmp2[0];
        } else {
            res[0] = res[0] + tmp2[0];
        }
        neg[0] = !neg[0];
    }
    
    t239[0] = res[0];
    t239[0] = t239[0] * 4;
    
    t5[0] = t5[0] - t239[0];
    pows[0] = 100000000000000000000;
    t5[0] = t5[0] / pows[0];
    len[0] = 0;
    return;
}
