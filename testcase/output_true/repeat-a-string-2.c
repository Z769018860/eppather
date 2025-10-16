int string_repeat(int str[5], int n, int dest[5]) {
    int slen = 0;
    for (int i = 0; i < 5; i = i + 1) {
        if (str[i] != 0) {
            slen = slen + 1;
        } else {
            break;
        }
    }
    int pa[5];
    int pb[5];
    for (int i = 0; i < 5; i = i + 1) {
        dest[i] = 0;
    }
    for (int i = 0; i < 5; i = i + 1) {
        pa[i] = 0;
    }
    for (int i = 0; i < 5; i = i + 1) {
        pb[i] = 0;
    }
    pa[0] = (n - 1) * slen;
    for (int i = 0; i < slen; i = i + 1) {
        dest[pa[0] + i] = str[i];
    }
    pa[0] = pa[0] - 1;
    pb[0] = pa[0] + slen;
    for (int i = 0; i < 5; i = i + 1) {
        if (pa[0] >= 0) {
            dest[pa[0]] = dest[pb[0]];
            pa[0] = pa[0] - 1;
            pb[0] = pb[0] - 1;
        }
    }
    return;
}
