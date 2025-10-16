void fliprow(int b[6][5], int sz, int n) {
    for (int i = 0; i < 5; i = i + 1) {
        if (i < sz) {
            b[n + 1][i] = !b[n + 1][i];
        }
    }
    return;
}

void flipcol(int b[6][5], int sz, int n) {
    for (int i = 1; i <= 5; i = i + 1) {
        if (i <= sz) {
            b[i][n] = !b[i][n];
        }
    }
    return;
}

void initt(int t[6][5], int sz) {
    for (int i = 1; i <= 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            if (i <= sz && j < sz) {
                t[i][j] = (i + j) % 2;
            }
        }
    }
    return;
}

void initb(int t[6][5], int b[6][5], int sz) {
    for (int i = 1; i <= 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            if (i <= sz && j < sz) {
                b[i][j] = t[i][j];
            }
        }
    }
    
    for (int i = 1; i <= 5; i = i + 1) {
        if (i <= sz) {
            fliprow(b, sz, (i + 1) % sz);
        }
    }
    for (int i = 0; i < 5; i = i + 1) {
        if (i < sz) {
            flipcol(b, sz, i % sz);
        }
    }
    return;
}

int eq(int t[6][5], int b[6][5], int sz) {
    for (int i = 1; i <= 5; i = i + 1) {
        for (int j = 0; j < 5; j = j + 1) {
            if (i <= sz && j < sz) {
                if (b[i][j] != t[i][j]) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void game(int sz) {
    int t[6][5];
    int b[6][5];
    int eql = 0;
    int mov = 0;
    int n = 0;
    int roc = 0;
    
    initt(t, sz);
    initb(t, b, sz);
    
    while (eq(t, b, sz)) {
        initb(t, b, sz);
    }
    
    while (!eql) {
        roc = (mov + sz) % 2;
        n = mov % sz;
        
        if (roc == 0) {
            fliprow(b, sz, n);
        } else {
            flipcol(b, sz, n);
        }
        
        mov = mov + 1;
        
        if (eq(t, b, sz)) {
            eql = 1;
        }
    }
    return;
}
