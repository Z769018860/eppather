#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6+5,Mod=998244353;

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

int n,fac[Maxn+5],inv[Maxn+5]; char s[Maxn+5];
int f[Maxn+5],cnt[Maxn+5];
inline int sgn(int x) {return (x&1)?Mod-1:1;}

struct Poly
{
    const int g=3;
    int lim=1,len,rev[Maxn+5],A[Maxn+5],B[Maxn+5];
    inline void GetLim(int n)
    {
        lim=1,len=0; while(lim<=n) lim<<=1,len++;
        For(i,0,lim-1) rev[i]=(rev[i>>1]>>1)|((i&1)<<len-1);
    }
    inline void NTT(int *A,int opt)
    {
        int ninv=Pow(lim,Mod-2);
        For(i,0,lim-1) if(i<rev[i]) swap(A[i],A[rev[i]]);
        for(int l=2,mid=1;l<=lim;l<<=1,mid<<=1)
        {
            int wi=Pow(g,(Mod-1)/l);
            if(opt==-1) wi=Pow(wi,Mod-2);
            for(int j=0;j<lim;j+=l) for(int k=0,w=1;k<mid;++k,w=1ll*w*wi%Mod)
            {
                int f=A[j+k],t=1ll*A[j+k+mid]*w%Mod;
                A[j+k]=(f+t)%Mod,A[j+k+mid]=(f-t+Mod)%Mod;
            }
        }
        if(opt==-1) For(i,0,lim-1) A[i]=1ll*A[i]*ninv%Mod;
    }
    inline void GetMul(int *F,int *G,int *H)
    {
        For(i,0,lim-1) A[i]=F[i],B[i]=G[i];
        NTT(A,1),NTT(B,1);
        For(i,0,lim-1) A[i]=1ll*A[i]*B[i]%Mod;
        NTT(A,-1); For(i,0,lim-1) H[i]=A[i];
    }
} P;

int A[Maxn+5],B[Maxn+5],C[Maxn+5];
inline void dfs(int l,int r)
{
    if(l==r) return;
    int mid=(l+r)>>1; dfs(l,mid);
    int s1=mid-l,s2=r-l; P.GetLim(s1+s2);
    For(i,0,P.lim-1) A[i]=B[i]=C[i]=0;
    For(i,l,mid) if(s[i]!='<') A[i-l]=1ll*f[i]*sgn(cnt[i])%Mod;
    For(i,0,s2) B[i]=inv[i];
    P.GetMul(A,B,C);
    For(i,mid+1,r) f[i]=(f[i]+1ll*C[i-l]*sgn(cnt[i-1]))%Mod;
    dfs(mid+1,r);
}

int main()
{
    

    scanf("%s",s+1),n=strlen(s+1),fac[0]=inv[0]=1;
    For(i,1,Maxn) fac[i]=1ll*fac[i-1]*i%Mod;
    inv[Maxn]=Pow(fac[Maxn],Mod-2);
    Rof(i,Maxn-1,1) inv[i]=1ll*inv[i+1]*(i+1)%Mod;
    For(i,1,n) cnt[i]=cnt[i-1]+(s[i]=='>');
    f[0]=1,dfs(0,n+1);
    
    
    
    
    
    
    int ans=1ll*f[n+1]*fac[n+1]%Mod;
    cout<<ans<<endl;
    return 0;
}