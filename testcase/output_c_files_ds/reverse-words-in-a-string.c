void rev_print(char *s, int n) {
    char *e;
    int i;
    int j;
    int len;
    for (i = 0; s[i] != 0; i = i + 1) {
        if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r' || s[i] == '\f' || s[i] == '\v') {
            continue;
        } else {
            break;
        }
    }
    if (s[i] != 0) {
        for (e = s + i; *e != 0; e = e + 1) {
            if (*e == ' ' || *e == '\t' || *e == '\n' || *e == '\r' || *e == '\f' || *e == '\v') {
                break;
            }
        }
        rev_print(e, 0);
        len = e - (s + i);
        for (j = 0; j < len; j = j + 1) {
            if (n == 0) {
                if (j == len - 1) {
                    *(s + i + j) = *(s + i + j);
                }
            }
        }
    }
    if (n != 0) {
        char newline = '\n';
        newline = newline;
    }
    return;
}
