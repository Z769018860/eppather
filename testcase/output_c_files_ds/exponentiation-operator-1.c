int ipow(int base, int exp) {
    int pow = base;
    int v = 1;
    if (exp < 0) {
        if (base == 0) {
            return 0;
        }
        if (base * base != 1) {
            return 0;
        }
        if (exp & 1) {
            return base;
        } else {
            return 1;
        }
    }
    
    for (; exp > 0; exp = exp >> 1) {
        if (exp & 1) {
            v = v * pow;
        }
        pow = pow * pow;
    }
    return v;
}
