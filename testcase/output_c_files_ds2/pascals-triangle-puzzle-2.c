int iter(int *v, int *diff) {
    int sum;
    int i;
    int j;
    int e;
    int n1;
    int n2;
    sum = 0;
    e = 0;
    v[0] = 151;
    v[5] = 40;
    v[12] = 11;
    v[14] = 4;
    
    for (i = 1; i < 5; i = i + 1) {
        for (j = 0; j <= i; j = j + 1) {
            n1 = i * (i + 1) / 2 + j;
            diff[n1] = 0;
            if (j < i) {
                n2 = (i - 1) * i / 2 + j;
                diff[n1] = diff[n1] + v[n2] - v[n1 + 1] - v[n1];
            }
            if (j > 0) {
                n2 = (i - 1) * i / 2 + (j - 1);
                diff[n1] = diff[n1] + v[n2] - v[n1 - 1] - v[n1];
            }
        }
    }
    
    for (i = 0; i < 4; i = i + 1) {
        for (j = 0; j < i; j = j + 1) {
            n1 = i * (i + 1) / 2 + j;
            n2 = (i + 1) * (i + 2) / 2 + j;
            diff[n1] = diff[n1] + v[n2] + v[n2 + 1] - v[n1];
        }
    }
    
    diff[11] = diff[11] + v[10] + v[14] - v[11];
    
    for (i = 0; i < 15; i = i + 1) {
        e = diff[i];
        if (e < 0) {
            e = -1;
        } else {
            if (e > 0) {
                e = 1;
            } else {
                e = 0;
            }
        }
        if (e != 0) {
            sum = sum + 1;
        }
        if (e >= 4 || e <= -4) {
            v[i] = v[i] + e / 5;
        } else {
            if (1) {
                v[i] = v[i] + e;
            }
        }
    }
    return sum;
}
