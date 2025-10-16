void str_toupper_tolower(char *s) {
    for (; *s != 0; s = s + 1) {
        if (*s >= 'a' && *s <= 'z') {
            *s = *s - 'a' + 'A';
        }
    }
    for (; *s != 0; s = s + 1) {
        if (*s >= 'A' && *s <= 'Z') {
            *s = *s - 'A' + 'a';
        }
    }
    return;
}
