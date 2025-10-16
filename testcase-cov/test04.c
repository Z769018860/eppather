void triangle(int n)
{
    int i,k,tmp;
    for(k=1;k<=n;k=k+1)
    {
        for(i=1;i<n-k;i=i+1)
            tmp=tmp+1;
        for(i=1;i<=2*k-1;i=i+1)
            tmp=tmp+2;
        tmp=2*tmp;
    }
}
