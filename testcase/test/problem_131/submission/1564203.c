#include<stdio.h>
#define maxn 1000010
typedef long long ll;
ll c[maxn];
int n,q;
int lowbit(int x)
{
    return x&(-x);
}
int update(int i,ll a)
{
    while(i<=n)
    {
        c[i]=c[i]+a;
        i=i+lowbit(i);
    }
}
ll sum(int x)
{
    ll ans=0;
    while(x>0)
    {
        ans=ans+c[x];
        x=x-lowbit(x);
    }
    return ans;
}
int main()
{
    int i,a,b=0;
    scanf("%d %d",&n,&q);
    for(i=1; i<=n; i++)
    {
        scanf("%d",&a);
        update(i,a-b);
        b=a;
    }
    while(q--)
    {
        int s,l,r,x;
        scanf("%d",&s);
        if(s==1)
        {
            scanf("%d %d %d",&l,&r,&x);
            update(l,x);
            update(r+1,-x);
        }
        else if(s==2)
        {
            int h;
            scanf("%d",&h);
            printf("%lld\n",sum(h));
        }
    }
}