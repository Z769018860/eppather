#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
typedef vector<int> vec;
const int Maxn=2e5+50,Mod=998244353;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,m,ans;
vec v[Maxn+5],w[Maxn+5],f[Maxn+5];

struct Poly
{
    const int g=3;
    int rev[Maxn*4+5],F[Maxn*4+5],G[Maxn*4+5],lim,len;
    inline void Reverse(int *A) {For(i,0,lim-1) if(i<rev[i]) swap(A[i],A[rev[i]]);}
    inline void NTT(int *A,int opt)
    {
        int ninv=Pow(lim,Mod-2); Reverse(A);
        for(int i=2,mid=1;i<=lim;i<<=1,mid<<=1)
        {
            int wi=Pow(g,(Mod-1)/i);
            if(opt==-1) wi=Pow(wi,Mod-2);
            for(int j=0;j<lim;j+=i)
            {
                int w=1;
                for(int k=0;k<mid;++k)
                {
                    int f=A[j+k],t=1ll*w*A[j+k+mid]%Mod;
                    A[j+k]=(f+t)%Mod,A[j+k+mid]=(f-t+Mod)%Mod;
                    w=1ll*w*wi%Mod;
                }
            }
        }
        if(opt==-1) For(i,0,lim-1) A[i]=1ll*A[i]*ninv%Mod;
    }
    inline vec Add(vec A,vec B)
    {
        if(A.size()<B.size()) swap(A,B);
        for(int i=0;i<B.size();++i) A[i]=(A[i]+B[i])%Mod;
        return A;
    }
    inline vec Mul(vec A,vec B)
    {
        int siz=A.size()+B.size()-1;
        lim=1,len=0; vec C(siz);
        while(lim<A.size()+B.size()) lim<<=1,len++;
        For(i,0,lim-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<len-1);
        For(i,0,lim-1) F[i]=(i<A.size()?A[i]:0),G[i]=(i<B.size()?B[i]:0);
        NTT(F,1),NTT(G,1);
        For(i,0,lim-1) F[i]=1ll*F[i]*G[i]%Mod;
        NTT(F,-1);
        for(int i=0;i<siz;++i) C[i]=F[i];
        return C;
    }
} P;

inline vec dfs(int id,int l,int r)
{
    if(l==r) {int p=v[id][l]; return {(1-p+Mod)%Mod,p};}
    int mid=(l+r)>>1; return P.Mul(dfs(id,l,mid),dfs(id,mid+1,r));
}

int main()
{
    

    cin>>n>>m; For(i,1,m)
    {
        int a,x,y; cin>>a>>x>>y;
        int p=1ll*x*Pow(y,Mod-2)%Mod;
        ans=(ans+p)%Mod,v[a].push_back(p);
    } f[0].push_back(1);
    For(i,0,n+50)
    {
        int sz=v[i].size();
        if(!sz) w[i]={1}; else w[i]=dfs(i,0,sz-1);
    }
    For(i,0,n+50) if(!f[i].empty())
    {
        int sz=f[i].size();
        For(j,0,sz-1) ans=(ans+1ll*j*f[i][j])%Mod;
        vec res=P.Mul(f[i],w[i]); sz=res.size();
        f[i+1].resize((sz-1)/2+1);
        For(j,0,sz-1) (f[i+1][j/2]+=res[j])%=Mod;
    }
    cout<<ans<<endl;
    return 0;
}