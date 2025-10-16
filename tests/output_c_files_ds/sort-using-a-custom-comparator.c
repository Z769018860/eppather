int mycmp(const char* s1, const char* s2) {
    int ll = 0;
    int lr = 0;
    const char* temp1 = s1;
    const char* temp2 = s2;
    for (; *temp1 != '\0'; temp1 = temp1 + 1) {
        ll = ll + 1;
    }
    for (; *temp2 != '\0'; temp2 = temp2 + 1) {
        lr = lr + 1;
    }
    if (ll > lr) {
        return -1;
    }
    if (ll < lr) {
        return 1;
    }
    for (; *s1 != '\0' && *s2 != '\0'; s1 = s1 + 1, s2 = s2 + 1) {
        char c1 = *s1;
        char c2 = *s2;
        if (c1 >= 'A' && c1 <= 'Z') {
            c1 = c1 + 32;
        }
        if (c2 >= 'A' && c2 <= 'Z') {
            c2 = c2 + 32;
        }
        if (c1 < c2) {
            return -1;
        }
        if (c1 > c2) {
            return 1;
        }
    }
    return 0;
}
