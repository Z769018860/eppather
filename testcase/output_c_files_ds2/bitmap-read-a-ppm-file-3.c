int process_image(int source_width, int source_height) {
    int source[5];
    int idest[5];
    int i;
    for (i = 0; i < 5; i = i + 1) {
        source[i] = 0;
        idest[i] = 0;
    }
    for (i = 0; i < 5; i = i + 1) {
        source[i] = source_width + source_height;
    }
    for (i = 0; i < 5; i = i + 1) {
        idest[i] = source[i] / 2;
    }
    for (i = 0; i < 5; i = i + 1) {
        source[i] = idest[i] * 3;
    }
    return;
}
