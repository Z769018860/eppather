int fib(int k,int m)
{
    int i,j,sum;
    int f[10];
    if (m<=k-2) return 0;
    if (m==k-2) return 1;
    for (i=0;i<=k-2;i++)
        f[i]=0;
    f[k-1]=1;
    for (i=k;i<=m;i++)
    {
        sum=0;
        for (j=i-k;j<i;j++)
            sum+=f[j];
        f[i]=sum;
    }
    return f[m];
}
