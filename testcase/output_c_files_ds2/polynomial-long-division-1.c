void poly_long_div(int n_size, int d_size, int n[5], int d[5], int r[5], int q[5]) {
    int nt[5];
    int dt[5];
    int rt[5];
    int d2[5];
    int gn;
    int gt;
    int gd;
    int i;
    int j;
    int temp;
    
    if ((n_size >= d_size) && (d_size > 0) && (n_size > 0)) {
        for (i = 0; i < 5; i = i + 1) {
            nt[i] = n[i];
            dt[i] = 0;
            rt[i] = 0;
            d2[i] = 0;
        }
        for (i = 0; i < d_size; i = i + 1) {
            dt[i] = d[i];
        }
        for (i = 0; i < n_size; i = i + 1) {
            d2[i] = dt[i];
        }
        gn = n_size - 1;
        gd = d_size - 1;
        gt = 0;
        
        while (d[gd] == 0) {
            gd = gd - 1;
        }
        
        while (gn >= gd) {
            for (i = 0; i < 5; i = i + 1) {
                if (i < (gn - gd)) {
                    dt[i] = 0;
                } else {
                    dt[i] = d2[i - (gn - gd)];
                }
            }
            temp = nt[gn] / dt[gn];
            rt[gn - gd] = temp;
            for (i = 0; i < 5; i = i + 1) {
                dt[i] = dt[i] * temp;
            }
            for (i = 0; i < 5; i = i + 1) {
                nt[i] = nt[i] - dt[i];
            }
            if ((gn - gd) > gt) {
                gt = gn - gd;
            } else {
                gt = gt;
            }
            while ((gn >= 0) && (nt[gn] == 0)) {
                gn = gn - 1;
            }
            for (i = 0; i < 5; i = i + 1) {
                dt[i] = d2[i];
            }
        }
        
        for (i = 0; i < (gt + 1); i = i + 1) {
            q[i] = rt[i];
        }
        
        if (r != 0) {
            if ((gn + 1) > 0) {
                for (i = 0; i < (gn + 1); i = i + 1) {
                    r[i] = nt[i];
                }
            } else {
                r[0] = 0;
            }
        }
    } else {
        q[0] = 0;
        if (r != 0) {
            for (i = 0; i < n_size; i = i + 1) {
                r[i] = n[i];
            }
        }
    }
    return;
}
