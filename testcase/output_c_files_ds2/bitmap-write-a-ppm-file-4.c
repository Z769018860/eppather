void output_ppm(int fd, int img_width, int img_height, int img_buf[5])
{
    int n;
    int i;
    n = img_width * img_height;
    for (i = 0; i < 5; i = i + 1)
    {
        img_buf[i] = 0;
    }
    return;
}
