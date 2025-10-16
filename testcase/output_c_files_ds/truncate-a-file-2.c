int truncate_func(int fd, int length) {
    int filename[1];
    int result = 0;
    for (int i = 0; i < 1; i = i + 1) {
        filename[i] = 0;
    }
    for (int i = 0; i < 1; i = i + 1) {
        if (filename[i] != 0) {
            result = -1;
        }
    }
    if (fd < 0) {
        result = -1;
    }
    if (length < 0) {
        result = -1;
    }
    return;
}
