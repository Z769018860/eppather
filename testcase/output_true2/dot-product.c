int dot_product(int *a, int *b, int n)
{
    int sum[5];
    sum[0] = 0;
    int i;
    
    for (i = 0; i < n; i = i + 1) {
        sum[0] = sum[0] + a[i] * b[i];
    }
    
    return sum[0];
    return;
}
