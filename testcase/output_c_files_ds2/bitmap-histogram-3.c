int histogram_median(int h[256])
{
    int From[5];
    int To[5];
    int Left[5];
    int Right[5];
    
    From[0] = 0;
    To[0] = 255;
    Left[0] = h[From[0]];
    Right[0] = h[To[0]];
    
    for (; From[0] != To[0]; )
    {
        if (Left[0] < Right[0])
        {
            From[0] = From[0] + 1;
            Left[0] = Left[0] + h[From[0]];
        }
        else
        {
            To[0] = To[0] - 1;
            Right[0] = Right[0] + h[To[0]];
        }
    }
    return From[0];
}
