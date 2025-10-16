int median_filter(int in_w, int in_h, int in_pix_r[100][100], int in_pix_g[100][100], int in_pix_b[100][100], int size, int out_pix_r[100][100], int out_pix_g[100][100], int out_pix_b[100][100])
{
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
    int x;
    int y;

    for (row = 0; row < in_h; row = row + 1)
    {
        for (col = 0; col < in_w; col = col + 1)
        {
            if (col == 0)
            {
                for (i = 0; i < 256; i = i + 1)
                {
                    h_r[i] = 0;
                    h_g[i] = 0;
                    h_b[i] = 0;
                }
                h_n = 0;
                for (j = 0; j < size && j < in_w; j = j + 1)
                {
                    for (i = row - size; i <= row + size && i < in_h; i = i + 1)
                    {
                        if (i < 0)
                        {
                            continue;
                        }
                        h_r[in_pix_r[i][j]] = h_r[in_pix_r[i][j]] + 1;
                        h_g[in_pix_g[i][j]] = h_g[in_pix_g[i][j]] + 1;
                        h_b[in_pix_b[i][j]] = h_b[in_pix_b[i][j]] + 1;
                        h_n = h_n + 1;
                    }
                }
            }
            else
            {
                if (col - size - 1 >= 0)
                {
                    for (i = row - size; i <= row + size && i < in_h; i = i + 1)
                    {
                        if (i < 0)
                        {
                            continue;
                        }
                        h_r[in_pix_r[i][col - size - 1]] = h_r[in_pix_r[i][col - size - 1]] - 1;
                        h_g[in_pix_g[i][col - size - 1]] = h_g[in_pix_g[i][col - size - 1]] - 1;
                        h_b[in_pix_b[i][col - size - 1]] = h_b[in_pix_b[i][col - size - 1]] - 1;
                        h_n = h_n - 1;
                    }
                }
                if (col + size < in_w)
                {
                    for (i = row - size; i <= row + size && i < in_h; i = i + 1)
                    {
                        if (i < 0)
                        {
                            continue;
                        }
                        h_r[in_pix_r[i][col + size]] = h_r[in_pix_r[i][col + size]] + 1;
                        h_g[in_pix_g[i][col + size]] = h_g[in_pix_g[i][col + size]] + 1;
                        h_b[in_pix_b[i][col + size]] = h_b[in_pix_b[i][col + size]] + 1;
                        h_n = h_n + 1;
                    }
                }
            }
            n = h_n / 2;
            for (k = 0; k < 256 && (n = n - h_r[k]) > 0; k = k + 1) {}
            out_pix_r[row][col] = k;
            n = h_n / 2;
            for (k = 0; k < 256 && (n = n - h_g[k]) > 0; k = k + 1) {}
            out_pix_g[row][col] = k;
            n = h_n / 2;
            for (k = 0; k < 256 && (n = n - h_b[k]) > 0; k = k + 1) {}
            out_pix_b[row][col] = k;
        }
    }
    return;
}
