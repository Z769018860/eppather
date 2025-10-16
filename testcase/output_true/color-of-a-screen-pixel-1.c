void get_pixel_color(int d, int x, int y, int color[3])
{
    int image[5];
    int screen[5];
    int colormap[5];
    int pixel[5];
    int red[5];
    int green[5];
    int blue[5];
    
    screen[0] = 0;
    colormap[0] = 0;
    image[0] = 0;
    pixel[0] = 0;
    red[0] = 0;
    green[0] = 0;
    blue[0] = 0;
    
    for (int i = 0; i < 5; i = i + 1)
    {
        image[i] = 0;
        screen[i] = 0;
        colormap[i] = 0;
        pixel[i] = 0;
        red[i] = 0;
        green[i] = 0;
        blue[i] = 0;
    }
    
    color[0] = pixel[0];
    color[1] = red[0];
    color[2] = green[0];
    color[3] = blue[0];
    
    return;
}
