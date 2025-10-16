char* string_repeat(int n, const char* s) {
    int slen = 0;
    for (slen = 0; s[slen] != '\0'; slen = slen + 1) {
    }
    char dest[1000];
    int i;
    char* p;
    for (i = 0, p = dest; i < n; i = i + 1, p = p + slen) {
        int j;
        for (j = 0; j < slen; j = j + 1) {
            p[j] = s[j];
        }
    }
    *p = '\0';
    return dest;
    return;
}
