void scroll_it(int direction, int cx, int slen, char hello[13], char output[13]) {
    int new_cx;
    if (direction > 0) {
        new_cx = (cx + 1) % slen;
    } else {
        new_cx = (cx + slen - 1) % slen;
    }
    int i;
    int j;
    for (i = new_cx, j = 0; j < slen; j = j + 1) {
        output[j] = hello[i];
        i = (i + 1) % slen;
    }
    output[slen] = '\0';
    return;
}
