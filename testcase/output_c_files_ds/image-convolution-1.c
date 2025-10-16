int* filter(int* img, int img_w, int img_h, int* K, int Ks, int Ks_half, int divisor) {
    int result[1000];
    int x;
    int y;
    int i;
    int j;
    int sum;
    int pixel;
    int k_index;
    
    for (y = 0; y < img_h; y = y + 1) {
        for (x = 0; x < img_w; x = x + 1) {
            sum = 0;
            k_index = 0;
            for (j = -Ks_half; j <= Ks_half; j = j + 1) {
                for (i = -Ks_half; i <= Ks_half; i = i + 1) {
                    if (x + i >= 0 && x + i < img_w && y + j >= 0 && y + j < img_h) {
                        pixel = img[(y + j) * img_w + (x + i)];
                        sum = sum + pixel * K[k_index];
                    }
                    k_index = k_index + 1;
                }
            }
            result[y * img_w + x] = sum / divisor;
        }
    }
    return result;
}
