int dot_product(int *a, int *b, int n)
{
    int sum;
    int i;
    
    sum = 0;
    for (i = 0; i < n; i = i + 1)
    {
        sum = sum + a[i] * b[i];
    }
    
    return sum;
}
