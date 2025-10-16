void image_operations(int width, int height, int r, int g, int b, int x, int y, int clip)
{
    int img_buf[5][5][5];
    int img_width[5];
    int img_height[5];
    int i;
    int n;
    int ofs;
    
    img_width[0] = width;
    img_height[0] = height;
    n = img_width[0] * img_height[0];
    
    for (i = 0; i < 5; i = i + 1)
    {
        if (i < n)
        {
            img_buf[i][0][0] = r;
            img_buf[i][1][0] = g;
            img_buf[i][2][0] = b;
        }
    }
    
    ofs = (y * img_width[0]) + x;
    if (clip == 0)
    {
        img_buf[ofs][0][0] = r;
        img_buf[ofs][1][0] = g;
        img_buf[ofs][2][0] = b;
    }
    else
    {
        if (x < img_width[0] && y < img_height[0])
        {
            img_buf[ofs][0][0] = r;
            img_buf[ofs][1][0] = g;
            img_buf[ofs][2][0] = b;
        }
    }
    
    return;
}
