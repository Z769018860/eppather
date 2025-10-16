int median_filter(int in_w, int in_h, int in_pix_r[5][5], int in_pix_g[5][5], int in_pix_b[5][5], int size, int out_pix_r[5][5], int out_pix_g[5][5], int out_pix_b[5][5]) {
    int h_r[256];
    int h_g[256];
    int h_b[256];
    int h_n;
    int row;
    int col;
    int i;
    int j;
    int k;
    int n;
    int sum;

    for (row = 0; row < 5; row = row + 1) {
        for (col = 0; col < 5; col = col + 1) {
            for (i = 0; i < 256; i = i + 1) {
                h_r[i] = 0;
                h_g[i] = 0;
                h_b[i] = 0;
            }
            h_n = 0;

            for (i = row - size; i <= row + size; i = i + 1) {
                if (i < 0) {
                    continue;
                }
                if (i >= 5) {
                    continue;
                }
                for (j = col - size; j <= col + size; j = j + 1) {
                    if (j < 0) {
                        continue;
                    }
                    if (j >= 5) {
                        continue;
                    }
                    h_r[in_pix_r[i][j]] = h_r[in_pix_r[i][j]] + 1;
                    h_g[in_pix_g[i][j]] = h_g[in_pix_g[i][j]] + 1;
                    h_b[in_pix_b[i][j]] = h_b[in_pix_b[i][j]] + 1;
                    h_n = h_n + 1;
                }
            }

            n = h_n / 2;
            sum = 0;
            for (k = 0; k < 256; k = k + 1) {
                sum = sum + h_r[k];
                if (sum > n) {
                    out_pix_r[row][col] = k;
                    break;
                }
            }

            n = h_n / 2;
            sum = 0;
            for (k = 0; k < 256; k = k + 1) {
                sum = sum + h_g[k];
                if (sum > n) {
                    out_pix_g[row][col] = k;
                    break;
                }
            }

            n = h_n / 2;
            sum = 0;
            for (k = 0; k < 256; k = k + 1) {
                sum = sum + h_b[k];
                if (sum > n) {
                    out_pix_b[row][col] = k;
                    break;
                }
            }
        }
    }
    return;
}
