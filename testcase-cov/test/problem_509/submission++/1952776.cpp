#include<bits/stdc++.h>
#include<bits/extc++.h>
#define i64 __int128
#define int long long
#define N 20000005
#define file(x) freopen(x".in","r",stdin);freopen(x".out","w",stdout)
using namespace std;
int read(){
	int w=0,h=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')h=-h;ch=getchar();}
	while(ch>='0'&&ch<='9'){w=w*10+ch-'0';ch=getchar();}
	return w*h;
}
int n,m,ans;bool vis[N];
int pri[N],mu[N],sum[N],sum2[N],cnt;
unordered_map<int,int>M,M2;
void Euler(int n){
	mu[1]=sum[1]=sum2[1]=1;
	for(int i=2;i<=n;i++){
		if(!vis[i])pri[++cnt]=i,mu[i]=-1;
		for(int j=1;j<=cnt&&i*pri[j]<=n;j++){
			vis[i*pri[j]]=true;
			if(i%pri[j]==0)break;
			mu[i*pri[j]]=-mu[i];
		}
		sum[i]=sum[i-1]+mu[i];
		sum2[i]=sum2[i-1]+mu[i]*mu[i];
	}
}
int Mu(int x){
	if(x<N)return sum[x];
	if(M.find(x)!=M.end())return M[x];
	int res=1;
	for(int l=2,r;l<=x;l=r+1)
		r=x/(x/l),res-=(r-l+1)*Mu(x/l);
	return M[x]=res;
}
int Mu2(int x){
	if(x<N)return sum2[x];
	if(M2.find(x)!=M2.end())return M2[x];
	int res=0,up=1;
	for(;up*up*up<=x;up++)res+=mu[up]*(x/up/up);
	for(int i=x/up/up;i;i--)res+=Mu(sqrt(x/i))-sum[up-1];
	return M2[x]=res;
}
signed main(){
	n=read();m=read();Euler(N-1);
	for(int l=1,r;l<=min(n,m);l=r+1){
		int sn=sqrt(n/l),sm=sqrt(m/l);
		r=min(n/sn/sn,m/sm/sm);
		ans+=(Mu2(r)-Mu2(l-1))*sn*sm;
	}
	printf("%lld\n",ans);
	return 0;
}
