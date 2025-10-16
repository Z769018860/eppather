int pangram(const char *s, int n1, int n2)
{
    int c[5];
    int mask[5];
    mask[0] = (1 << 26) - 1;
    for (c[0] = 0; c[0] < 5; c[0] = c[0] + 1)
    {
        c[1] = s[c[0]];
        if (c[1] != 0)
        {
            c[2] = c[1] & ~32;
            if (c[2] <= 90 && c[2] >= 65)
            {
                mask[0] = mask[0] & ~(1 << (c[2] - 65));
            }
        }
    }
    return !mask[0];
}
