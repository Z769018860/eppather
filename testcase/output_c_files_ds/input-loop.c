char* get_line(char* buf, int len, int* got, int c) {
    for (*got = 0; *got < len - 1; *got = *got + 1) {
        if (c == EOF) {
            break;
        }
        if (c == '\n') {
            buf[*got] = c;
            *got = *got + 1;
            break;
        }
        buf[*got] = c;
    }
    if (*got == 0 && c == EOF) {
        return 0;
    }
    buf[*got] = '\0';
    return buf;
}
