#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define sz(x) ((int)x.size())
#define ll long long
using namespace std;
const int N=55,M=1005,P=998244353;
int a,b,d,k,m,dp[N],fac[M],inv[M];
ll n;
int bp(int x,ll y){
	int r=1;
	for(;y;y=y>>1,x=1ll*x*x%P) if(y&1) r=1ll*r*x%P;
	return r;
}
namespace NTT{
    const int N=(1<<20);
	int n,f[N],g[N],w[N],tr[N];
	void ntt(int f[],bool o){
		for(int i=0;i<n;i++) if(tr[i]>i) swap(f[i],f[tr[i]]);
		for(int p=1;p<n;p=p<<1){
			w[0]=1,w[1]=bp(3,(P-1)/(2*p));
			if(o) w[1]=bp(w[1],P-2);
			for(int i=2;i<p;i++) w[i]=1ll*w[i-1]*w[1]%P;
			for(int l=0;l<n;l+=p*2){
				for(int t=l;t<l+p;t++){
					int tmp=1ll*w[t-l]*f[t+p]%P;
					f[t+p]=f[t]-tmp;
					if(f[t+p]<0) f[t+p]+=P;
					f[t]+=tmp;
					if(f[t]>=P) f[t]-=P;
				}
			}
		}
	}
	vector<int> mul(const vector<int>&a,const vector<int>&b){
		if(a.size()==0||b.size()==0) return {};
		int t=a.size()+b.size()-1;
		for(n=1;n<t;n=n<<1);
		for(int i=0;i<n;i++) f[i]=i<a.size()?a[i]:0;
		for(int i=0;i<n;i++) g[i]=i<b.size()?b[i]:0;		
		for(int i=1;i<n;i++) tr[i]=(tr[i>>1]>>1)+(i&1?n>>1:0);
		ntt(f,0),ntt(g,0);
		for(int i=0;i<n;i++) f[i]=1ll*f[i]*g[i]%P;
		ntt(f,1);
		vector<int> res(t);
		int tmp=bp(n,P-2);
		for(int i=0;i<t;i++) res[i]=1ll*f[i]*tmp%P;
		return res;
	}
}
using NTT::mul;
void Inc(int&x,int y){
    if((x+=y)>=P) x-=P;
}
void Dec(int&x,int y){
    if((x-=y)<0) x+=P;
}
vector<int> Mul(const vector<int>&a,const vector<int>&b){
    vector<int> c=mul(a,b);
    rep(i,d,sz(c)-1) Inc(c[i%d],c[i]);
    c.resize(d);
    return c;
}
vector<int> Add(vector<int> a,vector<int> b){
    vector<int> c;
    a.resize(d),b.resize(d),c.resize(d);
    rep(i,0,d-1) c[i]=(a[i]+b[i])%P;
    return c;
}
struct T{
    int x;
    ll y;
    bool operator<(const T&o)const{
        if(x!=o.x) return x<o.x;
        return y<o.y;
    }
}p[N];
int C(ll x,int y){
    int tmp=1;
    for(ll i=x-y+1;i<=x;i++) tmp=tmp*(i%P)%P;
    return 1ll*tmp*inv[y]%P;
}
vector<int> v1[M],v2[65],v3[65];
int main(){
    
    scanf("%d%d",&a,&b);
    swap(a,b);
    scanf("%lld%d%d%d",&n,&d,&m,&k);
    rep(i,1,k) scanf("%d%lld",&p[i].x,&p[i].y);
    fac[0]=inv[0]=1;
    rep(i,1,m) fac[i]=1ll*fac[i-1]*i%P,inv[i]=bp(fac[i],P-2);
    sort(p+1,p+k+1);
    dp[0]=1;
    rep(i,1,k){
        dp[i]=1ll*C(p[i].x+p[i].y,p[i].x)*bp(a,p[i].x)%P*bp(b,p[i].y)%P;
        rep(j,1,i-1) if(p[j].y<=p[i].y) 
            Dec(dp[i],1ll*dp[j]*C(p[i].x+p[i].y-p[j].x-p[j].y,p[i].x-p[j].x)%P*bp(a,p[i].x-p[j].x)%P*bp(b,p[i].y-p[j].y)%P);
    }
    v1[0]={1},v1[1]={a,b};
    rep(i,2,d) v1[i]=Mul(v1[i-1],v1[1]);
    v2[0]=v1[d];
    rep(i,1,60) v2[i]=Mul(v2[i-1],v2[i-1]);
    v3[0]={1};
    rep(i,1,60) v3[i]=Add(v3[i-1],Mul(v3[i-1],v2[i-1]));
    int ans=0;
    rep(i,0,k) if(p[i].x+p[i].y<=n){
        ll nn=n-p[i].x-p[i].y,ii=(d-p[i].x%d)%d,jj=(d-p[i].y%d)%d;
        ii=(ii+jj)%d;
        if(nn<ii) continue;
        ll l=(nn-ii)/d+1;
        vector<int> A={0};
        per(i,60,0) if(l>=(1ll<<i)){
            l-=(1ll<<i);
            A=Add(Mul(A,v2[i]),v3[i]);
        }
        A=Mul(A,v1[ii]);
        if(i) Dec(ans,1ll*dp[i]*A[jj]%P);
        else Inc(ans,A[jj]);
        
    }
    printf("%d\n",ans);
}
