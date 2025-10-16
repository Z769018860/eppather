#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=998244353;
const int G=3,Gi=332748118;
ll n;int A,B,K,S,D,cb[2005][2005],iv[1005];
int myp(int x,ll t){int a=1;for(;t;t>>=1,x=(ll)x*x%M)if(t&1)a=(ll)a*x%M;return a;}
ll a[55],b[55];int dp[55];vector<int>ord;
bool cmp(int x,int y){if(a[x]!=a[y])return a[x]<a[y];return b[x]<b[y];}
int binom(ll x,ll y){y+=x;int res=1;for(int i=0;i<x;i++,y--)res=(ll)res*(y%M)%M;return (ll)res*iv[x]%M;}
int N=1,lg,rev[2100];
void ntt(int *A,int z){
	for(int i=0;i<N;i++)if(i<rev[i])swap(A[i],A[rev[i]]);
	for(int t=2;t<=N;t<<=1){
		int md=(t>>1),Wn=myp(z==1?G:Gi,(M-1)/t);
		for(int j=0;j<N;j+=t)
			for(int k=0,w=1;k<md;k++,w=(ll)w*Wn%M){
				int x=A[j+k],y=(ll)A[j+md+k]*w%M;
				A[j+k]=(x+y)%M,A[j+md+k]=(x-y+M)%M;
			}
	}if(z<0){int iv=myp(N,M-2);for(int i=0;i<N;i++)A[i]=(ll)A[i]*iv%M;}
}
int X[2100],Y[2100],Z[2100],H[2100],sm[1005];
int calc(ll x,ll y){
	ll XX=(x+D-1)/D*D,YY=(y+D-1)/D*D;
	if(XX+YY>n)return 0;ll T=(n-XX-YY)/D+1;
	memset(X,0,sizeof(X));
	memset(Y,0,sizeof(Y));
	for(int i=0;i<=D;i++)(X[i%D]+=cb[i][D-i])%=M,Y[i]=i?0:1,Z[i]=i?0:1;
	memset(sm,0,sizeof(sm));
	ntt(X,1),ntt(Y,1);
	for(;T;T>>=1){
		if(T&1){
			ntt(Z,1);
			for(int i=0;i<N;i++)H[i]=(ll)Z[i]*Y[i]%M,Z[i]=(ll)Z[i]*X[i]%M;
			ntt(Z,-1),ntt(H,-1);
			for(int i=D;i<N;i++)(Z[i%D]+=Z[i])%=M,Z[i]=0;
			for(int i=0;i<N;i++)(sm[i%D]+=H[i])%=M;
		}
		for(int i=0;i<N;i++)H[i]=(ll)Y[i]*X[i]%M,X[i]=(ll)X[i]*X[i]%M;
		ntt(X,-1),ntt(H,-1),ntt(Y,-1);
		for(int i=D;i<N;i++)(X[i%D]+=X[i])%=M,X[i]=0;
		for(int i=0;i<N;i++)(Y[i%D]+=H[i])%=M;
		ntt(X,1),ntt(Y,1);
	}
	int ans=0;
	for(int i=0;i<=XX+YY-x-y;i++){
		int t=((XX-x)-i+D)%D;
		(ans+=(ll)cb[i][YY-y+XX-x-i]*sm[t]%M)%=M;
	}
	return ans;
}
int main(){
	int fc=1;for(int i=1;i<=1000;i++)fc=(ll)fc*i%M;
	iv[1000]=myp(fc,M-2);for(int i=1000;i;i--)iv[i-1]=(ll)iv[i]*i%M;
	scanf("%d%d%lld%d%d%d",&A,&B,&n,&D,&S,&K);
	for(int i=1;i<=K;i++)scanf("%lld%lld",&b[i],&a[i]),ord.push_back(i);
	sort(ord.begin(),ord.end(),cmp);
	for(int i=0;i<ord.size();i++){
		int x=ord[i];dp[x]=(ll)binom(b[x],a[x])*myp(A,a[x])%M*myp(B,b[x])%M;
		for(int j=0;j<i;j++){
			int y=ord[j];if(a[y]>a[x]||b[y]>b[x])continue;
			int tmp=(ll)binom(b[x]-b[y],a[x]-a[y])*myp(A,a[x]-a[y])%M*myp(B,b[x]-b[y])%M;
			(dp[x]+=M-(ll)dp[y]*tmp%M)%=M;
		}
	}
	cb[0][0]=1;
	for(int i=0;i<=D+D;i++)for(int j=0;j<=D+D;j++){
		if(i)(cb[i][j]+=(ll)cb[i-1][j]*B%M)%=M;
		if(j)(cb[i][j]+=(ll)cb[i][j-1]*A%M)%=M;
	}
	while(N<=D+D-2)N<<=1,lg++;for(int i=1;i<N;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(lg-1));
	int ans=calc(0,0);
	for(int t=1;t<=K;t++)(ans+=M-(ll)calc(b[t],a[t])*dp[t]%M)%=M;
	printf("%d",ans);
}