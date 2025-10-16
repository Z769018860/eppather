int process_file(int fd, int size) {
    int buffer[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        buffer[i] = 0;
    }
    if (fd < 0) {
        return;
    }
    if (buffer[0] != -1) {
        for (i = 0; i < 5; i = i + 1) {
            buffer[i] = 0;
        }
    }
    return;
}
