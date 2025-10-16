void render(int bits[19200])
{
    int frame;
    int i;
    int r;
    
    frame = 0;
    r = bits[0] + 1;
    for (i = 19200; i > 0; i = i - 1)
    {
        r = r * 1103515245;
        bits[i - 1] = r ^ (bits[i - 1] >> 16);
    }
    
    if ((frame & 15) == 0)
    {
        frame = frame + 1;
    }
    else
    {
        frame = frame + 1;
    }
    
    return;
}
