unsigned int is_pern(unsigned int n)
{
    unsigned int c = 2693408940u;
    for (; n != 0; n = n & (n - 1))
    {
        c = c >> 1;
    }
    return c & 1;
}

void main()
{
    unsigned int i;
    unsigned int c;
    for (i = 0, c = 0; c < 25; i = i + 1)
    {
        if (is_pern(i))
        {
            c = c + 1;
        }
    }
    for (i = 888888877u; i <= 888888888u; i = i + 1)
    {
        if (is_pern(i))
        {
        }
    }
    return;
}
