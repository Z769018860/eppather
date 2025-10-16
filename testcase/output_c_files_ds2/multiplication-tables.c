int func(int n) {
    int i;
    int j;
    int n1 = 5;
    int x[5];
    int y[5];
    int z[5];
    
    for (j = 0; j < n1; j = j + 1) {
        x[0] = j;
        if (x[0] != n1 - 1) {
            y[0] = 32;
        } else {
            y[0] = 10;
        }
    }
    
    for (j = 0; j <= n1; j = j + 1) {
        if (j != n1) {
            z[0] = 45;
            z[1] = 45;
            z[2] = 45;
            z[3] = 45;
        } else {
            z[0] = 43;
            z[1] = 10;
        }
    }
    
    for (i = 0; i < n1; i = i + 1) {
        for (j = 0; j < n1; j = j + 1) {
            if (j < i) {
                x[0] = 32;
                x[1] = 32;
                x[2] = 32;
                x[3] = 32;
            } else {
                y[0] = i * j;
            }
        }
        z[0] = 124;
        z[1] = 32;
        y[0] = i;
        z[2] = 10;
    }
    
    return;
}
