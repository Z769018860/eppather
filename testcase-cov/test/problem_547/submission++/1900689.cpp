#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;
#define int long long
const int mod=65537;
const int maxn=505;
int n,m,qz[mod+5],inv_qz[mod+5],pow2[mod+5];
int power(int x,int y){
	if(!y)return 1;
	int tmp=power(x,y>>1);
	if(y&1)return tmp*tmp*x%mod;
	return tmp*tmp%mod;
}
int Cz(int x,int y){
	if(x<y)return 0;
	return qz[x]*inv_qz[y]*inv_qz[x-y]%mod;
}
int luc(int x,int y){
	if(y==0)return 1;
	int tmp=Cz(x%mod,y%mod);
	if(!tmp)return 0;
	return tmp*luc(x/mod,y/mod)%mod;
}
int solve(int x){
	int res=0;
	for(int i=0;i*m<=x;++i){
		int c2=x-i*m,mul=1;
		if(i&1)mul=mod-1;
		res=(res+mul*pow2[c2%(mod-1)]*luc(c2+i,i))%mod;
	}
	return res;
}
struct node{
	int p[maxn][maxn];
	node(int x=0){
		memset(p,0,sizeof(p));
		for(int i=1;i<=m;++i)p[i][i]=x;
	}
	node operator*(const node& tmp)const{
		node res;
		for(int i=1;i<=m;++i)for(int j=1;j<=m;++j)for(int k=1;k<=m;++k){
			res.p[i][k]+=p[i][j]*tmp.p[j][k];
		}
		for(int i=1;i<=m;++i)for(int j=1;j<=m;++j)res.p[i][j]%=mod;
		return res;
	}
};
node power(node x,int y){
	if(!y)return node(1);
	node tmp=power(x,y>>1);
	if(y&1)return tmp*tmp*x;
	return tmp*tmp;
}
signed main(){
	scanf("%lld%lld",&n,&m);
	if(m<=500){
		node bas;
		for(int i=1;i<=m;++i)bas.p[1][i]=1;
		for(int i=1;i<m;++i)bas.p[i+1][i]=1;
		printf("%lld",power(bas,n+1).p[1][1]);
	}
	else{
		pow2[0]=1;
		for(int i=1;i<mod-1;++i)pow2[i]=pow2[i-1]*2%mod;
		qz[0]=inv_qz[0]=1;
		for(int i=1;i<mod;++i){
			qz[i]=qz[i-1]*i%mod;
			inv_qz[i]=power(qz[i],mod-2);
		}
		++m;
		printf("%lld",(solve(n+1)-solve(n)+mod)%mod);
	}
	return 0;
}