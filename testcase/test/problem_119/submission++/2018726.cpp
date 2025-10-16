#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;

#define int long long

int n,m,s,t;
int w[2509][2509];
int dis[2509];
int v[2509];

signed main(){
	memset(w,0x3f,sizeof(w));
	memset(dis,0x3f,sizeof(dis));
	
	scanf("%lld%lld%lld%lld",&n,&m,&s,&t);
	for (int i=1;i<=n;i++)	w[i][i]=0;
	for (int i=1;i<=m;i++){
		int _,__,___;
		scanf("%lld%lld%lld",&_,&__,&___);
		w[_][__]=min(___,w[_][__]);
		w[__][_]=min(___,w[__][_]);
	}
	dis[s]=0;
	
	
	for (int i=1;i<n;i++){
		int x=0;
		for (int j=1;j<=n;j++)
			if (!v[j] && (x==0||dis[j]<dis[x]))
				x=j;
		
		v[x]=1;
		for (int j=1;j<=n;j++)	dis[j]=min(dis[j],dis[x]+w[x][j]);
	}
	
	printf("%lld\n",dis[t]);
	return 0;
}