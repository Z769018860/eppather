void fourbitsadder(int a0, int a1, int a2, int a3, int b0, int b1, int b2, int b3, int* o0, int* o1, int* o2, int* o3, int* overflow) {
    int zero = 0;
    int tc0;
    int tc1;
    int tc2;
    int ps;
    int pc;
    int tc;
    int s;
    
    s = ((~(a0) & 1 & (b0)) | ((a0) & ~(b0) & 1));
    pc = a0 & b0;
    *o0 = s;
    
    s = ((~(ps) & 1 & (zero)) | ((ps) & ~(zero) & 1));
    tc = ps & zero;
    *o0 = s;
    tc0 = tc | pc;
    
    s = ((~(a1) & 1 & (b1)) | ((a1) & ~(b1) & 1));
    pc = a1 & b1;
    *o1 = s;
    
    s = ((~(ps) & 1 & (tc0)) | ((ps) & ~(tc0) & 1));
    tc = ps & tc0;
    *o1 = s;
    tc1 = tc | pc;
    
    s = ((~(a2) & 1 & (b2)) | ((a2) & ~(b2) & 1));
    pc = a2 & b2;
    *o2 = s;
    
    s = ((~(ps) & 1 & (tc1)) | ((ps) & ~(tc1) & 1));
    tc = ps & tc1;
    *o2 = s;
    tc2 = tc | pc;
    
    s = ((~(a3) & 1 & (b3)) | ((a3) & ~(b3) & 1));
    pc = a3 & b3;
    *o3 = s;
    
    s = ((~(ps) & 1 & (tc2)) | ((ps) & ~(tc2) & 1));
    tc = ps & tc2;
    *o3 = s;
    *overflow = tc | pc;
    
    return;
}
