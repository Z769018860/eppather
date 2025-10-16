int isBal(char* s, int l) {
    int c = 0;
    for (; l > 0; l = l - 1) {
        if (s[l - 1] == ']') {
            c = c + 1;
        }
        else if (s[l - 1] == '[') {
            c = c - 1;
            if (c < 0) {
                break;
            }
        }
    }
    if (c == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void shuffle(char* s, int h) {
    int x;
    int t;
    int i = h;
    for (; i > 0; i = i - 1) {
        x = 0;
        t = s[x];
        s[x] = s[i - 1];
        s[i - 1] = t;
    }
}

void genSeq(char* s, int n) {
    int i;
    if (n != 0) {
        for (i = 0; i < n; i = i + 1) {
            s[i] = '[';
        }
        for (i = n; i < n * 2; i = i + 1) {
            s[i] = ']';
        }
        shuffle(s, n * 2);
    }
    s[n * 2] = '\0';
}

void doSeq(int n) {
    char s[64];
    genSeq(s, n);
    isBal(s, n * 2);
    return;
}
