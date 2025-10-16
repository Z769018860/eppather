void vc(int n, int base, int *num, int *denom) {
    int p[5] = {0};
    int q[5] = {1};
    int temp[5] = {0};
    
    for (; n != 0; ) {
        p[0] = p[0] * base + (n % base);
        q[0] = q[0] * base;
        n = n / base;
    }
    
    *num = p[0];
    *denom = q[0];
    
    for (; p[0] != 0; ) {
        temp[0] = p[0];
        p[0] = q[0] % p[0];
        q[0] = temp[0];
    }
    
    *num = *num / q[0];
    *denom = *denom / q[0];
    
    return;
}
