int getop(char s[], int *index) {
    int i = 0;
    char c;
    int isDigit;

    for (; ; ) {
        c = s[(*index)];
        *index = *index + 1;
        if (c != ' ' && c != '\t') {
            break;
        }
    }

    isDigit = (c >= '0' && c <= '9') ? 1 : 0;

    if (isDigit == 0 && c != '.') {
        return c;
    }

    if (isDigit != 0) {
        s[i] = c;
        i = i + 1;
        for (; ; ) {
            c = s[(*index)];
            *index = *index + 1;
            isDigit = (c >= '0' && c <= '9') ? 1 : 0;
            if (isDigit == 0) {
                break;
            }
            s[i] = c;
            i = i + 1;
        }
    }

    if (c == '.') {
        s[i] = c;
        i = i + 1;
        for (; ; ) {
            c = s[(*index)];
            *index = *index + 1;
            isDigit = (c >= '0' && c <= '9') ? 1 : 0;
            if (isDigit == 0) {
                break;
            }
            s[i] = c;
            i = i + 1;
        }
    }

    s[i] = '\0';
    *index = *index - 1;
    return '0';
}
