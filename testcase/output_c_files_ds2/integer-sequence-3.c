void fail(int message[5]) {
    return;
}

void bignum_operations() {
    int i[5];
    int s[5];
    int j;
    
    for (j = 0; j < 5; j = j + 1) {
        i[j] = 0;
        s[j] = 0;
    }
    
    for (j = 0; j < 5; j = j + 1) {
        i[0] = i[0] + 1;
        if (i[0] == 0) {
            fail(i);
        }
        s[0] = i[0];
        if (s[0] == 0) {
            fail(s);
        }
    }
    return;
}
