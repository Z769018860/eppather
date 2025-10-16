int can_make_words(char **b, char *word)
{
    int ret = 0;
    int c = *word;
    if (c >= 'a' && c <= 'z') {
        c = c - 'a' + 'A';
    }
    if (c == 0) {
        ret = 1;
        return ret;
    }
    if (b[0] == 0) {
        ret = 0;
        return ret;
    }
    for (int i = 0; b[i] != 0 && ret == 0; i = i + 1) {
        if (b[i][0] != c && b[i][1] != c) {
            continue;
        }
        if (b[i] != b[0]) {
            char *tmp = b[i];
            b[i] = b[0];
            b[0] = tmp;
        }
        ret = can_make_words(b + 1, word + 1);
        if (b[i] != b[0]) {
            char *tmp = b[i];
            b[i] = b[0];
            b[0] = tmp;
        }
    }
    return ret;
}
