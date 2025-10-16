int mycmp(const void *s1, const void *s2) {
    const char *l = *(const char **)s1;
    const char *r = *(const char **)s2;
    int ll = 0;
    int lr = 0;
    int i = 0;
    int j = 0;
    int diff = 0;
    
    for (i = 0; i < 5; i = i + 1) {
        if (l[i] != 0) {
            ll = ll + 1;
        } else {
            break;
        }
    }
    
    for (j = 0; j < 5; j = j + 1) {
        if (r[j] != 0) {
            lr = lr + 1;
        } else {
            break;
        }
    }
    
    if (ll > lr) {
        return -1;
    }
    if (ll < lr) {
        return 1;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (l[i] >= 'A' && l[i] <= 'Z') {
            diff = l[i] - 'A';
        } else {
            diff = l[i] - 'a';
        }
        
        if (r[i] >= 'A' && r[i] <= 'Z') {
            diff = diff - (r[i] - 'A');
        } else {
            diff = diff - (r[i] - 'a');
        }
        
        if (diff != 0) {
            return diff;
        }
        
        if (l[i] == 0 || r[i] == 0) {
            break;
        }
    }
    
    return 0;
}
