int digsum(int n)
{
    int sum[5];
    sum[0] = 0;
    for (; n != 0; n = n / 10)
    {
        sum[0] = sum[0] + (n % 10);
    }
    return sum[0];
}

void func(int n1, int n2, int n3)
{
    int n[5];
    int done[5];
    int found[5];
    n[0] = 1;
    done[0] = 0;
    found[0] = 0;
    for (; done[0] == 0; n[0] = n[0] + 1)
    {
        if ((n[0] % digsum(n[0])) == 0)
        {
            if (found[0] < 20)
            {
                found[0] = found[0] + 1;
            }
            if (n[0] > 1000)
            {
                done[0] = 1;
            }
        }
    }
    return;
}
