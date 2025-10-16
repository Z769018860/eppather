#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define clr(f,n) memset(f,0,sizeof(int)*(n))
#define cpy(f,g,n) memcpy(f,g,sizeof(int)*(n))
#define rev(a,n) reverse(a,a+n)
#define bceil(n) (1<<__lg(n-1)+1)
using namespace std;
int read(){
    int a=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') a=(a<<3)+(a<<1)+(ch^'0'),ch=getchar();
    return a;
} 
void write(int a){
    if(a>9) write(a/10);putchar(a%10+'0');
}
const int MAXN=1e6+10,P=998244353,G=3,Gi=332748118,Img=86583718;
int l,_lg_l,r[MAXN],inv[MAXN],sav[MAXN<<1],Wn[MAXN<<1];
ll qpow(ll a,ll b=P-2){
    if(a==1) return 1;ll ans=1;
    while(b){if(b&1) ans=ans*a%P;a=a*a%P;b>>=1;}
    return ans;
}
void Init(int lim){
    l=bceil(lim),_lg_l=__lg(l);int W=qpow(G,(P-1)/l);Wn[l>>1]=1;
    for(int i=0;i<l;i++) r[i]=(r[i>>1]>>1)|((i&1)?l>>1:0);
    for(int i=(l>>1)+1;i<l;i++) Wn[i]=1ll*Wn[i-1]*W%P;
    for(int i=(l>>1)-1;i;i--) Wn[i]=Wn[i<<1];
}
void px(int *A,int *B,int n){for(int i=0;i<n;i++) A[i]=1ll*A[i]*B[i]%P;} 
void NTT(int *A,int lim,int type){
    static ull f[MAXN<<1];if(type-1) rev(A+1,lim-1);
    for(int i=0,u=_lg_l-__lg(lim);i<lim;i++) f[i]=A[r[i]>>u];
    for(int mid=1;mid<lim;mid<<=1){
        for(int j=0;j<lim;j+=mid+mid){
            for(int k=0,x;k<mid;k++)
                x=Wn[mid+k]*f[j|mid|k]%P,f[j|mid|k]=f[j|k]+P-x,f[j|k]+=x;
        }if(mid==(1<<10)){for(int i=0;i<lim;i++) f[i]%=P;}
    }if(type-1){
        ull inv=P-(P-1)/lim;for(int i=0;i<lim;i++) A[i]=f[i]%P*inv%P;
    }else for(int i=0;i<lim;i++) A[i]=f[i]%P;
}
void mul(int *A,int *B,int la,int lb){
    int lim=bceil(la+la);cpy(sav,B,lim);clr(sav+la,lim-la);
    NTT(A,lim,1);NTT(sav,lim,1);px(A,sav,lim);NTT(A,lim,-1);
    clr(A+lb,lim-lb);clr(sav,lim);
} 
void invp(int *A,int lim){
    int n=bceil(lim);static int w[MAXN<<1],r[MAXN<<1];w[0]=qpow(A[0]);
    for (int ln=2;ln<=n;ln<<=1){
        cpy(r,w,ln>>1);cpy(sav,A,ln);
        NTT(sav,ln,1);NTT(r,ln,1);px(r,sav,ln);NTT(r,ln,-1);clr(r,ln>>1);
        cpy(sav,w,ln);NTT(sav,ln,1);NTT(r,ln,1);px(r,sav,ln);NTT(r,ln,-1);
        for(int i=ln>>1;i<ln;i++) w[i]=(w[i]*2ll-r[i]+P)%P;
    }cpy(A,w,lim);clr(sav,n);clr(w,n);clr(r,n);
}
void mof(int *A,int *B,int n,int m){
    static int q[MAXN<<1],t[MAXN<<1],_s[MAXN]; 
    int l=n-m+1;cpy(_s,B,m);rev(B,m);cpy(q,B,l);rev(B,m);
    rev(A,n);cpy(t,A,l);rev(A,n);invp(q,l);
    mul(q,t,l,l);rev(q,l);mul(B,q,n,n);
    for(int i=0;i<m-1;i++) A[i]=(A[i]-B[i]+P)%P;
    clr(B+m-1,l);cpy(B,_s,m);clr(B+m,n-m);clr(q,n);clr(t,n);
}
void deriv(int *A,int lim){
    for(int i=1;i<lim;i++) A[i-1]=1ll*A[i]*i%P;A[lim-1]=0;
}void inv_init(int lim){
    inv[1]=1;for(int i=2;i<=lim;i++) inv[i]=1ll*inv[P%i]*(P-P/i)%P;
}void integ(int *A,int lim){
    for(int i=lim;i;i--) A[i]=1ll*A[i-1]*inv[i]%P;A[0]=0;
}
void lnp(int *A,int lim){
    static int w[MAXN<<1];cpy(w,A,lim);
    invp(w,lim);deriv(A,lim);mul(A,w,lim,lim);
    integ(A,lim-1);clr(w,lim);
}
void exp(int *A,int lim){
    static int s[MAXN<<1],s2[MAXN<<1];int n=bceil(lim);s2[0]=1;
    for(int ln=2;ln<=n;ln<<=1){ 
        cpy(s,s2,ln>>1);lnp(s,ln);
        for(int i=0;i<ln;i++) s[i]=(A[i]-s[i]+P)%P;
        s[0]=(s[0]+1)%P;mul(s2,s,ln,ln);
    }cpy(A,s2,lim);clr(s,n);clr(s2,n);
}
void power(int *A,int lim,ll k){
    int a,inv,t=0;
    while(A[t]==0) t++;a=qpow(A[t],k);inv=qpow(A[t]);
    if(t*k>lim){clr(A,lim);return;}
    for(int i=0;i+t<lim;i++) A[i]=1ll*A[i+t]*inv%P;
    lnp(A,lim);for(int i=0;i<lim;i++) A[i]=1ll*A[i]*k%P;exp(A,lim);
    for(int i=lim-1-t*k;i>=0;i--) A[i+t*k]=1ll*A[i]*a%P;clr(A,t*k);
}
int sq;random_device rd;mt19937 rnd(rd());
struct Complex{
    ll Re,Im;Complex(ll a=0,ll b=0){Re=a,Im=b;}
    const Complex operator*(const Complex a)const{
        return Complex((Re*a.Re%P+Im*a.Im%P*sq%P)%P,(Re*a.Im%P+Im*a.Re%P)%P);
    }
};
int Cipolla(int n){
    if(!n) return 0;n%=P;
    if(qpow(n,P-1>>1)==P-1) return -1;
    ll a;while(1){
        a=rnd()%P;sq=(a*a%P-n+P)%P;if(qpow(sq,P-1>>1)==P-1) break;
    }Complex ans(1),k(a,1);int b=P+1>>1;
    while(b){if(b&1) ans=ans*k;k=k*k;b>>=1;}
    return ans.Re;
}
void sqrt(int *A,int lim){
    int n=bceil(lim);
    static int s[MAXN<<1],s2[MAXN<<1];
    if(A[0]==1) s[0]=1;
    else{s[0]=Cipolla(A[0]);s[0]=P-s[0]<s[0]?P-s[0]:s[0];}
    for(int ln=2;ln<=n;ln<<=1){
        for(int i=0;i<(ln>>1);i++) s2[i]=(s[i]<<1)%P;
        invp(s2,ln);NTT(s,ln,1);px(s,s,ln);NTT(s,ln,-1);
        for(int i=0;i<ln;i++) s[i]=(A[i]+s[i])%P;mul(s,s2,ln,ln);
    }cpy(A,s,lim);clr(s,n+n);clr(s2,n+n);
}
void cos(int *A,int lim){
    static int S[MAXN];int inv=qpow(2);
    for(int i=0;i<lim;i++) A[i]=1ll*A[i]*Img%P;
    exp(A,lim);cpy(S,A,lim);invp(S,lim);
    for(int i=0;i<lim;i++) A[i]=1ll*(A[i]+S[i])%P*inv%P;
}
void sin(int *A,int lim){
    static int S[MAXN];int inv=qpow(Img<<1);
    for(int i=0;i<lim;i++) A[i]=1ll*A[i]*Img%P;
    exp(A,lim);cpy(S,A,lim);invp(S,lim);
    for(int i=0;i<lim;i++) A[i]=1ll*(A[i]-S[i]+P)%P*inv%P;
}
void arcsin(int *A,int lim){
    static int S[MAXN];cpy(S,A,lim);deriv(S,lim);
    int n=bceil(lim*2);
    NTT(A,n,1);px(A,A,n);NTT(A,n,-1);clr(A+lim,n-lim);
    for(int i=0;i<lim;i++) A[i]=(P-A[i])%P;
    A[0]=(A[0]+1)%P;sqrt(A,lim);invp(A,lim);
    mul(A,S,lim,lim);integ(A,lim);clr(S,lim);
}
void arctan(int *A,int lim){
    static int S[MAXN];cpy(S,A,lim);deriv(S,lim);
    int n=bceil(lim*2);
    NTT(A,n,1);px(A,A,n);NTT(A,n,-1);clr(A+lim,n-lim);
    A[0]=(A[0]+1)%P;invp(A,lim);
    mul(A,S,lim,lim);integ(A,lim);clr(S,lim);
}
int Fac[MAXN],iFac[MAXN];
void Fac_init(int lim){
    Fac[0]=iFac[0]=1;
    for(int i=1;i<=lim;i++) Fac[i]=1ll*Fac[i-1]*i%P,iFac[i]=1ll*iFac[i-1]*inv[i]%P;
}
void mulT(int *A,int *B,int lim){
    rev(B,lim);mul(A,B,lim,lim+lim);
    for(int i=0;i<lim;i++) A[i]=A[lim+i-1];
    clr(A+lim,lim);rev(B,lim);
}
void trans(int *A,int lim,int k){
    static int g[MAXN];g[0]=1;
    for(int i=1;i<lim;i++) g[i]=1ll*g[i-1]*k%P,A[i]=1ll*A[i]*Fac[i]%P;
    for(int i=1;i<lim;i++) g[i]=1ll*g[i]*iFac[i]%P;mulT(A,g,lim);
    for(int i=0;i<lim;i++) A[i]=1ll*A[i]*iFac[i]%P;clr(g,lim);
}
void Stirling(int *A,int lim,int type,int r_c,int k=0){
    static int f[MAXN];lim++;
    if(type==1&&r_c==1){
        int b[20],tot=0,ln=--lim;while(ln) b[++tot]=ln,ln>>=1;
        ln=A[1]=b[tot--];while(tot--){
            cpy(f,A,ln+1);trans(f,ln+1,ln);mul(A,f,ln+1,(ln<<1)+1);
            ln<<=1;if(ln==b[tot+1]) continue;A[ln+1]=A[ln];
            for(int i=ln;i;i--) A[i]=(1ll*A[i]*ln%P+A[i-1])%P;A[0]=1ll*A[0]*ln%P;
            ln++;
        }clr(f,lim+1);
    }else if(type==2&&r_c==1){
        for(int i=0;i<lim;i++) A[i]=qpow(i,lim-1)*iFac[i]%P,f[i]=(i&1?P-1ll:1ll)*iFac[i]%P;
        mul(A,f,lim,lim);clr(f,lim);
    }else{
        cpy(A,(type==1?inv:iFac)+1,lim-1);
        lnp(A,lim);for(int i=0;i<lim;i++) A[i]=1ll*A[i]*k%P;exp(A,lim);
        for(int i=lim-1;i>=k;i--) A[i]=A[i-k];clr(A,k);
        for(int i=0;i<lim;i++) A[i]=1ll*A[i]*iFac[k]%P*Fac[i]%P;
    }
}
void comp(int *A,int *B,int n,int m){
    int L=sqrt(n)+1,lim=bceil(n+n);
    static int B1[210][MAXN],B2[210][MAXN],R[MAXN],C[MAXN];
    B1[0][0]=B2[0][0]=1;cpy(B1[1],B,m);NTT(B,lim,1);
    for(int i=2;i<=L;i++){
        int *Bp=B1[i-1],*Bn=B1[i];NTT(Bp,lim,1);
        for(int j=0;j<lim;j++) Bn[j]=1ll*B[j]*Bp[j]%P;
        NTT(Bp,lim,-1);NTT(Bn,lim,-1);clr(Bn+n,lim-n);
    }cpy(B2[1],B1[L],n);int *Bl=B1[L];NTT(Bl,lim,1);
    for(int i=2;i<L;i++){
        int *Bp=B2[i-1],*Bn=B2[i];NTT(Bp,lim,1);
        for(int j=0;j<lim;j++) Bn[j]=1ll*Bl[j]*Bp[j]%P;
        NTT(Bp,lim,-1);NTT(Bn,lim,-1);clr(Bn+n,lim-n);
    }NTT(Bl,lim,-1);
    for(int i=0;i<L;i++){
        clr(C,lim);
        for(int j=0;j<L;j++)for(int k=0;k<n;k++) C[k]=(C[k]+1ll*A[i*L+j]*B1[j][k])%P;
        NTT(C,lim,1);NTT(B2[i],lim,1);for(int j=0;j<lim;j++) C[j]=1ll*C[j]*B2[i][j]%P;
        NTT(C,lim,-1);for(int i=0;i<n;i++) R[i]=(R[i]+C[i])%P; 
    }cpy(A,R,n);
}
void print(int *A,int lim){
    for(int i=0;i<lim;i++) write(A[i]),putchar(' ');
    putchar('\n');
}
int n,k,a[MAXN],b[MAXN];
int main(){
    n=read()+1;k=read();Init(n<<1);inv_init(n);
    for(int i=0;i<n;i++) a[i]=read();cpy(b,a,n);b[0]=2;
    sqrt(a,n);invp(a,n);integ(a,n);exp(a,n);
    for(int i=0;i<n;i++) a[i]=(b[i]-a[i]+P)%P;
    lnp(a,n);a[0]=1;lnp(a,n);
    for(int i=0;i<n;i++) a[i]=1ll*a[i]*k%P;
    exp(a,n);deriv(a,n);print(a,n-1);
    return 0;
}