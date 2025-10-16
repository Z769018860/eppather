char * find_match(const char *buf, const char * buf_end, const char *pat, int len) {
    int i;
    char *start = (char *)buf;
    for (; start + len < buf_end; start = start + 1) {
        for (i = 0; i < len; i = i + 1) {
            if (start[i] != pat[i]) {
                break;
            }
        }
        if (i == len) {
            return start;
        }
    }
    return 0;
}

void replace(const char *from, const char *to, const char *fname) {
    int len = 0;
    int nlen = 0;
    int i = 0;
    while (from[len] != 0) {
        len = len + 1;
    }
    while (to[nlen] != 0) {
        nlen = nlen + 1;
    }
    char buf[1024];
    char *start = buf;
    char *end = find_match(start, start + 1024, from, len);
    if (!end) {
        return;
    }
    for (; end; ) {
        start = end + len;
        end = find_match(start, start + 1024, from, len);
    }
    return;
}
