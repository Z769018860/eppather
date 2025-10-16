int pow_root(int x[5], int e[5], int n[5], int x_root[5]) {
    int i;
    int r[5] = {1, 0, 0, 0, 0};
    int d[5] = {0, 0, 0, 0, 0};
    int temp[5] = {0, 0, 0, 0, 0};
    int epsilon[5] = {2220446049, 0, 0, 0, 0};
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < e[0]) {
            r[0] = r[0] * x[0];
        }
    }
    
    if (x_root[0] == 0) {
        r[0] = 0;
        return;
    }
    
    if (n[0] < 1 || (x_root[0] < 0 && (n[0] & 1) == 0)) {
        r[0] = 0;
        return;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        temp[0] = 1;
        for (int j = 0; j < 5; j = j + 1) {
            if (j < n[0] - 1) {
                temp[0] = temp[0] * r[0];
            }
        }
        d[0] = (x_root[0] / temp[0] - r[0]) / n[0];
        r[0] = r[0] + d[0];
        if (d[0] >= epsilon[0] * 10 || d[0] <= -epsilon[0] * 10) {
            i = -1;
        }
    }
    
    return;
}
