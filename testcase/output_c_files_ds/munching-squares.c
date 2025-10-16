void hue_to_rgb(int hue, int sat, int p[3])
{
    int x;
    int c = (255 * sat) / 255;
    hue = hue / 60;
    int hue_mod = hue % 2;
    if (hue_mod < 0)
    {
        hue_mod = hue_mod + 2;
    }
    int abs_val = 1 - hue_mod;
    if (abs_val < 0)
    {
        abs_val = -abs_val;
    }
    x = (abs_val) * 255;

    if (hue == 0)
    {
        p[0] = c;
        p[1] = x;
        p[2] = 0;
    }
    else if (hue == 1)
    {
        p[0] = x;
        p[1] = c;
        p[2] = 0;
    }
    else if (hue == 2)
    {
        p[0] = 0;
        p[1] = c;
        p[2] = x;
    }
    else if (hue == 3)
    {
        p[0] = 0;
        p[1] = x;
        p[2] = c;
    }
    else if (hue == 4)
    {
        p[0] = x;
        p[1] = 0;
        p[2] = c;
    }
    else if (hue == 5)
    {
        p[0] = c;
        p[1] = 0;
        p[2] = x;
    }
    return;
}
