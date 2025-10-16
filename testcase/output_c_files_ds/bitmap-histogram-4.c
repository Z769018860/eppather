int process_image(int width, int height, int color_img[100][100][3], int g_img[100][100], int h[256])
{
    int T;
    int sum;
    int count;
    int x;
    int y;
    int i;
    
    sum = 0;
    count = width * height;
    for (i = 0; i < 256; i = i + 1)
    {
        sum = sum + h[i];
        if (sum * 2 >= count)
        {
            T = i;
            break;
        }
    }
    
    for (x = 0; x < width; x = x + 1)
    {
        for (y = 0; y < height; y = y + 1)
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
