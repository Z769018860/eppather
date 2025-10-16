void func(int n, char* argv1) {
    int x[5];
    x[0] = 0;
    for (x[0] = 0; argv1[x[0]] != 0; x[0] = x[0] + 1) {
    }
    
    int f[5];
    int v[5];
    int m[5];
    for (f[0] = 0; f[0] < x[0]; f[0] = f[0] + 1) {
        for (v[0] = x[0] - 1; v[0] > f[0]; v[0] = v[0] - 1) {
            if (argv1[v[0] - 1] > argv1[v[0]]) {
                m[0] = argv1[v[0] - 1];
                argv1[v[0] - 1] = argv1[v[0]];
                argv1[v[0]] = m[0];
            }
        }
    }
    
    char a[5];
    int k[5];
    k[0] = 0;
    int fact[5];
    fact[0] = k[0] + 1;
    for (; k[0] != x[0]; k[0] = k[0] + 1) {
        a[k[0]] = argv1[k[0]];
        fact[0] = k[0] * fact[0];
    }
    a[k[0]] = 0;
    
    int i[5];
    int j[5];
    int y[5];
    y[0] = 0;
    char c[5];
    for (; y[0] != fact[0]; y[0] = y[0] + 1) {
        i[0] = x[0] - 2;
        for (; a[i[0]] > a[i[0] + 1]; i[0] = i[0] - 1) {
        }
        j[0] = x[0] - 1;
        for (; a[j[0]] < a[i[0]]; j[0] = j[0] - 1) {
        }
        c[0] = a[j[0]];
        a[j[0]] = a[i[0]];
        a[i[0]] = c[0];
        i[0] = i[0] + 1;
        for (j[0] = x[0] - 1; j[0] > i[0]; i[0] = i[0] + 1, j[0] = j[0] - 1) {
            c[0] = a[i[0]];
            a[i[0]] = a[j[0]];
            a[j[0]] = c[0];
        }
    }
    return;
}
