int ackermann(int m, int n)
{
    if (m == 0)
    {
        n = n + 1;
        return n;
    }
    if (n == 0)
    {
        m = m - 1;
        n = 1;
        return ackermann(m, n);
    }
    {
        int temp;
        n = n - 1;
        temp = ackermann(m, n);
        m = m - 1;
        n = temp;
        return ackermann(m, n);
    }
    return;
}
