#include<stdio.h>
int n;
int main()
{
    scanf("%d",&n);
    printf("%d\n",++n);
    for(int i=1;i<=n;i++)
    {
        printf("%d ",((n^i)&1?n-i+1:n+i)>>1);
    }
    puts("");
    return 0;
}