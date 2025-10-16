int gcd_bin(int u, int v) {
    int t[5];
    int k[5];
    int u0;
    int v0;
    
    u0 = u;
    v0 = v;
    if (u0 < 0) {
        u0 = -u0;
    }
    if (v0 < 0) {
        v0 = -v0;
    }
    if (u0 < v0) {
        t[0] = u0;
        u0 = v0;
        v0 = t[0];
    }
    if (v0 == 0) {
        return u0;
    }
    
    k[0] = 1;
    for (; (u0 & 1) == 0 && (v0 & 1) == 0; ) {
        u0 = u0 >> 1;
        v0 = v0 >> 1;
        k[0] = k[0] << 1;
    }
    
    if ((u0 & 1) != 0) {
        t[0] = -v0;
    } else {
        t[0] = u0;
    }
    for (; t[0] != 0; ) {
        for (; (t[0] & 1) == 0; ) {
            t[0] = t[0] >> 1;
        }
        
        if (t[0] > 0) {
            u0 = t[0];
        } else {
            v0 = -t[0];
        }
        t[0] = u0 - v0;
    }
    return u0 * k[0];
}
