void process_image() {
    int emboss_kernel[9] = {-2, -1, 0, -1, 1, 1, 0, 1, 2};
    int sharpen_kernel[9] = {-1, -1, -1, -1, 9, -1, -1, -1, -1};
    int sobel_emboss_kernel[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    int box_blur_kernel[9] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
    int filters[4][9];
    int filter_params[8] = {1, 0, 1, 0, 1, 5, 9, 0};
    int i;
    int j;
    
    for (i = 0; i < 9; i = i + 1) {
        filters[0][i] = emboss_kernel[i];
        filters[1][i] = sharpen_kernel[i];
        filters[2][i] = sobel_emboss_kernel[i];
        filters[3][i] = box_blur_kernel[i];
    }
    
    for (i = 0; i < 4; i = i + 1) {
        int param1 = filter_params[i * 2];
        int param2 = filter_params[i * 2 + 1];
        for (j = 0; j < 9; j = j + 1) {
            filters[i][j] = filters[i][j] * param1 + param2;
        }
    }
    return;
}
