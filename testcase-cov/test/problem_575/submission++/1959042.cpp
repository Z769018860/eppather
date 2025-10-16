#include<bits/stdc++.h>
#define int ll
#define ll long long
#define db double
#define MP make_pair
#define vec vector<int>
#define pii pair<int,int>
#define pb emplace_back
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define CLK (double)clock()/CLOCKS_PER_SEC
using namespace std;
mt19937 rnd(time(0));
int read(){
    int x=0,f=1;char c=getchar();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
    return x*f;
}
void write(int x){
    if(x<0){putchar('-');write(-x);}
    else {
        if(x>9)write(x/10);
        putchar(x%10+'0');
    }
}
const int N=1e5+5,mod=998244353,g=3;
int n,fac[N],inv[N],cnt[N],f[N];
char s[N];
int Qpow(int b,int p){
    int res=1ll;
    while(p){
        if(p&1)(res*=b)%=mod;
        (b*=b)%=mod;p>>=1;
    }
    return res;
}
struct Poly{
    int lim=1,len=0,rev[N<<2],F[N<<2],G[N<<2];
    void init(int n){
        lim=1,len=0;while(lim<=n*2)lim<<=1,len++;
        for(int i=0;i<lim;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<len-1);
    }
    void NTT(int *f,int op){
        for(int i=0;i<lim;i++)if(i<rev[i])swap(f[i],f[rev[i]]);
        for(int h=2;h<=lim;h<<=1){
            int wi=Qpow(g,(mod-1)/h);
            if(op==-1)wi=Qpow(wi,mod-2);
            for(int j=0;j<lim;j+=h){
                int w=1;
                for(int k=j;k<j+h/2;k++){
                    int u=f[k],t=f[k+h/2]*w%mod;
                    f[k]=(u+t)%mod,f[k+h/2]=(u-t+mod)%mod;
                    w=w*wi%mod;
                }
            }
        }
        if(op==1)return ;int ivn=Qpow(lim,mod-2);
        for(int i=0;i<lim;i++)f[i]=f[i]*ivn%mod;
    }
    void Mul(int *A,int *B,int *C){
        
        
        
        for(int i=0;i<lim;i++)F[i]=A[i],G[i]=B[i];
        NTT(F,1),NTT(G,1);
        for(int i=0;i<lim;i++)F[i]=F[i]*G[i]%mod;
        NTT(F,-1);
        for(int i=0;i<lim;i++)C[i]=F[i];
    }
}P;
int sgn(int i){return (i&1)?mod-1:1;}
void init(int n){
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
    inv[n]=Qpow(fac[n],mod-2);for(int i=n-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
}
int calcC(int n,int m){if(n<m||m<0)return 0;return fac[n]*inv[m]%mod*inv[n-m]%mod;}
int A[N<<2],B[N<<2],C[N<<2];
void Solve(int l,int r){
    if(l==r)return ;
    int mid=l+r>>1;Solve(l,mid);
    P.init(r-l);
    for(int i=0;i<P.lim;i++)A[i]=B[i]=C[i]=0;
    for(int i=l;i<=mid;i++)if(s[i]!='<')A[i-l]=f[i]*sgn(cnt[i])%mod;
    for(int i=l;i<=r;i++)B[i-l]=inv[i-l];
    P.Mul(A,B,C);
    for(int i=mid+1;i<=r;i++)(f[i]+=C[i-l]*sgn(cnt[i-1])%mod)%=mod;
    Solve(mid+1,r);
}
void MAIN(){
    scanf("%s",s+1);
    n=strlen(s+1),init(n+1);
    for(int i=1;i<=n;i++)cnt[i]=cnt[i-1]+(s[i]=='>');
    f[0]=1;Solve(0,n+1);cout<<f[n+1]*fac[n+1]%mod<<"\n";
}
signed main(){
    
    
    int T=1;while(T--)MAIN();
    
    return 0;
}
