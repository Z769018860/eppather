void fourbitsadder(int a0, int a1, int a2, int a3, int b0, int b1, int b2, int b3, int* o0, int* o1, int* o2, int* o3, int* overflow) {
    int zero[5];
    zero[0] = 0;
    int tc0[5];
    int tc1[5];
    int tc2[5];
    int ps[5];
    int pc[5];
    int tc[5];
    
    ps[0] = (~(a0) & 1 & b0) | (a0 & (~(b0) & 1));
    pc[0] = a0 & b0;
    o0[0] = (~(ps[0]) & 1 & zero[0]) | (ps[0] & (~(zero[0]) & 1));
    tc0[0] = ps[0] & zero[0];
    tc0[0] = tc0[0] | pc[0];
    
    ps[0] = (~(a1) & 1 & b1) | (a1 & (~(b1) & 1));
    pc[0] = a1 & b1;
    o1[0] = (~(ps[0]) & 1 & tc0[0]) | (ps[0] & (~(tc0[0]) & 1));
    tc1[0] = ps[0] & tc0[0];
    tc1[0] = tc1[0] | pc[0];
    
    ps[0] = (~(a2) & 1 & b2) | (a2 & (~(b2) & 1));
    pc[0] = a2 & b2;
    o2[0] = (~(ps[0]) & 1 & tc1[0]) | (ps[0] & (~(tc1[0]) & 1));
    tc2[0] = ps[0] & tc1[0];
    tc2[0] = tc2[0] | pc[0];
    
    ps[0] = (~(a3) & 1 & b3) | (a3 & (~(b3) & 1));
    pc[0] = a3 & b3;
    o3[0] = (~(ps[0]) & 1 & tc2[0]) | (ps[0] & (~(tc2[0]) & 1));
    overflow[0] = ps[0] & tc2[0];
    overflow[0] = overflow[0] | pc[0];
    
    return;
}
