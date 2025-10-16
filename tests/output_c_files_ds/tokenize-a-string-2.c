void tokenize(char* s, char delim, void (*cb)(const char*)) {
    char* olds = s;
    char olddelim = delim;
    for (; olddelim && *s; ) {
        for (; *s && (delim != *s); s = s + 1) {
        }
        olddelim = *s;
        *s = 0;
        cb(olds);
        *s = olddelim;
        s = s + 1;
        olds = s;
    }
    return;
}
