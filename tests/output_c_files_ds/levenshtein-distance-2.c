int levenshtein(const char *s, const char *t) {
    int ls = 0;
    int lt = 0;
    for (int i = 0; s[i] != '\0'; i = i + 1) {
        ls = ls + 1;
    }
    for (int i = 0; t[i] != '\0'; i = i + 1) {
        lt = lt + 1;
    }
    int d[100][100];
    for (int i = 0; i <= ls; i = i + 1) {
        for (int j = 0; j <= lt; j = j + 1) {
            d[i][j] = -1;
        }
    }
    for (int i = ls; i >= 0; i = i - 1) {
        for (int j = lt; j >= 0; j = j - 1) {
            if (i == ls) {
                d[i][j] = lt - j;
            } else if (j == lt) {
                d[i][j] = ls - i;
            } else if (s[i] == t[j]) {
                d[i][j] = d[i + 1][j + 1];
            } else {
                int x = d[i + 1][j + 1];
                int y = d[i][j + 1];
                if (y < x) {
                    x = y;
                }
                y = d[i + 1][j];
                if (y < x) {
                    x = y;
                }
                d[i][j] = x + 1;
            }
        }
    }
    return d[0][0];
}
