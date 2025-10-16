#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=5e5,inf=1e9;

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

int n,m,s,cur,fa[Maxn+5]; ll ans;
struct Link{int a,b,c;} h[Maxn+5];
inline int Find(int x) {return fa[x]==x?x:fa[x]=Find(fa[x]);}
inline int Merge(int x,int y)
{x=Find(x),y=Find(y); if(x==y) return 0; fa[x]=y; return 1;}
inline void Check(int mid)
{
    For(i,1,n) fa[i]=i; cur=ans=0; int cnt=0;
    for(int l=1,r=m;l<=r;)
    {
        Link now; bool chk=0;
        if(h[l].c>=mid-h[r].c) now=h[l++];
        else now=h[r--],chk=1,now.c=mid-now.c;
        if(Merge(now.a,now.b))
        {
            ans+=now.c,cur+=chk;
            if(++cnt==s*2) break;
        }
    } ans-=1ll*s*mid;
}

int main()
{
    

    n=read(),m=read(),s=(n-1)/2;
    if(!s) {puts("0"); return 0;}
    For(i,1,m)
    {
        int a=read(),b=read(),c=read();
        h[i]=Link{a,b,c};
    }
    sort(h+1,h+m+1,[&](Link x,Link y){return x.c>y.c;});
    int l=0,r=min(h[1].c*2+1,inf); ll all;
    while(l<=r)
    {
        int mid=(l+r)/2; Check(mid);
        if(cur==s) {cout<<ans<<endl; return 0;}
        if(cur<s) l=mid+1,all=ans; else r=mid-1;
    } cout<<all<<endl;
    return 0;
}