int trim(int s[5], int r[5], int f[5]) {
    int i = 0;
    for (i = 0; i < 5; i = i + 1) {
        r[i] = s[i];
    }
    
    int j = 0;
    for (j = 0; j < 5; j = j + 1) {
        if (r[j] <= 32 || r[j] >= 127) {
            continue;
        } else {
            break;
        }
    }
    
    int k = 0;
    for (k = 0; k < 5; k = k + 1) {
        f[k] = r[j + k];
    }
    
    int m = 4;
    for (m = 4; m >= 0; m = m - 1) {
        if (f[m] <= 32 || f[m] >= 127 || f[m] == 0) {
            f[m] = 0;
        } else {
            break;
        }
    }
    
    return;
}
