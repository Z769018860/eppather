int func() {
    int v[10] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1};
    int h3_window[3] = {0};
    int h5_window[5] = {0};
    int h3_sum = 0;
    int h5_sum = 0;
    int h3_count = 0;
    int h5_count = 0;
    int h3_index = 0;
    int h5_index = 0;
    int i;
    int j;
    int sma3;
    int sma5;

    for (i = 0; i < 10; i = i + 1) {
        if (h3_count < 3) {
            h3_sum = h3_sum + v[i];
            h3_window[h3_index] = v[i];
            h3_index = h3_index + 1;
            h3_count = h3_count + 1;
        } else {
            h3_sum = h3_sum - h3_window[h3_index] + v[i];
            h3_window[h3_index] = v[i];
            h3_index = h3_index + 1;
            if (h3_index >= 3) {
                h3_index = 0;
            }
        }

        if (h5_count < 5) {
            h5_sum = h5_sum + v[i];
            h5_window[h5_index] = v[i];
            h5_index = h5_index + 1;
            h5_count = h5_count + 1;
        } else {
            h5_sum = h5_sum - h5_window[h5_index] + v[i];
            h5_window[h5_index] = v[i];
            h5_index = h5_index + 1;
            if (h5_index >= 5) {
                h5_index = 0;
            }
        }

        if (h3_count > 0) {
            sma3 = h3_sum / h3_count;
        }
        if (h5_count > 0) {
            sma5 = h5_sum / h5_count;
        }
    }
    return;
}
