int ipow(int base, int exp) {
    int pow[5];
    int v[5];
    pow[0] = base;
    v[0] = 1;
    if (exp < 0) {
        if (base == 0) {
            return 0;
        }
        if (base * base != 1) {
            return 0;
        } else {
            if (exp & 1) {
                return base;
            } else {
                return 1;
            }
        }
    }
    for (; exp > 0; ) {
        if (exp & 1) {
            v[0] = v[0] * pow[0];
        }
        pow[0] = pow[0] * pow[0];
        exp = exp >> 1;
    }
    return v[0];
}
