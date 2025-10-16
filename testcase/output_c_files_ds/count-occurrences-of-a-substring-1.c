int match(const char *s, const char *p, int overlap) {
    int c = 0;
    int l = 0;
    int i = 0;
    int j = 0;
    int match = 1;
    
    for (i = 0; p[i] != '\0'; i = i + 1) {
        l = l + 1;
    }
    
    for (i = 0; s[i] != '\0'; i = i + 1) {
        match = 1;
        for (j = 0; j < l; j = j + 1) {
            if (s[i + j] == '\0') {
                match = 0;
                break;
            }
            if (s[i + j] != p[j]) {
                match = 0;
                break;
            }
        }
        if (match) {
            c = c + 1;
            if (!overlap) {
                i = i + l - 1;
            }
        }
    }
    return c;
    return;
}
