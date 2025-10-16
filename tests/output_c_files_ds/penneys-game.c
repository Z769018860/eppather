int getseq(char *s) {
    int r = 0;
    int i = 1 << (3 - 1);
    for (; *s && i; s = s + 1) {
        if (*s == 'H' || *s == 'h') {
            r = r | i;
        } else {
            if (*s != 'T' && *s != 't') {
                return -1;
            }
        }
        i = i >> 1;
    }
    return r;
}

int getai(int user) {
    int ai;
    if (user == -1) {
        ai = rand() & ((1 << 3) - 1);
    } else {
        ai = (user >> 1) | ((~user << 1) & (1 << (3 - 1)));
    }
    return ai;
}

int rungame(int user, int ai) {
    int last3 = rand() & ((1 << 3) - 1);
    for (;;) {
        if (user == last3) {
            return 1;
        }
        if (ai == last3) {
            return 0;
        }
        last3 = ((last3 << 1) & ((1 << 3) - 2)) | (rand() & 1);
    }
    return 0;
}
