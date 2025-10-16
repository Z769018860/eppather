void insert(int data,int len)
{
    int a[5];
    int k=0;
    int i;
    while (a[k]<data)
        k=k+1;
    for (i=len;i>k;i=i-1)
        a[i]=a[i-1];
    a[k]=data;
    return;
}
