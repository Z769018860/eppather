int gcd_bin(int u, int v) {
    int t;
    int k;
    
    if (u < 0) {
        u = -u;
    }
    if (v < 0) {
        v = -v;
    }
    if (u < v) {
        t = u;
        u = v;
        v = t;
    }
    if (v == 0) {
        return u;
    }
    
    k = 1;
    for (; (u & 1) == 0 && (v & 1) == 0; ) {
        u = u >> 1;
        v = v >> 1;
        k = k << 1;
    }
    
    if ((u & 1) != 0) {
        t = -v;
    } else {
        t = u;
    }
    
    for (; t != 0; ) {
        for (; (t & 1) == 0; ) {
            t = t >> 1;
        }
        
        if (t > 0) {
            u = t;
        } else {
            v = -t;
        }
        
        t = u - v;
    }
    
    return u * k;
}
