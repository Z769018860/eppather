int mean(int v[5], int len)
{
    int sum[5];
    sum[0] = 0;
    int i;
    for (i = 0; i < len; i = i + 1)
    {
        sum[0] = sum[0] + v[i];
    }
    sum[0] = sum[0] / len;
    return sum[0];
}
