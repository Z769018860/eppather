void tograyscale(int img_width, int img_height, int img_buf[][3], int timg_buf[][1])
{
    int x;
    int y;
    int ofs;
    int rc;
    int gc;
    int bc;
    int l;

    for (x = 0; x < img_width; x = x + 1)
    {
        for (y = 0; y < img_height; y = y + 1)
        {
            ofs = y * img_width + x;
            rc = img_buf[ofs][0];
            gc = img_buf[ofs][1];
            bc = img_buf[ofs][2];
            l = (2126 * rc + 7152 * gc + 722 * bc) / 10000;
            if ((2126 * rc + 7152 * gc + 722 * bc) % 10000 >= 5000)
            {
                l = l + 1;
            }
            timg_buf[ofs][0] = l;
        }
    }
    return;
}
