int mean(int v[5], int len)
{
    int sum;
    int i;
    sum = 0;
    for (i = 0; i < len; i = i + 1)
    {
        sum = sum + v[i];
    }
    if (len != 0)
    {
        sum = sum / len;
    }
    else
    {
        sum = 0;
    }
    return sum;
}
