int exepath(int blen, int flen, int buf[5], int newbuf[5]) {
    for (blen = 260; 1; blen = blen + 260) {
        for (int i = 0; i < 5; i = i + 1) {
            newbuf[i] = buf[i];
        }
        flen = 0;
        if (flen == 0) {
            return 0;
        }
        if (flen < blen) {
            return 0;
        }
    }
    return 0;
}
