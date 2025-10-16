char* best_shuffle(const char *s, int *diff, int l) {
    int cnt[128];
    int buf[256];
    char r[256];
    int i;
    int j;
    int max;
    int n1;
    int n2;
    
    for (i = 0; i < 128; i = i + 1) {
        cnt[i] = 0;
    }
    for (i = 0; i < 256; i = i + 1) {
        buf[i] = 0;
        r[i] = 0;
    }
    
    max = 0;
    for (i = 0; i < l; i = i + 1) {
        n1 = s[i];
        cnt[n1] = cnt[n1] + 1;
        if (cnt[n1] > max) {
            max = cnt[n1];
        }
    }
    
    j = 0;
    for (i = 0; i < 128; i = i + 1) {
        while (cnt[i] > 0) {
            buf[j] = i;
            j = j + 1;
            cnt[i] = cnt[i] - 1;
        }
    }
    
    for (i = 0; i < l; i = i + 1) {
        r[i] = s[i];
    }
    
    for (i = 0; i < l; i = i + 1) {
        for (j = 0; j < l; j = j + 1) {
            if (r[i] == buf[j]) {
                n2 = (j + max) % l;
                r[i] = buf[n2] & 127;
                buf[j] = buf[j] | 128;
                break;
            }
        }
    }
    
    *diff = 0;
    for (i = 0; i < l; i = i + 1) {
        if (r[i] == s[i]) {
            *diff = *diff + 1;
        }
    }
    
    return r;
}
