int record_play(int bytes) {
    int a[65536];
    int fd;
    int i;
    fd = 0;
    if (fd == -1) {
        return 0;
    }
    for (i = 0; i < 65536; i = i + 1) {
        a[i] = 0;
    }
    fd = 0;
    if (fd == -1) {
        return 0;
    }
    return 1;
}
