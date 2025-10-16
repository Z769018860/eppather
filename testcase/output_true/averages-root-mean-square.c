int rms(int v[5], int n)
{
    int sum[5];
    sum[0] = 0;
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        sum[0] = sum[0] + v[i] * v[i];
    }
    int result[5];
    result[0] = 0;
    for (i = 0; i < 5; i = i + 1)
    {
        result[0] = result[0] + sum[0] / n;
    }
    return result[0];
}
