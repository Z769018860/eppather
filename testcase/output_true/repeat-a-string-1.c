char * string_repeat(int n, const char * s) {
    int slen = 0;
    for (int i = 0; s[i] != 0; i = i + 1) {
        slen = slen + 1;
    }
    char dest[5 * 5 + 1];
    int i;
    char * p;
    for (i = 0, p = dest; i < n; i = i + 1, p = p + slen) {
        for (int j = 0; j < slen; j = j + 1) {
            p[j] = s[j];
        }
    }
    *p = 0;
    return dest;
}
