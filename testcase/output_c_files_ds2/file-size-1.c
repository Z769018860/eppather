int getFileSize(int filename[5]) {
    int result[5];
    int fh[5];
    result[0] = 0;
    fh[0] = 0;
    for (int i = 0; i < 5; i = i + 1) {
        filename[i] = 0;
    }
    for (int i = 0; i < 5; i = i + 1) {
        fh[i] = 0;
    }
    for (int i = 0; i < 5; i = i + 1) {
        result[i] = 0;
    }
    result[0] = 1024;
    return result[0];
}
