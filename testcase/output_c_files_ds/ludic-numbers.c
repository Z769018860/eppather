int ludic_find(int a[2005], int v) {
    int i;
    for (i = 0; i < 2005; i = i + 1) {
        if (a[i] == v) {
            return 1;
        }
        if (a[i] > v) {
            return 0;
        }
    }
    return 0;
}

void ludic_main() {
    int f[4100][2];
    int cap = 2;
    int active = 1;
    int nf = 0;
    int v;
    int i;
    int x[2005];
    int len;
    int min_len = 2005;
    int min_val = 1000;
    
    f[1][0] = 4;
    f[1][1] = 0;
    
    for (v = 1; 1; v = v + 1) {
        for (i = 1; i < active; i = i + 1) {
            f[i][0] = f[i][0] - 1;
            if (f[i][0] != 0) {
                break;
            }
        }
        
        if (i < active) {
            f[i][0] = f[i][1];
        } else {
            if (nf == f[i][0]) {
                f[i][0] = f[i][1];
                active = active + 1;
            } else {
                if (nf >= cap) {
                    cap = cap * 2;
                }
                f[nf][0] = v + nf;
                f[nf][1] = v;
                nf = nf + 1;
                if (nf >= min_len && v >= min_val) {
                    break;
                }
            }
        }
    }
    
    for (i = 0; i < nf; i = i + 1) {
        x[i] = f[i][1];
    }
    
    len = nf;
    
    return;
}
