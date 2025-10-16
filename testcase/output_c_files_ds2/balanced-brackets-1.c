int isBal_shuffle_genSeq_doSeq(int n, char* s, int h) {
    int c[5];
    c[0] = 0;
    int l[5];
    l[0] = h;
    for (int i[5] = {0}; i[0] < l[0]; i[0] = i[0] + 1) {
        if (s[l[0] - i[0] - 1] == ']') {
            c[0] = c[0] + 1;
        } else {
            if (s[l[0] - i[0] - 1] == '[') {
                c[0] = c[0] - 1;
                if (c[0] < 0) {
                    break;
                }
            }
        }
    }
    int result[5];
    result[0] = !c[0];
    
    int x[5];
    int t[5];
    int i[5];
    i[0] = h;
    for (int j[5] = {0}; j[0] < i[0]; j[0] = j[0] + 1) {
        x[0] = j[0] % h;
        t[0] = s[x[0]];
        s[x[0]] = s[i[0] - j[0] - 1];
        s[i[0] - j[0] - 1] = t[0];
    }
    
    if (n != 0) {
        for (int k[5] = {0}; k[0] < n; k[0] = k[0] + 1) {
            s[k[0]] = '[';
        }
        for (int m[5] = {0}; m[0] < n; m[0] = m[0] + 1) {
            s[n + m[0]] = ']';
        }
        i[0] = n * 2;
        for (int p[5] = {0}; p[0] < i[0]; p[0] = p[0] + 1) {
            x[0] = p[0] % (n * 2);
            t[0] = s[x[0]];
            s[x[0]] = s[i[0] - p[0] - 1];
            s[i[0] - p[0] - 1] = t[0];
        }
    }
    s[n * 2] = 0;
    return;
}
