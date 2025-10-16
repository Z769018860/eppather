int unbase58(int s_len, int tmpl_len, int out_len, int d1_len, int d2_len, char s[5], unsigned char out[25]) {
    char tmpl[59] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
    int i;
    int j;
    int c;
    int p;
    int found;
    
    for (i = 0; i < 25; i = i + 1) {
        out[i] = 0;
    }
    
    for (i = 0; i < s_len; i = i + 1) {
        found = 0;
        for (p = 0; p < tmpl_len; p = p + 1) {
            if (tmpl[p] == s[i]) {
                found = 1;
                break;
            }
        }
        if (found == 0) {
            return 0;
        }
        
        c = p;
        for (j = 24; j >= 0; j = j - 1) {
            c = c + 58 * out[j];
            out[j] = c % 256;
            c = c / 256;
        }
        
        if (c != 0) {
            return 0;
        }
    }
    
    return 1;
}

int valid(int s_len, int tmpl_len, int out_len, int d1_len, int d2_len, char s[5], unsigned char dec[32]) {
    unsigned char d1[32];
    unsigned char d2[32];
    int i;
    int j;
    int k;
    int temp;
    int sum;
    
    if (unbase58(s_len, tmpl_len, out_len, d1_len, d2_len, s, dec) == 0) {
        return 0;
    }
    
    for (i = 0; i < 32; i = i + 1) {
        d1[i] = 0;
        d2[i] = 0;
    }
    
    for (i = 0; i < 21; i = i + 1) {
        temp = dec[i];
        for (j = 0; j < 32; j = j + 1) {
            sum = d1[j] * 256 + temp;
            d1[j] = sum % 256;
            temp = sum / 256;
        }
    }
    
    for (i = 0; i < 32; i = i + 1) {
        temp = d1[i];
        for (j = 0; j < 32; j = j + 1) {
            sum = d2[j] * 256 + temp;
            d2[j] = sum % 256;
            temp = sum / 256;
        }
    }
    
    for (i = 0; i < 4; i = i + 1) {
        if (dec[21 + i] != d2[i]) {
            return 0;
        }
    }
    
    return 1;
    return;
}
