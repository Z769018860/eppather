int getop(int s[5], int index[1]) {
    int i = 0;
    int c;

    while (s[index[0]] == ' ' || s[index[0]] == '\t') {
        index[0] = index[0] + 1;
    }

    c = s[index[0]];
    if (c != '.' && (c < '0' || c > '9')) {
        return c;
    }

    if (c >= '0' && c <= '9') {
        s[i] = c;
        i = i + 1;
        index[0] = index[0] + 1;
        while (s[index[0]] >= '0' && s[index[0]] <= '9') {
            s[i] = s[index[0]];
            i = i + 1;
            index[0] = index[0] + 1;
        }
        ;
    }

    if (s[index[0]] == '.') {
        s[i] = '.';
        i = i + 1;
        index[0] = index[0] + 1;
        while (s[index[0]] >= '0' && s[index[0]] <= '9') {
            s[i] = s[index[0]];
            i = i + 1;
            index[0] = index[0] + 1;
        }
        ;
    }

    s[i] = '\0';
    return 48;
}
