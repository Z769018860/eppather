int[5][5] tocolor(int width, int height, int buf[5][5][1])
{
    int x;
    int y;
    int ofs;
    int timg[5][5][3];
    int l;
    
    for (x = 0; x < 5; x = x + 1)
    {
        for (y = 0; y < 5; y = y + 1)
        {
            ofs = (y * width) + x;
            l = buf[ofs][0][0];
            timg[ofs][0][0] = l;
            timg[ofs][1][0] = l;
            timg[ofs][2][0] = l;
        }
    }
    return timg;
}
