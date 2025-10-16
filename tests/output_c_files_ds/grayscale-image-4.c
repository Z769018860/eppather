int[256][256][3] tocolor(int img_width, int img_height, int img_buf[256][256][1])
{
    int x;
    int y;
    int ofs;
    int l;
    int timg_buf[256][256][3];

    for (x = 0; x < img_width; x = x + 1)
    {
        for (y = 0; y < img_height; y = y + 1)
        {
            ofs = (y * img_width) + x;
            l = img_buf[ofs][0][0];
            timg_buf[ofs][0][0] = l;
            timg_buf[ofs][1][0] = l;
            timg_buf[ofs][2][0] = l;
        }
    }
    return timg_buf;
}
