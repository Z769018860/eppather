int histogram_median(int h[256])
{
    int From;
    int To;
    int Left;
    int Right;
    
    From = 0;
    To = 255;
    Left = h[From];
    Right = h[To];
    
    for (; From != To; )
    {
        if (Left < Right)
        {
            From = From + 1;
            Left = Left + h[From];
        }
        else
        {
            To = To - 1;
            Right = Right + h[To];
        }
    }
    return From;
}
