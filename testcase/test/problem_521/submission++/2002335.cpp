#include<bits/stdc++.h>
#define ci const int
using namespace std;
ci N=5e5+5;
int n,mat[N],in[N];
vector<int>g[N],G[N];
set<int>S;
void dfs(ci x,ci f){
	for(int y:g[x])
		if(y!=f)
			dfs(y,x);
	if(!mat[x]){
		if(!f||mat[f])puts("-1"),exit(0);
		mat[x]=f,mat[f]=x;
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,x,y;i<n;++i)
		scanf("%d%d",&x,&y),
		g[x].push_back(y),
		g[y].push_back(x);
	dfs(1,0);
	for(int i=1;i<=n;++i)
		for(int x:g[i])
			if(x!=mat[i])
				G[mat[i]].push_back(x),
				++in[x];
	for(int i=1;i<=n;++i)if(!in[i])S.insert(i);
	for(int i=1;i<=n;++i){
		ci x=*S.begin();
		printf("%d ",x),S.erase(x);
		for(int y:G[x])if(!(--in[y]))S.insert(y);
	}
	return 0;
}