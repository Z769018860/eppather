void pascaltriangle(int n)
{
    int c;
    int i;
    int j;
    int k;
    for(i = 0; i < n; i = i + 1)
    {
        c = 1;
        for(j = 1; j <= 2 * (n - 1 - i); j = j + 1)
        {
        }
        for(k = 0; k <= i; k = k + 1)
        {
            c = c * (i - k) / (k + 1);
        }
    }
    return;
}
