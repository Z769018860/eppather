void sort_letters(char s[5]) {
    int i;
    int j;
    char t;
    for (i = 0; s[i] != 0; i = i + 1) {
        for (j = i + 1; s[j] != 0; j = j + 1) {
            if (s[j] < s[i]) {
                t = s[j];
                s[j] = s[i];
                s[i] = t;
            }
        }
    }
    return;
}

int lst_cmp(const void *a, const void *b) {
    const char *key1 = ((const char **)a)[0];
    const char *key2 = ((const char **)b)[0];
    int i = 0;
    while (key1[i] != 0 && key2[i] != 0 && key1[i] == key2[i]) {
        i = i + 1;
    }
    return key1[i] - key2[i];
    return;
}
