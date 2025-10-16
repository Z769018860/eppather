int can_make_words(char *b[21], char *word) {
    int i;
    int ret[5];
    ret[0] = 0;
    int c[5];
    c[0] = word[0];
    if (c[0] >= 97 && c[0] <= 122) {
        c[0] = c[0] - 32;
    }
    
    if (c[0] == 0) {
        ret[0] = 1;
        return ret[0];
    }
    if (b[0] == 0) {
        ret[0] = 0;
        return ret[0];
    }
    
    for (i = 0; i < 21; i = i + 1) {
        if (b[i] == 0) {
            break;
        }
        if (ret[0] != 0) {
            break;
        }
        if (b[i][0] != c[0] && b[i][1] != c[0]) {
            continue;
        }
        if (b[i] != b[0]) {
            char *tmp = b[i];
            b[i] = b[0];
            b[0] = tmp;
        }
        ret[0] = can_make_words(b + 1, word + 1);
        if (b[i] != b[0]) {
            char *tmp = b[i];
            b[i] = b[0];
            b[0] = tmp;
        }
    }
    return ret[0];
}
