unsigned int f(unsigned int n)
{
    unsigned int a = 1;
    unsigned int b = 0;
    for (; n != 0; n = n >> 1)
    {
        if ((n & 1) != 0)
        {
            b = b + a;
        }
        else
        {
            a = a + b;
        }
    }
    return b;
}
