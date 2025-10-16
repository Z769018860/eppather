#include<bits/stdc++.h>
#define pii pair<int,int>
#define rs resize
using namespace std;
const int mod=998244353,phi=998244352;
const int polysize=262144;
inline int mul(int x,int y,int mod){return 1ll*x*y%mod;}
inline int add(int x,int y,int mod){return x+y>=mod?x+y-mod:x+y;}
inline int sub(int x,int y,int mod){return x<y?x+mod-y:x-y;}
inline int qpow(int x,int y,int mod){int ret=1;while(y){if(y&1)ret=mul(ret,x,mod);x=mul(x,x,mod),y>>=1;}return ret;}
inline int inv(int x,int mod){return qpow(x,mod-2,mod);}
int exgcd(int a,int b,int &x,int &y){if(b==0){x=1,y=0;return a;}int ret=exgcd(b,a%b,y,x);y-=(a/b)*x;return ret;}
unordered_map<int,int>mp;
inline int bsgs(int a,int b,int mod)
{
    mp.clear();
    int qwq=(int)ceil(sqrt(mod));
    int j=1;
    for(register int i=0;i<qwq;i++,j=mul(j,a,mod))if(!mp.count(j))mp[j]=i+1;
    j=inv(j,mod);
    for(register int i=0,k=1;i<=qwq;i++,k=mul(k,j,mod))
    {
        int t=mul(k,b,mod);
        if(mp.count(t))return i*qwq+mp[t]-1;
    }
    return -1;
}
int facs[70],fcnt;
inline int getroot(int mod)
{
    if(mod==998244353)return 3;
    fcnt=0;
    int k=mod-1;
    for(register int i=2;i*i<=k;i++)
        if(k%i==0)
        {
            facs[++fcnt]=i;
            while(k%i==0)k/=i;
        }
    if(k!=1)facs[++fcnt]=k;
    for(register int i=2;i<=mod;i++)
    {
        bool flag=true;
        for(register int j=1;j<=fcnt;j++)
            if(qpow(i,(mod-1)/facs[j],mod)==1)
            {
                flag=false;
                break;
            }
        if(flag)return i;
    }
    return -1;
}
inline pii Sqrt(int b,int mod)
{
    int g=getroot(mod);
    int t=bsgs(g,b,mod);
    int phi=mod-1,x,y;
    int gcd=exgcd(2,phi,x,y);
    if(t%gcd!=0)return{-1,-1};
    x=x*(t/gcd);
    int phii=phi/gcd;
    x=(x%phii+phii)%phii;
    int u=qpow(g,x,mod);
    int v=sub(mod,u,mod);
    if(u>v)swap(u,v);
    return{u,v};
}
typedef vector<int>vi;
int rev[polysize+100];
inline void pre(int len){for(register int i=0;i<len;i++)rev[i]=(rev[i>>1]>>1)|(i&1?(len>>1):0);}
inline int getlen(int n){return 1<<(int)ceil(log2(n+1));}
int wpow[polysize+100],invwpow[polysize+100];
void initwpow()
{
    wpow[0]=invwpow[0]=1,wpow[1]=qpow(3,(mod-1)/polysize,mod),invwpow[1]=qpow(332748118,(mod-1)/polysize,mod);
    for(int i=2;i<polysize;i++)wpow[i]=mul(wpow[i-1],wpow[1],mod),invwpow[i]=mul(invwpow[i-1],invwpow[1],mod);
}
int nttlaslen=-1;
inline void NTT(int a[],int len,int opt)
{
    if(len!=nttlaslen)nttlaslen=len,pre(len);
    for(register int i=0;i<len;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
    int w1,w0,x,y;
    for(register int i=1,t=polysize>>1;i<len;i<<=1,t>>=1)
        for(register int l=0,r=i<<1;l<len;l+=r)
            for(register int j=0,q=0;j<i;j++,q+=t)
            {
                w0=opt==1?wpow[q]:invwpow[q];
                x=a[l|j];
                y=mul(w0,a[l|j|i],mod);
                a[l|j|i]=sub(x,y,mod);
                a[l|j]=add(x,y,mod);
            }
    if(opt==1)return;
    int leninv=inv(len,mod);
    for(register int i=0;i<len;i++)a[i]=mul(a[i],leninv,mod);
}
inline vi fix(vi a,int n){a.rs(n);return a;}
inline vi operator*(vi a,int b){int n=a.size();for(register int i=0;i<n;i++)a[i]=mul(a[i],b,mod);return a;}
inline vi operator*(int b,vi a){int n=a.size();for(register int i=0;i<n;i++)a[i]=mul(a[i],b,mod);return a;}
inline vi operator+(vi a,vi b){if(a.size()<b.size())swap(a,b);int m=b.size();for(register int i=0;i<m;i++)a[i]=add(a[i],b[i],mod);return a;}
inline vi operator-(vi a,vi b){int n=max(a.size(),b.size()),m=b.size();a.rs(n);for(register int i=0;i<m;i++)a[i]=sub(a[i],b[i],mod);return a;}
inline vi operator*(vi a,vi b)
{
    int n=a.size(),m=b.size();
    int len=getlen(n+m);
    a.rs(len);
    b.rs(len);
    NTT(&a[0],len,1);
    NTT(&b[0],len,1);
    for(register int i=0;i<len;i++)a[i]=mul(a[i],b[i],mod);
    NTT(&a[0],len,-1);
    a.rs(n+m-1);
    return a;
}
inline vi Der(vi a){int n=a.size();for(register int i=0;i<n-1;i++)a[i]=mul(a[i+1],i+1,mod);a.pop_back();return a;}
inline vi Int(vi a){a.push_back(0);int n=a.size();for(register int i=n-1;i>=1;i--)a[i]=mul(a[i-1],inv(i,mod),mod);a[0]=0;return a;}
vi polyinv(vi a)
{
    int n=a.size();
    if(n==1)return vi(1,inv(a[0],mod));
    vi b=polyinv(fix(a,n+1>>1));
    return fix(b+b-b*b*a,n);
}
inline vi operator/(vi a,vi b)
{
    int n=a.size(),m=b.size();
    if(n<m)return vi();
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    
    a=fix(a*polyinv(fix(b,n-m+1)),n-m+1);
    reverse(a.begin(),a.end());
    return a;
}
inline vi operator%(vi a,vi b){return fix(a-a/b*b,b.size()-1);}
vi polysqrt(vi a)
{
    int n=a.size();
    if(n==1)return vi(1,Sqrt(a[0],mod).first);
    vi b=fix(polysqrt(fix(a,n+1>>1)),n);
    return fix((b+a*polyinv(b))*(mod+1>>1),n);
}
inline vi polyln(vi a){return Int(fix(Der(a)*polyinv(a),a.size()-1));}
vi polyexp(vi a)
{
    int n=a.size();
    if(n==1)return vi(1,1);
    vi b=polyexp(fix(a,n+1>>1));
    return fix(b*(a-polyln(fix(b,n)))+b,n);
}
inline vi polypow(vi a,int k1,int k2,int k3)
{
    int n=a.size();
    int pos;
    for(pos=0;pos<n;pos++)if(a[pos])break;
    if(1ll*pos*k3>=n)return vi(n,0);
    for(register int i=0;i<n-pos;i++)a[i]=a[i+pos];
    for(register int i=n-pos;i<n;i++)a[i]=0;
    int b=a[0];
    a=a*inv(a[0],mod);
    a=polyexp(polyln(a)*k1)*qpow(b,k2,mod);
    pos=min(1ll*pos*k3,(long long)n);
    for(register int i=n-pos-1;i>=0;i--)a[i+pos]=a[i];
    for(register int i=0;i<pos;i++)a[i]=0;
    return a;
}
typedef vi Poly;
Poly tree[4*polysize+100];
vi pts,ans;
void build(int p,int l,int r)
{
    if(l==r){tree[p]={sub(mod,pts[l],mod),1};return;}
    int mid=l+r>>1;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    tree[p]=tree[p*2]*tree[p*2+1];
}
void solve(Poly f,int p,int l,int r)
{
    f=fix(f%tree[p],(int)tree[p].size()-1);
    if(l==r){ans[l]=f[0];return;}
    int mid=l+r>>1;
    solve(f,p*2,l,mid);
    solve(f,p*2+1,mid+1,r);
}
inline vi eval(Poly f,vi x)
{
    int n=x.size();
    if(!n)return vi();
    ans.rs(n);
    pts=x;
    build(1,0,n-1);
    solve(f,1,0,n-1);
    return ans;
}

int k,k2,k3;
Poly a(0,0);
Poly b(0,0);
int main()
{
    initwpow();
    int n;
    scanf("%d%d",&n,&k);
    a.rs(n+1);
    for(register int i=0;i<=n;i++)scanf("%d",&a[i]);
    k2=k%phi;
    k3=min(k,n);
    b=a;
    b[0]=2;
    a=polyln(b-polyexp(Int(polyinv(polysqrt(a)))));
    a[0]=add(a[0],1,mod);
    a=polypow(a,k,k2,k3);
    a=Der(a);
    for(register int i=0;i<n;i++)printf("%d ",a[i]);
    puts("");
    return 0;
}
