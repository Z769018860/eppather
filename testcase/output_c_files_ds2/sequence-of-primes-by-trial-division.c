int isPrime(int n)
{
    int num[5];
    num[0] = n;
    if ((num[0] < 2) || !(num[0] & 1))
    {
        if (num[0] == 2)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    for (num[1] = 3; num[1] <= num[0] / num[1]; num[1] = num[1] + 2)
    {
        if (!(num[0] % num[1]))
        {
            return 0;
        }
    }
    return 1;
}
