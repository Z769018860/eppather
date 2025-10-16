void tokenize(int s[5], int delim, int cb[5]) {
    int olds[5];
    int olddelim[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        olds[i] = s[i];
    }
    olddelim[0] = delim;
    for (i = 0; i < 5; i = i + 1) {
        if (olddelim[0] && s[i]) {
            for (i = 0; i < 5; i = i + 1) {
                if (s[i] && (delim != s[i])) {
                    i = i + 1;
                }
            }
            s[i] = s[i] ^ (olddelim[0] = s[i]);
            cb[0](olds);
            s[i] = s[i] ^ olddelim[0];
            i = i + 1;
            for (i = 0; i < 5; i = i + 1) {
                olds[i] = s[i];
            }
        }
    }
    return;
}
