#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6,Mod=998244353;

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

int n,m,s,ans,TP;

struct Matrix
{
    int f[2][2];
    inline int&operator()(int a,int b) {return f[a][b];}
} t[Maxn*4+5],idt;
inline Matrix operator*(Matrix a,Matrix b)
{
    Matrix c; memset(c.f,0,sizeof(c.f));
    For(i,0,1) For(j,0,1) For(k,0,1)
        c(i,k)=(c(i,k)+1ll*a(i,j)*b(j,k))%Mod;
    return c;
}
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void push_up(int p) {t[p]=t[ls(p)]*t[rs(p)];}
inline void Modify(int l,int r,int p,int pos,Matrix k)
{
    if(l==r) {t[p]=k; return;}
    int mid=(l+r)>>1;
    if(pos<=mid) Modify(l,mid,ls(p),pos,k);
    else Modify(mid+1,r,rs(p),pos,k);
    push_up(p);
}
inline Matrix Count(int nl,int nr,int l,int r,int p)
{
    if(l<=nl && nr<=r) return t[p];
    int mid=(nl+nr)>>1; Matrix res=idt;
    if(l<=mid) res=res*Count(nl,mid,l,r,ls(p));
    if(r>mid) res=res*Count(mid+1,nr,l,r,rs(p));
    return res;
}
inline Matrix Get(int x)
{
    Matrix res; res(0,0)=x;
    res(0,1)=res(1,0)=1,res(1,1)=0; return res;
}

int main()
{
    

    n=read(),m=read(),TP=read(),s=n+m,idt(0,0)=idt(1,1)=1;
    For(i,1,n) Modify(1,s,1,i,Get(read()));
    while(m--)
    {
        int op=read(),x,y;
        if(op==1) x=read()^ans,Modify(1,s,1,++n,Get(x));
        else
        {
            x=read()^ans,y=read()^ans;
            int s1=0,s2=0; auto res=Count(1,s,x,y,1);
            s1=res(0,0),s2=res(1,0),ans=s1^s2;
            printf("%d %d\n",s1,s2); if(!TP) ans=0;
        }
    }
    return 0;
}