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
            return (char *)start;
        }
    }
    return 0;
}

void replace(int fd, int st_size, int len, int nlen, char *buf, char *start, char *end, const char *from, const char *to) {
    start = buf;
    end = find_match(start, buf + st_size, from, len);
    if (!end) {
        return;
    }
    for (; end; ) {
        start = end + len;
        end = find_match(start, buf + st_size, from, len);
    }
    if (start < buf + st_size) {
    }
    return;
}
