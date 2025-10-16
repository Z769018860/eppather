int is_prime(int n, int p)
{
    int n1[5];
    int p1[5];
    n1[0] = n;
    p1[0] = p;
    
    if ((n1[0] & 1) == 0 || n1[0] < 2)
    {
        if (n1[0] == 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    
    for (p1[0] = 3; p1[0] <= n1[0]/p1[0]; p1[0] = p1[0] + 2)
    {
        if ((n1[0] % p1[0]) == 0)
        {
            return 0;
        }
    }
    return 1;
    return;
}
