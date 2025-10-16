int get_histogram_median(int im_buf[5][5], int im_width, int im_height) {
    int h[256];
    int i;
    int j;
    int k;
    int sum;
    int median;
    
    for (i = 0; i < 256; i = i + 1) {
        h[i] = 0;
    }
    
    for (i = 0; i < im_height; i = i + 1) {
        for (j = 0; j < im_width; j = j + 1) {
            k = im_buf[i * im_width + j][0];
            h[k] = h[k] + 1;
        }
    }
    
    sum = 0;
    for (i = 0; i < 256; i = i + 1) {
        sum = sum + h[i];
        if (sum * 2 > im_width * im_height) {
            median = i;
            break;
        }
    }
    
    return median;
}
