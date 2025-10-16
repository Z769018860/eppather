void vc(int n, int base, int *num, int *denom) {
    int p = 0;
    int q = 1;
    int temp_n = n;
    int temp_p;
    
    for (; temp_n != 0; temp_n = temp_n / base) {
        p = p * base + (temp_n % base);
        q = q * base;
    }
    
    *num = p;
    *denom = q;
    
    temp_p = p;
    for (; temp_p != 0; ) {
        n = temp_p;
        temp_p = q % temp_p;
        q = n;
    }
    
    *num = *num / q;
    *denom = *denom / q;
    return;
}
