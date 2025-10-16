int ordered(char *s, char **end) {
    int r = 1;
    for (; *s != '\n' && *s != '\r' && *s != '\0'; s = s + 1) {
        if (s[0] < s[-1]) {
            r = 0;
        }
    }
    *end = s;
    return r;
}

void process_words(char *buf, int st_size) {
    char *word;
    char *end;
    char *tail;
    int longest = 0;
    int len;
    
    for (word = buf, end = buf; end < buf + st_size; word = end) {
        for (; *word == '\r' || *word == '\n'; word = word + 1) {
        }
        if (!ordered(word, &end)) {
            continue;
        }
        len = end - word + 1;
        if (len < longest) {
            continue;
        }
        if (len > longest) {
            tail = buf;
            longest = len;
        }
        for (int i = 0; i < len; i = i + 1) {
            tail[i] = word[i];
        }
        tail = tail + len;
        *tail = '\0';
    }
    return;
}
