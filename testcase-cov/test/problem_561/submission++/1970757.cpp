#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e5,Mod=998244353;

int n,m,q,pr[Maxn+5],tot,a[Maxn+5],qr[Maxn+5];
int b[Maxn+5],s;
map<int,int> f,h;

inline void Divide(int x)
{
    For(i,1,tot) while(x%pr[i]==0) x/=pr[i];
    for(int i=2;i*i<=x;++i) if(x%i==0)
        {pr[++tot]=i; while(x%i==0) x/=i;}
    if(x>1) pr[++tot]=x;
}
inline void dfs(int x,int id)
{
    if(id>tot) {a[++m]=x; return;}
    while(x<=n) {dfs(x,id+1); if(1ll*x*pr[id]>n) break; x*=pr[id];}
}
const int iv6=(Mod+1)/6;
inline int S(int x) {return 1ll*x*(x+1)%Mod*(x+x+1)%Mod*iv6%Mod;}

int main()
{
    

    cin>>n>>m>>q;
    For(i,1,m) {int p,x; cin>>p>>x; h[p]=(h[p]+x)%Mod,Divide(p);}
    For(i,1,q) cin>>qr[i],Divide(qr[i]); m=0;
    sort(pr+1,pr+tot+1),dfs(1,1),sort(a+1,a+m+1);
    for(int l=1,r;l<=n;l=r+1) r=n/(n/l),b[++s]=n/l; sort(b+1,b+s+1);
    For(i,1,s) f[b[i]]=S(b[i]); For(j,1,tot) Rof(i,s,1)
        f[b[i]]=(f[b[i]]+1ll*(Mod-f[b[i]/pr[j]])*pr[j]%Mod*pr[j])%Mod;
    For(i,1,tot) For(j,1,m) if(a[j]%pr[i]==0)
        h[a[j]]=(h[a[j]]+1ll*h[a[j]/pr[i]]*pr[i])%Mod;
    For(i,1,m) h[a[i]]=1ll*h[a[i]]*f[n/a[i]]%Mod;
    For(i,1,tot) Rof(j,m,1) if(1ll*a[j]*pr[i]<=n)
        h[a[j]]=(h[a[j]]+1ll*h[a[j]*pr[i]]*pr[i])%Mod;
    For(i,1,q) printf("%d\n",h[qr[i]]);
    return 0;
}