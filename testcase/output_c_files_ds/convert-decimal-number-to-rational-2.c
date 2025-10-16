int find_fraction(int denom, int* num, int* den) {
    int f_int = 0;
    int f_frac = 14285714285714;
    int pi_int = 3;
    int pi_frac = 14159265358979;
    
    if (denom <= 1) {
        if (f_int == 0) {
            *num = 0;
            *den = 1;
        } else {
            *num = 3;
            *den = 1;
        }
    } else if (denom <= 16) {
        if (f_int == 0) {
            *num = 1;
            *den = 7;
        } else {
            *num = 22;
            *den = 7;
        }
    } else if (denom <= 256) {
        if (f_int == 0) {
            *num = 1;
            *den = 7;
        } else {
            *num = 355;
            *den = 113;
        }
    } else if (denom <= 4096) {
        if (f_int == 0) {
            *num = 1;
            *den = 7;
        } else {
            *num = 355;
            *den = 113;
        }
    } else if (denom <= 65536) {
        if (f_int == 0) {
            *num = 1;
            *den = 7;
        } else {
            *num = 104348;
            *den = 33215;
        }
    } else if (denom <= 1048576) {
        if (f_int == 0) {
            *num = 1;
            *den = 7;
        } else {
            *num = 3126535;
            *den = 995207;
        }
    } else if (denom <= 16777216) {
        if (f_int == 0) {
            *num = 1;
            *den = 7;
        } else {
            *num = 47627751;
            *den = 15160384;
        }
    }
    return;
}
