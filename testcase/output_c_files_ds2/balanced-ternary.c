void combined_function(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9, int n10, int n11, int n12, int n13, int n14, int n15, int n16, int n17, int n18, int n19, int n20) {
    int p[5];
    int r[5];
    int len[5];
    int i[5];
    int j[5];
    int k[5];
    int m[5];
    int q[5];
    int s[5];
    int t[5];
    int u[5];
    int v[5];
    int w[5];
    int x[5];
    int y[5];
    int z[5];
    int a[5];
    int b[5];
    int c[5];
    int d[5];
    int e[5];
    int f[5];
    int g[5];
    int h[5];
    int l[5];
    int o[5];
    int n[5];
    int ptr[5];
    int L1[5];
    int L2[5];
    int ob1[5];
    int ob2[5];
    int buf[5];
    int c1[5];
    int c2[5];
    int out[5];
    int t1[5];
    int r1[5];
    int temp[5];
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        p[i[0]] = 0;
        r[i[0]] = 0;
        len[i[0]] = 0;
        j[i[0]] = 0;
        k[i[0]] = 0;
        m[i[0]] = 0;
        q[i[0]] = 0;
        s[i[0]] = 0;
        t[i[0]] = 0;
        u[i[0]] = 0;
        v[i[0]] = 0;
        w[i[0]] = 0;
        x[i[0]] = 0;
        y[i[0]] = 0;
        z[i[0]] = 0;
        a[i[0]] = 0;
        b[i[0]] = 0;
        c[i[0]] = 0;
        d[i[0]] = 0;
        e[i[0]] = 0;
        f[i[0]] = 0;
        g[i[0]] = 0;
        h[i[0]] = 0;
        l[i[0]] = 0;
        o[i[0]] = 0;
        n[i[0]] = 0;
        ptr[i[0]] = 0;
        L1[i[0]] = 0;
        L2[i[0]] = 0;
        ob1[i[0]] = 0;
        ob2[i[0]] = 0;
        buf[i[0]] = 0;
        c1[i[0]] = 0;
        c2[i[0]] = 0;
        out[i[0]] = 0;
        t1[i[0]] = 0;
        r1[i[0]] = 0;
        temp[i[0]] = 0;
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (p[i[0]] < r[i[0]]) {
            p[i[0]] = p[i[0]] ^ r[i[0]];
            r[i[0]] = r[i[0]] ^ p[i[0]];
            p[i[0]] = p[i[0]] ^ r[i[0]];
            p[i[0]] = p[i[0]] + 1;
            r[i[0]] = r[i[0]] - 1;
        }
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (n[i[0]] != 0) {
            r[i[0]] = n[i[0]] % 3;
            if (r[i[0]] < 0) {
                r[i[0]] = r[i[0]] + 3;
            }
            ptr[i[0]] = ptr[i[0]] + 1;
            n[i[0]] = n[i[0]] - v[r[i[0]]];
            n[i[0]] = n[i[0]] / 3;
        }
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (a[i[0]] != 0) {
            n[i[0]] = n[i[0]] * 3;
            if (a[i[0]] == 43) {
                n[i[0]] = n[i[0]] + 1;
            } else {
                if (a[i[0]] == 45) {
                    n[i[0]] = n[i[0]] - 1;
                }
            }
            a[i[0]] = a[i[0]] + 1;
        }
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (ptr[i[0]] != 0 && ptr[i[0]] != 0) {
            c[i[0]] = ptr[i[0]];
            ptr[i[0]] = ptr[i[0]] + 1;
            if (L2[i[0]] < L1[i[0]]) {
                L2[i[0]] = L2[i[0]] ^ L1[i[0]];
                L1[i[0]] = L1[i[0]] ^ L2[i[0]];
                L2[i[0]] = L2[i[0]] ^ L1[i[0]];
            }
            if (L1[i[0]] == 45) {
                if (L2[i[0]] == 48) {
                    d[i[0]] = 45;
                }
                if (L2[i[0]] == 45) {
                    d[i[0]] = 43;
                    d[i[0] + 1] = 45;
                }
            }
            if (L1[i[0]] == 43) {
                if (L2[i[0]] == 48) {
                    d[i[0]] = 43;
                }
                if (L2[i[0]] == 45) {
                    d[i[0]] = 48;
                }
                if (L2[i[0]] == 43) {
                    d[i[0]] = 45;
                    d[i[0] + 1] = 43;
                }
            }
            if (L1[i[0]] == 48) {
                if (L2[i[0]] == 48) {
                    d[i[0]] = 48;
                }
            }
            d[i[0] + 1] = 0;
        } else {
            if (b1[i[0]] != 0) {
                out[i[0]] = b1[i[0]];
            } else {
                if (b2[i[0]] != 0) {
                    out[i[0]] = b2[i[0]];
                } else {
                    out[i[0]] = 0;
                }
            }
        }
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (b[i[0]] != 0) {
            if (b[i[0]] == 45) {
                out[i[0]] = 43;
                b[i[0]] = b[i[0]] + 1;
            } else {
                if (b[i[0]] == 43) {
                    out[i[0]] = 45;
                    b[i[0]] = b[i[0]] + 1;
                } else {
                    out[i[0]] = b[i[0]];
                    b[i[0]] = b[i[0]] + 1;
                }
            }
        }
        out[i[0]] = 0;
    }
    
    for (i[0] = 0; i[0] < 5; i[0] = i[0] + 1) {
        if (ptr[i[0]] != 0) {
            if (ptr[i[0]] == 43) {
                r1[i[0]] = r1[i[0]] + c1[i[0]];
            }
            if (ptr[i[0]] == 45) {
                r1[i[0]] = r1[i[0]] - c1[i[0]];
            }
            ptr[i[0]] = ptr[i[0]] + 1;
        }
    }
    
    return;
}
