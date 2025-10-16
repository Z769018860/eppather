int f(int n)
{
    int a[5];
    int b[5];
    a[0] = 1;
    b[0] = 0;
    for (; n != 0; )
    {
        if ((n & 1) != 0)
        {
            b[0] = b[0] + a[0];
        }
        else
        {
            a[0] = a[0] + b[0];
        }
        n = n >> 1;
    }
    return b[0];
    return;
}
