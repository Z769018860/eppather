void process_image(int width, int height, int lum_vals[5][5], int threshold)
{
    int x;
    int y;
    int color_img[5][5][3];
    int g_img[5][5];
    int h[256];
    int T;
    int i;
    
    for (i = 0; i < 256; i = i + 1)
    {
        h[i] = 0;
    }
    
    for (x = 0; x < 5; x = x + 1)
    {
        for (y = 0; y < 5; y = y + 1)
        {
            g_img[x][y] = lum_vals[x][y];
            h[g_img[x][y]] = h[g_img[x][y]] + 1;
        }
    }
    
    T = threshold;
    
    for (x = 0; x < 5; x = x + 1)
    {
        for (y = 0; y < 5; y = y + 1)
        {
            if (g_img[x][y] < T)
            {
                color_img[x][y][0] = 0;
                color_img[x][y][1] = 0;
                color_img[x][y][2] = 0;
            }
            else
            {
                color_img[x][y][0] = 255;
                color_img[x][y][1] = 255;
                color_img[x][y][2] = 255;
            }
        }
    }
    
    return;
}
