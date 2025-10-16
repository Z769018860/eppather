#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(int i=j;i<=k;++i)
#define g(i,j,k) for(int i=j;i>=k;--i)
int n,m,s,l;
const int N=101,inf=1e17;
inline void Max(int&x,int y){if(x<y)x=y;}
int b[N],c[N],p[N],d[N][N],f[N][N][20],g[N][N*N],x,y,z;
signed main(){
	cin>>n>>m>>s>>l;
	f(i,1,n)cin>>p[i]>>c[i],c[i]=min(c[i],s);
	f(t,0,19)f(i,1,n)f(j,1,n)f[i][j][t]=d[i][j]=i!=j?b[i]=-inf:0;
	f(i,1,m)cin>>x>>y>>z,Max(f[x][y][0],z);
	f(t,1,19)f(i,1,n)f(j,1,n)f(k,1,n)Max(f[i][j][t],f[i][k][t-1]+f[k][j][t-1]);
	f(i,1,n){
		f(t,0,19)if((c[i]>>t)&1){
			f(j,1,n)f(k,1,n)Max(b[k],d[i][j]+f[j][k][t]);
			f(j,1,n)d[i][j]=b[j],b[j]=-inf;
		}
	}
	f(w,0,n*n)f(i,1,n)if(w>=p[i])f(j,1,n)Max(g[i][w],d[i][j]+g[j][w-p[i]]);
	f(_,1,l)cin>>x>>y>>z,cout<<y+g[x]-lower_bound(g[x]+1,g[x]+y+1,z)<<"\n";
	return 0;
}