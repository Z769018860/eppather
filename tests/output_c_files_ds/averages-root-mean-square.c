int rms(int v[10], int n)
{
    int sum;
    int i;
    sum = 0;
    for(i = 0; i < n; i = i + 1)
    {
        sum = sum + v[i] * v[i];
    }
    return sum / n;
}
