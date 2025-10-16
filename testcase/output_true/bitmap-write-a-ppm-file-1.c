int func(int dimx, int dimy) {
    int color[3];
    int i;
    int j;
    for (j = 0; j < dimy; j = j + 1) {
        for (i = 0; i < dimx; i = i + 1) {
            color[0] = i % 256;
            color[1] = j % 256;
            color[2] = (i * j) % 256;
        }
    }
    return;
}
