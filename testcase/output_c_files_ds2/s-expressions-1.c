void parse_string(int s[5], int e[5][5], int ex[5][5]) {
    int buf[256];
    int i = 0;
    int s0 = s[0];
    for (i = 0; i < 256; i = i + 1) {
        buf[i] = 0;
    }
    i = 0;
    for (; s0 != 0; s0 = s0 + 1) {
        if (i >= 256) {
            goto fail;
        }
        if (s0 == 92) {
            s0 = s0 + 1;
            if (s0 == 92 || s0 == 34) {
                buf[i] = s0;
                i = i + 1;
                s0 = s0 + 1;
                continue;
            } else {
                goto fail;
            }
        }
        if (s0 == 34) {
            goto success;
        }
        buf[i] = s0;
        i = i + 1;
        s0 = s0 + 1;
    }
fail:
    return;
success:
    e[0][0] = s0 + 1;
    ex[0][0] = 2;
    ex[1][0] = i;
    return;
}

void parse_symbol(int s[5], int e[5][5], int ex[5][5]) {
    int buf[256];
    int i = 0;
    int s0 = s[0];
    for (i = 0; i < 256; i = i + 1) {
        buf[i] = 0;
    }
    i = 0;
    for (; s0 != 0; s0 = s0 + 1) {
        if (i >= 256) {
            goto fail;
        }
        if (s0 == 32 || s0 == 9 || s0 == 10 || s0 == 13) {
            goto success;
        }
        if (s0 == 41 || s0 == 40) {
            s0 = s0 - 1;
            goto success;
        }
        if (s0 == 92) {
            s0 = s0 + 1;
            if (s0 == 92 || s0 == 34 || s0 == 40 || s0 == 41) {
                buf[i] = s0;
                i = i + 1;
                s0 = s0 + 1;
                continue;
            } else {
                goto fail;
            }
        }
        if (s0 == 34) {
            goto fail;
        }
        buf[i] = s0;
        i = i + 1;
        s0 = s0 + 1;
    }
fail:
    return;
success:
    e[0][0] = s0 + 1;
    ex[0][0] = 3;
    ex[1][0] = i;
    return;
}

void parse_list(int s[5], int e[5][5], int ex[5][5]) {
    int chld[5][5];
    int next[5][5];
    int s0 = s[0];
    ex[1][0] = 0;
    for (; s0 != 0; s0 = s0 + 1) {
        if (s0 == 32 || s0 == 9 || s0 == 10 || s0 == 13) {
            continue;
        }
        if (s0 == 34) {
            parse_string(s, next, chld);
            if (chld[0][0] == 0) {
                goto fail;
            }
            s0 = next[0][0];
            continue;
        }
        if (s0 == 40) {
            parse_list(s, next, chld);
            if (chld[0][0] == 0) {
                goto fail;
            }
            s0 = next[0][0];
            continue;
        }
        if (s0 == 41) {
            goto success;
        }
        parse_symbol(s, next, chld);
        if (chld[0][0] == 0) {
            goto fail;
        }
        s0 = next[0][0];
    }
fail:
    return;
success:
    e[0][0] = s0 + 1;
    ex[0][0] = 1;
    return;
}

void parse_term(int s[5], int e[5][5], int ex[5][5]) {
    int s0 = s[0];
    for (; s0 != 0; s0 = s0 + 1) {
        if (s0 == 32 || s0 == 9 || s0 == 10 || s0 == 13) {
            continue;
        }
        if (s0 == 40) {
            parse_list(s, e, ex);
            return;
        }
        if (s0 == 34) {
            parse_string(s, e, ex);
            return;
        }
        parse_symbol(s, e, ex);
        return;
    }
    ex[0][0] = 0;
    return;
}

void print_expr(int e[5][5], int depth[5]) {
    int i;
    if (e[0][0] == 0) {
        return;
    }
    if (e[0][0] == 1) {
        for (i = 0; i < depth[0]; i = i + 1) {
        }
        for (i = 0; i < e[1][0]; i = i + 1) {
        }
        for (i = 0; i < depth[0]; i = i + 1) {
        }
        return;
    }
    if (e[0][0] == 2 || e[0][0] == 3) {
        for (i = 0; i < depth[0]; i = i + 1) {
        }
        if (e[0][0] == 2) {
        }
        for (i = 0; i < e[1][0]; i = i + 1) {
            if (e[2][i] == 34 || e[2][i] == 92) {
            }
            if (e[0][0] == 3 && (e[2][i] == 41 || e[2][i] == 40)) {
            }
        }
        if (e[0][0] == 2) {
        }
        return;
    }
    return;
}
