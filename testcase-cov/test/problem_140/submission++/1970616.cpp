#include<bits/stdc++.h>
using namespace std;
int n,m,rt,gege;
struct node{int u,v,w;}e[10004],e1[10004];
int lst[103],mn[103],id[103],vis[103],stk[303],tail;
int cir[103],tot1;
int calc(){
	int res=0;
	while(1){
		for(int i=1;i<=n;++i)lst[i]=-1,mn[i]=2e9,vis[i]=id[i]=0;int tot=0;
		for(int i=1;i<=m;++i)if(lst[e[i].v]==-1||mn[e[i].v]>e[i].w)mn[e[i].v]=e[i].w,lst[e[i].v]=e[i].u;
		lst[rt]=-1,mn[rt]=1e9;
		for(int i=1;i<=n;++i)
		for(int i=1;i<=n;++i)if(i!=rt&&lst[i]==-1)return -1;
		for(int i=1;i<=n;++i){
			if(i==rt)continue;int p=i;tail=0;
			while(p!=rt&&!vis[p])vis[p]=1,stk[++tail]=p,p=lst[p];
			if(p==rt){while(tail)vis[stk[tail--]]=0;continue;}
			tot1=0;memset(vis,0,sizeof(vis));++tot;
			while(!vis[p])vis[p]=1,cir[++tot1]=p,id[p]=tot,p=lst[p];
			for(int j=1;j<=tot1;++j)res+=mn[cir[j]];
		    break;
		}
		if(!tot){
			for(int i=1;i<=n;++i)if(i!=rt)res+=mn[i];
			return res;
		}
		for(int i=1;i<=n;++i)if(!id[i])id[i]=++tot;gege=0;
		for(int i=1;i<=m;++i){
			if(e[i].v==rt||id[e[i].u]==id[e[i].v])continue;
			if(id[e[i].v]==1)e[i].w-=mn[e[i].v];
			e[i].u=id[e[i].u],e[i].v=id[e[i].v];
		    e1[++gege]=e[i];
		} 
		m=gege;n=tot;rt=id[rt];
		for(int i=1;i<=m;++i)e[i]=e1[i];
	}
}
int main() {
	cin>>n>>m>>rt;
	for(int i=1;i<=m;++i)scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	cout<<calc();
	return 0;
}