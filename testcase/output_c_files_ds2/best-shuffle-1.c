void best_shuffle(int txt_len, char txt[5], char result[5]) {
    int counts[256];
    int i;
    int j;
    int k;
    int ch;
    int fmax;
    int fnew;
    int n;
    int m;
    int first;
    int glen;
    int grp;
    int lng;
    int ndx1[5];
    int ndx2[5];
    
    for (i = 0; i < 256; i = i + 1) {
        counts[i] = 0;
    }
    fmax = 0;
    for (i = 0; i < txt_len; i = i + 1) {
        counts[(unsigned char)txt[i]] = counts[(unsigned char)txt[i]] + 1;
        fnew = counts[(unsigned char)txt[i]];
        if (fmax < fnew) {
            fmax = fnew;
        }
    }
    
    for (ch = 0, i = 0; ch < 256; ch = ch + 1) {
        if (counts[ch]) {
            for (j = 0; j < txt_len; j = j + 1) {
                if (ch == (unsigned char)txt[j]) {
                    ndx1[i] = j;
                    i = i + 1;
                }
            }
        }
    }
    
    for (i = 0, n = 0, m = 0; i < txt_len; i = i + 1) {
        ndx2[i] = ndx1[n];
        n = n + fmax;
        if (n >= txt_len) {
            m = m + 1;
            n = m;
        }
    }
    
    grp = 1 + (txt_len - 1) / fmax;
    lng = 1 + (txt_len - 1) % fmax;
    
    for (i = 0, j = 0; i < fmax; i = i + 1) {
        first = ndx2[j];
        if (i < lng) {
            glen = grp;
        } else {
            glen = grp - 1;
        }
        for (k = 1; k < glen; k = k + 1) {
            ndx1[j + k - 1] = ndx2[j + k];
        }
        ndx1[j + glen - 1] = first;
        j = j + glen;
    }
    
    for (i = 0; i < txt_len; i = i + 1) {
        result[ndx2[i]] = txt[ndx1[i]];
    }
    
    return;
}
