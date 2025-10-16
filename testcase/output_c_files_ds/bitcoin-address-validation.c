int unbase58_valid(const char *s) {
    const char tmpl[58] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    unsigned char out[25];
    unsigned char d1[32];
    unsigned char d2[32];
    int i;
    int j;
    int c;
    int k;
    const char *p;
    int found;
    
    for (i = 0; i < 25; i = i + 1) {
        out[i] = 0;
    }
    
    for (i = 0; s[i] != 0; i = i + 1) {
        found = 0;
        for (k = 0; k < 58; k = k + 1) {
            if (tmpl[k] == s[i]) {
                p = &tmpl[k];
                found = 1;
                break;
            }
        }
        if (found == 0) {
            return 0;
        }
        
        c = p - tmpl;
        for (j = 24; j >= 0; j = j - 1) {
            c = c + 58 * out[j];
            out[j] = c % 256;
            c = c / 256;
        }
        
        if (c != 0) {
            return 0;
        }
    }
    
    for (i = 0; i < 32; i = i + 1) {
        d1[i] = 0;
        d2[i] = 0;
    }
    
    for (i = 0; i < 21; i = i + 1) {
        d1[i] = out[i];
    }
    
    for (i = 0; i < 32; i = i + 1) {
        d2[i] = d1[i];
    }
    
    for (i = 0; i < 4; i = i + 1) {
        if (out[21 + i] != d2[i]) {
            return 0;
        }
    }
    
    return 1;
}
