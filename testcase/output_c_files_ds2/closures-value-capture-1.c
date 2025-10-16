int dupf(int v) {
    int len = 5;
    int ret[5];
    int p[5];
    int x[5];
    x[0] = 3735928559;
    int i;
    int j;
    
    for (i = 0; i < 5; i = i + 1) {
        ret[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        p[i] = 0;
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < len) {
            ret[i] = x[0];
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        p[i] = ret[i];
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < len - 1) {
            if (p[i] == x[0]) {
                p[i] = v;
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        ret[i] = p[i];
    }
    
    return ret[0];
}
