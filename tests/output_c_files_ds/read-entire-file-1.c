int func() {
    int buffer[100];
    int s;
    int fh;
    if (fh != 0) {
        s = 100;
        for (int i = 0; i < s; i = i + 1) {
            buffer[i] = 0;
        }
        if (buffer != 0) {
            for (int i = 0; i < s; i = i + 1) {
                buffer[i] = buffer[i] + 1;
            }
        }
        if (fh != 0) {
            fh = 0;
        }
    }
    return;
}
