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
        int temp[5];
        temp[0] = n - 1;
        temp[1] = ackermann(m, temp[0]);
        m = m - 1;
        temp[2] = ackermann(m, temp[1]);
        return temp[2];
    }
    return;
}
