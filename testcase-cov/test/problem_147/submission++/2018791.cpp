#include<iostream>
#include<cstdio>
#include<vector>
#pragma GCC optimze(2)
using namespace std;
int a[1000005];
vector<int>G[1000005];
int dfn[1000005],adfn[1000005],siz[1000005],dep[1000005],f[1000005],hson[1000005],top[1000005];
long long c[1000005],cc[1000005];
int n,m,r;
void dfs(int x,int fa){
	siz[x]=1;
	for(int i=0; i<G[x].size(); i++){
		int y=G[x][i];
		if(y==fa){continue;}
		dep[y]=dep[x]+1;f[y]=x;
		dfs(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[hson[x]])hson[x]=y;
	}
}void dfs2(int x,int fa,int t){
	top[x]=t;dfn[x]=++dfn[0];
	if(hson[x]==0){return;}
	dfs2(hson[x],x,t);
	for(int i=0; i<G[x].size(); i++){
		int y=G[x][i];
		if(y==fa||y==hson[x]){continue;}
		dfs2(y,x,y);
	}
}int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])swap(x,y);
		int tx=top[x],ty=top[y];
		y=f[top[y]];
	}if(dep[x]>dep[y])swap(x,y);
	return x;
}
int lowbit(int x){return x&-x;}

void add(int x,long long a){for(int i=x; i<=n; i+=lowbit(i))c[i]+=a,cc[i]+=a*x;}
long long sum(int x){long long ans=0,ans1=0;for(int i=x; i; i-=lowbit(i))ans+=c[i],ans1+=cc[i];return ans*(x+1)-ans1;}
void upd(int l,int r,int k){add(l,k),add(r+1,-k);}
long long query(int l,int r){return sum(r)-sum(l-1);}
long long query_path(int x,int y){
	long long ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])swap(x,y);
		int tx=top[x],ty=top[y];
		ans+=query(dfn[ty],dfn[y]);
		y=f[top[y]];
	}if(dep[x]>dep[y])swap(x,y);
	ans+=query(dfn[x],dfn[y]);
	return ans;
}
int main(){
	scanf("%d%d%d",&n,&m,&r);
	for(int i=1; i<=n; i++)scanf("%d",&a[i]);
	dep[r]=1;
	for(int i=1; i<n; i++){
		int x,y;
		scanf("%d%d",&x,&y);
		G[x].push_back(y);
		G[y].push_back(x);
	}dfs(r,r);
	dfs2(r,r,r);
	for(int i=1; i<=n; i++){
		upd(dfn[i],dfn[i],a[i]); 
	}
	while(m--){
		int op,x,a;
		scanf("%d%d",&op,&x);
		if(op==1){
			scanf("%d",&a);
			upd(dfn[x],dfn[x],a);
		}else if(op==2){
			scanf("%d",&a);
			upd(dfn[x],dfn[x]+siz[x]-1,a);
		}else{
			scanf("%d",&a);
			printf("%lld\n",query_path(x,a)) ;
		}
	}
	return 0;
}