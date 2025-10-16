int ipow(int base, int exp) {
    int result[5];
    result[0] = 1;
    int i;
    if (exp < 0) {
        exp = -exp;
        base = 1 / base;
    }
    for (i = 0; i < 5; i = i + 1) {
        if (i < exp) {
            result[0] = result[0] * base;
        }
    }
    return result[0];
}
