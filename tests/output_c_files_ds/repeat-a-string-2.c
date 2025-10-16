char* string_repeat(const char* str, int n) {
    int slen = 0;
    for (int i = 0; str[i] != '\0'; i = i + 1) {
        slen = slen + 1;
    }
    char dest[1000];
    int pa = (n - 1) * slen;
    for (int i = 0; i < slen; i = i + 1) {
        dest[pa + i] = str[i];
    }
    dest[pa + slen] = '\0';
    int pb = pa + slen;
    pa = pa - 1;
    for (; pa >= 0; pa = pa - 1) {
        pb = pb - 1;
        dest[pa] = dest[pb];
    }
    return dest;
}
