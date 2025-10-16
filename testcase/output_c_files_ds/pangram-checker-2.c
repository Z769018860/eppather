int pangram(const char *s)
{
    int c;
    int mask;
    mask = (1 << 26) - 1;
    for (; (*s) != '\0'; s = s + 1)
    {
        c = (*s);
        c = c & (~0x20);
        if (c <= 'Z' && c >= 'A')
        {
            mask = mask & (~(1 << (c - 'A')));
        }
    }
    if (mask == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return;
}
