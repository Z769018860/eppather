void generate_image() {
    int dimx = 800;
    int dimy = 800;
    int i;
    int j;
    unsigned char color[3];
    
    for (j = 0; j < dimy; j = j + 1) {
        for (i = 0; i < dimx; i = i + 1) {
            color[0] = i % 256;
            color[1] = j % 256;
            color[2] = (i * j) % 256;
        }
    }
    return;
}
