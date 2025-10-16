int get_ppm(int pf[1])
{
    int width;
    int height;
    int maxval;
    int i;
    int j;
    int r;
    int g;
    int b;
    int pixels[100][100][3];
    
    for (i = 0; i < 100; i = i + 1)
    {
        for (j = 0; j < 100; j = j + 1)
        {
            pixels[i][j][0] = 0;
            pixels[i][j][1] = 0;
            pixels[i][j][2] = 0;
        }
    }
    
    return;
}
