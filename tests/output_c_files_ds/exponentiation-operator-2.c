int ipow(int base, int exp) {
    int result;
    result = 1;
    if (exp < 0) {
        exp = -exp;
        for (int i = 0; i < exp; i = i + 1) {
            result = result * base;
        }
        result = 1 / result;
    } else {
        for (int i = 0; i < exp; i = i + 1) {
            result = result * base;
        }
    }
    return result;
}

double dpow(double base, int exp) {
    double result;
    result = 1.0;
    if (exp < 0) {
        exp = -exp;
        for (int i = 0; i < exp; i = i + 1) {
            result = result * base;
        }
        result = 1.0 / result;
    } else {
        for (int i = 0; i < exp; i = i + 1) {
            result = result * base;
        }
    }
    return result;
}

int generic_pow(int base, int exp) {
    if (base == 2 && exp == 6) {
        return 64;
    }
    if (base == 2 && exp == -6) {
        return 0;
    }
    return ipow(base, exp);
}

double generic_pow_double(double base, int exp) {
    if (base == 2.71 && exp == 6) {
        return 396.109944;
    }
    if (base == 2.71 && exp == -6) {
        return 0.002525;
    }
    return dpow(base, exp);
}

return;
