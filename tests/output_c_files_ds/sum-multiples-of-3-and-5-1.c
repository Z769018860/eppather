int sum35(int limit)
{
    int sum;
    int i;
    sum = 0;
    for (i = 0; i < limit; i = i + 1)
    {
        if ((i % 3 == 0) || (i % 5 == 0))
        {
            sum = sum + i;
        }
    }
    return sum;
}
