#include<bits/stdc++.h>
#define N 300010
#define mod 998244353
#define For(i,a,b) for(register int i=a;i<=b;i++)
#define Down(i,a,b) for(register int i=a;i>=b;i--)
using namespace std;
int n,m,f[N],g[N],c[N],d[N],pos[N],h[N],len,cnt[N];
int inv[N],w[20][N>>1],iw[20][N>>1],rt=3,invlen;
inline int addm(int x){return x>=mod?x-mod:x;}
inline int add(int &x,int y){x+=y;if(x>=mod) x-=mod;}
inline int read()
{
    register int x=0,c=getchar();
    while(!isdigit(c)) c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    return x;
}

inline int fpow(int a,int b)
{
    int res=1;
    while(b) {if(b&1) res=1ll*res*a%mod;a=1ll*a*a%mod,b>>=1;}
    return res;
}

inline void init()
{
    For(i,1,18)
    {
        int x=fpow(rt,(mod-1)/(1<<i));w[i][0]=1;
        int y=fpow(x,mod-2);iw[i][0]=1;
        For(j,1,1<<i-1)
        {
            w[i][j]=1ll*w[i][j-1]*x%mod;
            iw[i][j]=1ll*iw[i][j-1]*y%mod;
        }
    }
    return;
}

inline void NTT(int *f,int len,int flag)
{
    For(i,1,len-2) if(i < pos[i]) swap(f[i],f[pos[i]]);
    for(int l=2,b=1;l<=len;l<<=1,b++)
        for(int i=0;i<len;i+=l) For(j,i,i+(l>>1)-1)
        {
            int g=f[j],h=1ll*(flag?w[b][j-i]:iw[b][j-i])*f[j|(l>>1)]%mod;
            f[j]=addm(g+h),f[j|(l>>1)]=addm(g+mod-h);
        }
    if(!flag) For(i,0,len-1) f[i]=1ll*f[i]*invlen%mod;
    return;
}

inline void calc_inv(int *a,int *b,int n)
{
    if(n == 1) {b[0]=fpow(a[0],mod-2);return;}
    calc_inv(a,b,n+1>>1),len=1;
    while(len < n<<1) len<<=1;
    invlen=fpow(len,mod-2);
    For(i,1,len-2) pos[i]=pos[i>>1]>>1|(i&1?len>>1:0);
    For(i,0,n-1) c[i]=a[i];
    For(i,n,len) c[i]=0;
    NTT(b,len,true),NTT(c,len,true);
    For(i,0,len-1) b[i]=1ll*b[i]*(mod+2-1ll*b[i]*c[i]%mod)%mod;
    NTT(b,len,false);
    For(i,n,len) b[i]=0;
    return;
}

inline void calc_deri(int *f,int n)
{
    For(i,1,n) f[i-1]=1ll*f[i]*i%mod;
    return;
}

inline void calc_calcu(int *f,int n)
{
    Down(i,n,0) f[i+1]=1ll*f[i]*inv[i+1]%mod;
    return;
}

inline void calc_ln(int *f,int n)
{
    memset(g,0,sizeof(g));
    calc_inv(f,g,n),calc_deri(f,n);
    NTT(f,len,true),NTT(g,len,true);
    For(i,0,len-1) f[i]=1ll*f[i]*g[i]%mod;
    NTT(f,len,false),calc_calcu(f,n),f[0]=0;
    For(i,n,len) f[i]=0;
    return;
}

inline void calc_exp(int *a,int *b,int n)
{
    if(n == 1) {b[0]=1;return;}
    calc_exp(a,b,n+1>>1);
    For(i,0,n-1) d[i]=b[i];
    For(i,n,len) d[i]=0;
    calc_ln(d,n),add(d[0],mod-1);
    For(i,0,n-1) d[i]=addm(a[i]+mod-d[i]);
    NTT(b,len,true),NTT(d,len,true);
    For(i,0,len-1) b[i]=1ll*b[i]*d[i]%mod;
    NTT(b,len,false);
    For(i,n,len) b[i]=0;
    return;
}

int main()
{
    n=read(),m=read();
    inv[0]=inv[1]=1,init();
    For(i,2,n) inv[i]=1ll*(mod-mod/i)*inv[mod%i]%mod;
    For(i,1,m)
    {
        int x=read(),y=read();cnt[x]++;
        if(!x) continue;
        if(y) cnt[(min(n/x,y)+1)*x]--;
    }
    For(i,1,n)
    {
        cnt[i]=addm(mod+cnt[i]);
        for(int j=i;j<=n;j+=i)
            add(f[j],1ll*cnt[i]*inv[j/i]%mod);
    }calc_exp(f,h,n+1);
    For(i,1,n) printf("%d\n",h[i]);
    return 0;
}
