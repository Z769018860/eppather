#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,m,q,fa[Maxn+5],g[Maxn+5],d[Maxn+5];
inline int Find(int x)
{
    if(fa[x]==x) return x;
    int k=Find(fa[x]); d[x]=(d[x]+d[fa[x]])%m;
    return fa[x]=k;
}
inline void exgcd(int a,int b,int &x,int &y)
{
    if(!b) {x=1,y=0; return;}
    exgcd(b,a%b,y,x),y=y-a/b*x;
}

int main()
{
    

    n=read(),m=read(),q=read();
    For(i,1,n) fa[i]=i,g[i]=m;
    while(q--)
    {
        int op=read(),x=read(),y=read(),k=read();
        if(op==1)
        {
            int fx=Find(x),fy=Find(y);
            if(fx==fy)
            {
                int res=(1ll*d[x]+d[y]+k)%m;
                
                g[fx]=__gcd(g[fx],__gcd(k*2%m,res));
            }
            else
            {
                fa[fx]=fy,d[fx]=(1ll*d[x]+d[y]+k)%m;
                g[fy]=__gcd(g[fy],__gcd(g[fx],k*2%m));
            }
        }
        else
        {
            int b=read(),c=read(),fx=Find(x),fy=Find(y),g=::g[fx];
            b%=g; int gcd=__gcd(g,b);
            
            k=(1ll*d[x]+d[y]-k)%g; k=(k+g)%g;
            if(fx!=fy || k%gcd) {puts("0"); continue;}
            k/=gcd,b/=gcd,g/=gcd;
            int p,q; exgcd(b,g,p,q); p=(1ll*p*k%g+g)%g; c--;
            if(c<p) puts("0");
            else printf("%d\n",(c-p)/g+1);
        }
    }
    return 0;
}