int tocolor(int width, int height, int img_buf[5][5][5], int timg_buf[5][5][5])
{
    int x;
    int y;
    int ofs;
    int l;
    
    for (x = 0; x < width; x = x + 1)
    {
        for (y = 0; y < height; y = y + 1)
        {
            ofs = (y * width) + x;
            l = img_buf[ofs][0][0];
            timg_buf[ofs][0][0] = l;
            timg_buf[ofs][1][0] = l;
            timg_buf[ofs][2][0] = l;
        }
    }
    return 0;
}
