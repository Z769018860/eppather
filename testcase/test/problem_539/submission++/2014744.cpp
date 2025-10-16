#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j) for(int i=1;i<=j;++i)
int n,m,s,l;
const int N=101;
#define Max(x,y)x=max(x,y)
int c[N],p[N],d[N][N],f[N][N][20],g[N][N*N],x,y,z;
signed main(){
	cin>>n>>m>>s>>l;
	f(i,n)cin>>p[i]>>c[i],c[i]=min(c[i],s);
	f(t,19)f(i,n)f(j,n)f[i][j][t]=d[i][j]=i!=j?-1e17:0;
	f(i,m)cin>>x>>y>>z,Max(f[x][y][1],z);
	f(t,18)f(i,n)f(j,n)f(k,n)Max(f[i][j][t+1],f[i][k][t]+f[k][j][t]);
	f(i,n){
		f(t,19)if(c[i]>>t-1&1){
			f(j,n)d[0][j]=d[i][j];
			f(j,n)f(k,n)Max(d[i][k],d[0][j]+f[j][k][t]);
		}
	}
	f(w,n*n)f(i,n)if(w>=p[i])f(j,n)Max(g[i][w],d[i][j]+g[j][w-p[i]]);
	f(_,l)cin>>x>>y>>z,cout<<y+g[x]-lower_bound(g[x]+1,g[x]+y+1,z)<<"\n";
	return 0;
}