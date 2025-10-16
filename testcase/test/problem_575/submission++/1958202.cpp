#include<bits/stdc++.h>
#define pb push_back
#define MP make_pair
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
typedef long long ll;
template<typename T>void readmain(T &x){
    bool neg=false;unsigned int c=getchar();
    for(;(c^48)>9;c=getchar())if(c=='-')neg=true;
    for(x=0;(c^48)<10;c=getchar())x=(x<<3)+(x<<1)+(c^48);
    if(neg)x=-x;
}
template<typename T>T& read(T &x){readmain(x);return x;}
template<typename T,typename ...Tr>void read(T &x,Tr&... r){readmain(x);read(r...);}
constexpr int N=100005,mod=998244353;
typedef vector<int> PN;
constexpr int maxt=1<<18;
int wn[maxt+5],temA[maxt+5],temB[maxt+5];
void add(int &x,int y){x+=y;if(x>=mod)x-=mod;}
int ADD(int x,int y){return (x+y>=mod?x+y-mod:x+y);}
int MUL(int x,int y){return (ll)x*y%mod;}
ll power(ll a,ll b){
	ll res=1,tmp=a;
	while(b){
		if(b&1)res=res*tmp%mod;
		tmp=tmp*tmp%mod;
		b>>=1;
	}
	return res;
}
void NTTPre(){
	int x=power(3,(mod-1)/maxt);
	wn[maxt>>1]=1;
	for (int i=(maxt>>1)+1;i<maxt;i++) wn[i]=MUL(wn[i-1],x);
	for (int i=(maxt>>1)-1;i;i--) wn[i]=wn[i<<1];
}
void NTT(int *a,int n,int f){
	if (f>0){
		for (int k=n>>1;k;k>>=1)
			for (int i=0;i<n;i+=k<<1)
				for (int j=0;j<k;j++){
					int x=a[i+j],y=a[i+j+k];
					a[i+j+k]=MUL(x+mod-y,wn[k+j]);
					a[i+j]=ADD(x,y);
				}
	} else {
		for (int k=1;k<n;k<<=1)
			for (int i=0;i<n;i+=k<<1)
				for (int j=0;j<k;j++){
					int x=a[i+j],y=MUL(a[i+j+k],wn[k+j]);
					a[i+j+k]=ADD(x,mod-y);
					a[i+j]=ADD(x,y);
				}
		for (int i=0,INV=mod-(mod-1)/n;i<n;i++) a[i]=MUL(a[i],INV);
		reverse(a+1,a+n);
	}
}
PN operator * (const PN &a,const PN &b){
	static PN c;
	int n=a.size(),m=b.size(),t;
	for (t=1;t<n+m-1;t<<=1);
	for (int i=0;i<n;i++) temA[i]=a[i];for (int i=n;i<t;i++) temA[i]=0;
	for (int i=0;i<m;i++) temB[i]=b[i];for (int i=m;i<t;i++) temB[i]=0;
	NTT(temA,t,1);NTT(temB,t,1);
	for (int i=0;i<t;i++) temA[i]=MUL(temA[i],temB[i]);
	NTT(temA,t,-1);
	c.resize(n+m-1);for (int i=0;i<n+m-1;i++) c[i]=temA[i];
	return c;
}
int n,op,ans,fac[N],inv[N],f[N];
char s[N];
PN A,B;
void solve(int l,int r){
    if(l==r){
        if(!l)f[l]=(op?mod-1:1);
        else if(s[l]=='>')f[l]=(ll)f[l]*(mod-inv[n-l])%mod;
        else f[l]=0;
        return;
    }
    int mid=(l+r)>>1;
    solve(l,mid);
    A.clear();B.clear();
    for(int i=l;i<=mid;i++)A.pb((ll)f[i]*fac[n-i]%mod);
    for(int i=1;i<=r-l+1;i++)B.pb(inv[i]);
    A=A*B;
    for(int i=mid+1;i<=r;i++)add(f[i],A[i-l-1]);
    solve(mid+1,r);
}
void init(int nn){
    fac[0]=1;
    for(int i=1;i<=nn;i++)fac[i]=(ll)fac[i-1]*i%mod;
    inv[nn]=power(fac[nn],mod-2);
    for(int i=nn;i>=1;i--)inv[i-1]=(ll)inv[i]*i%mod;
}
int main(){
    scanf("%s",s+1);n=strlen(s+1)+1;
    init(n);NTTPre();
    for(int i=1;i<n;i++)op^=(s[i]=='>');
    solve(0,n);
    for(int i=0;i<=n;i++)add(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}