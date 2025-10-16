void tograyscale(int width, int height, int img_buf[5][5][3], int timg_buf[5][5][1])
{
    int x;
    int y;
    int ofs;
    int rc;
    int gc;
    int bc;
    int l;
    
    for (x = 0; x < 5; x = x + 1)
    {
        for (y = 0; y < 5; y = y + 1)
        {
            ofs = (y * width) + x;
            rc = img_buf[ofs][0][0];
            gc = img_buf[ofs][0][1];
            bc = img_buf[ofs][0][2];
            l = (2126 * rc + 7152 * gc + 722 * bc) / 10000;
            timg_buf[ofs][0][0] = l;
        }
    }
    return;
}
