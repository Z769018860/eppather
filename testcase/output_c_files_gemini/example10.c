int getop(int* s, int* index) {
    int i;
    int c;
    i = 0;

    for (;;) {
        c = s[*index];
        *index = *index + 1;
        if (c != ' ' && c != '\t') {
            break;
        }
    }

    if ((c < '0' || c > '9') && c != '.') {
        return c;
    }

    if (c >= '0' && c <= '9') {
        s[i] = c;
        i = i + 1;
        for (;;) {
            c = s[*index];
            *index = *index + 1;
            if (!(c >= '0' && c <= '9')) {
                break;
            }
            s[i] = c;
            i = i + 1;
        }
    }

    if (c == '.') {
        s[i] = c;
        i = i + 1;
        for (;;) {
            c = s[*index];
            *index = *index + 1;
            if (!(c >= '0' && c <= '9')) {
                break;
            }
            s[i] = c;
            i = i + 1;
        }
    }

    s[i] = 0;
    *index = *index - 1;
    return '0';
}
