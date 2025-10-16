#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#define rep(i,l,r) for(int i=(l);i<=(r);++i)
#define per(i,r,l) for(int i=(r);i>=(l);--i)
using namespace std;
typedef long long ll;
const int P=232792561,G=71,N=30,_N=5e5+10;
int n,m,A[N][N],a[N][N],b[N][N],w[N][N],tot,p[_N],q[_N],ord[N],M,f[N];ll k;
inline void upd(int &x,int y){((x+=y)>=P)&&(x-=P);}
int ksm(int a,ll b){
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%P) if(b&1) ans=1ll*ans*a%P;
	return ans;
}
bool check(int x){
	rep(i,0,x-1) rep(j,i,x-1) if(A[i][j]<x&&1ll*f[i]*f[j]%P!=f[A[i][j]]) return 0;
	return 1;
}
void dfs(int x){
	if(tot==m) return;
	if(x==m){
		bool ok=0;
		rep(i,0,m-1) if(f[i]){ok=1;break;}
		if(!ok) return;
		rep(i,0,m-1) a[tot][i]=f[i];++tot;
		return;
	}
	rep(j,0,ord[x]){
		f[x]=w[ord[x]][j];
		if(check(x+1)) dfs(x+1);
	}
}
void inv(){
	rep(i,0,m-1)  b[i][i]=1;
	rep(i,0,m-1){
		rep(j,i,m-1) if(a[j][i]){
			rep(k,0,m-1) swap(a[i][k],a[j][k]),swap(b[i][k],b[j][k]);
			break;
		}
		int inv=ksm(a[i][i],P-2);
		rep(j,0,m-1) a[i][j]=1ll*a[i][j]*inv%P,b[i][j]=1ll*b[i][j]*inv%P;
		rep(j,0,m-1) if((i^j)&&a[j][i]){
			int w=a[j][i];
			rep(k,0,m-1) upd(a[j][k],P-1ll*a[i][k]*w%P),upd(b[j][k],P-1ll*b[i][k]*w%P);
		}
	}
}
void fwt(int *p,int n,int A[N][N]){
	
	if(n==1) return;
	int c=n/m;
	rep(i,0,m-1) fwt(p+i*c,c,A);
	rep(i,0,n-1) q[i]=0;
	rep(i,0,m-1) rep(j,0,m-1) rep(k,0,c-1) upd(q[i*c+k],1ll*p[j*c+k]*A[i][j]%P);
	rep(i,0,n-1) p[i]=q[i];
}
int main(){
	scanf("%d%d%lld",&n,&m,&k);w[1][0]=1;
	rep(i,2,m){
		w[i][0]=1;w[i][1]=ksm(G,(P-1)/i);
		rep(j,2,i-1) w[i][j]=1ll*w[i][j-1]*w[i][1]%P;
	}
	rep(i,0,m-1) rep(j,0,m-1) scanf("%d",&A[i][j]);
	rep(i,0,m-1) ord[i]=1;
	rep(i,0,m-1) for(int j=i;A[i][j]!=i;j=A[i][j],++ord[i]);
	
	dfs(0);M=ksm(m,n);
	
	rep(i,0,M-1) scanf("%d",p+i);
	fwt(p,M,a);
	rep(i,0,M-1) p[i]=ksm(p[i],k+1);
	inv();
	fwt(p,M,b);
	rep(i,0,M-1) printf("%d\n",p[i]);
	return 0;
}