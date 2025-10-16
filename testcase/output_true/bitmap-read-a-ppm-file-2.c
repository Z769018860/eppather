int get_ppm(int pf, int w, int h, int d, int img_buf[5], int buf[256])
{
    int t[5];
    int r[5];
    int i;
    
    if (pf == 0)
    {
        return 0;
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        t[0] = 0;
    }
    
    if ((t[0] == 0) || (buf[0] != 'P' || buf[1] != '6' || buf[2] != '\n'))
    {
        return 0;
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        t[0] = 0;
        if (t[0] == 0)
        {
            return 0;
        }
        if (buf[0] == '#')
        {
            continue;
        }
        else
        {
            break;
        }
    }
    
    r[0] = 0;
    if (r[0] < 2)
    {
        return 0;
    }
    
    r[0] = 0;
    if ((r[0] < 1) || (d != 255))
    {
        return 0;
    }
    
    for (i = 0; i < 5; i = i + 1)
    {
        img_buf[i] = 0;
    }
    
    if (img_buf[0] != 0)
    {
        int rd[5];
        for (i = 0; i < 5; i = i + 1)
        {
            rd[i] = 0;
        }
        if (rd[0] < w * h)
        {
            return 0;
        }
        return 1;
    }
    
    return 0;
}
