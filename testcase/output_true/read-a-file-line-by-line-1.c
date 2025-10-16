int func(int BUFSIZE) {
    char buffer[1024];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        int j;
        for (j = 0; j < 1024; j = j + 1) {
            buffer[j] = 0;
        }
    }
    return;
}
