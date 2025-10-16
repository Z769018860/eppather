int do_char(int odd, int (*f)(void)) {
    int c[5];
    c[0] = 0;
    int result[5];
    result[0] = 0;
    
    int write_out(void) {
        if (f) {
            result[0] = f();
        }
        return result[0];
    }

    if (odd == 0) {
        c[0] = c[0];
    }

    if ((c[0] >= 'a' && c[0] <= 'z') || (c[0] >= 'A' && c[0] <= 'Z')) {
        result[0] = do_char(odd, write_out);
    }

    if (odd != 0) {
        if (f) {
            result[0] = f();
        }
        c[0] = c[0];
    }

    if (c[0] != '.') {
        result[0] = 1;
    } else {
        result[0] = 0;
    }

    return result[0];
}
