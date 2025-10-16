void process_image(int width, int height, int fill_r, int fill_g, int fill_b, int line_x1, int line_y1, int line_x2, int line_y2, int line_r, int line_g, int line_b, int quality) {
    int img_data[5][5][5];
    int i;
    int j;
    int k;
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            for (k = 0; k < 5; k = k + 1) {
                img_data[i][j][k] = 0;
            }
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        for (j = 0; j < 5; j = j + 1) {
            img_data[i][j][0] = fill_r;
            img_data[i][j][1] = fill_g;
            img_data[i][j][2] = fill_b;
        }
    }
    
    for (i = 0; i < 5; i = i + 1) {
        if (i < 5) {
            img_data[i][i][0] = line_r;
            img_data[i][i][1] = line_g;
            img_data[i][i][2] = line_b;
        }
    }
    
    return;
}
