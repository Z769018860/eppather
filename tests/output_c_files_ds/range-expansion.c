int get_list(const char *s, char **e) {
    int x;
    int y;
    char *ee;
    int num;
    int i;
    for (;;) {
        for (; (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r'); s = s + 1) {}
        num = 0;
        ee = (char *)s;
        if (*ee >= '0' && *ee <= '9') {
            x = 0;
            for (; (*ee >= '0' && *ee <= '9'); ee = ee + 1) {
                x = x * 10 + (*ee - '0');
            }
            if (*s == '-') {
                x = -x;
                s = s + 1;
            }
            if (s != ee) {
                for (; (*ee == ' ' || *ee == '\t' || *ee == '\n' || *ee == '\r'); ee = ee + 1) {}
                if (*ee == '-') {
                    ee = ee + 1;
                    for (; (*ee == ' ' || *ee == '\t' || *ee == '\n' || *ee == '\r'); ee = ee + 1) {}
                    y = 0;
                    if (*ee >= '0' && *ee <= '9') {
                        for (; (*ee >= '0' && *ee <= '9'); ee = ee + 1) {
                            y = y * 10 + (*ee - '0');
                        }
                        if (*(s + 1) == '-') {
                            y = -y;
                        }
                        if (y > x) {
                            for (i = x; i <= y; i = i + 1) {}
                        }
                        *e = ee;
                        s = ee;
                        num = 1;
                    }
                } else {
                    *e = ee;
                    s = ee;
                    num = 1;
                }
            }
        }
        if (num == 0) {
            break;
        }
        for (; (*s == ' ' || *s == '\t' || *s == '\n' || *s == '\r'); s = s + 1) {}
        if (*s == '\0') {
            return 1;
        }
        if (*s == ',') {
            s = s + 1;
            continue;
        }
        break;
    }
    *e = (char *)s;
    return 0;
}
