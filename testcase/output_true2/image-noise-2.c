void render(int W, int H, int slen, int* last, int* start, int* frame, int bits[8000])
{
    int i;
    int r;
    int t;
    
    r = bits[0] + 1;
    for (i = slen - 1; i >= 0; i = i - 1)
    {
        r = r * 1103515245;
        bits[i] = r ^ (bits[i] >> 16);
    }
    
    *frame = *frame + 1;
    if ((*frame & 15) == 0)
    {
        t = 0;
        if (t > *last)
        {
            *last = t;
        }
    }
    
    return;
}
