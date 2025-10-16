#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m,k,top,cnt,f[N],d[N],sz[N],id[5005][5005];
struct node{int x,d,sz;}st[N*20];
vector<pair<int,int> > g[N<<2],q[N];
void update(int o,int l,int r,int x,int y,int a,int b){
	if(x<=l&&r<=y)return g[o].push_back(make_pair(a,b)),void();
	int mid=(l+r)>>1;
	if(x<=mid)update(o<<1,l,mid,x,y,a,b);
	if(y>mid)update(o<<1|1,mid+1,r,x,y,a,b); 
}
int find(int x){return x==f[x]?x:find(f[x]);}
void merge(int x,int y){x=find(x),y=find(y);if(x==y)return ;
	st[++top]={x,d[x],sz[x]},st[++top]={y,d[y],sz[y]};
	if(d[x]<d[y])swap(x,y);
	f[y]=x,sz[x]+=sz[y],d[x]+=(d[x]==d[y]);
}
void solve(int o,int l,int r,bool p){int tmp=top;
	for(auto x:g[o])merge(x.first,x.second);
	if(l==r){
		for(auto x:q[l])
			if(find(x.first)==find(x.second))printf("Y\n");
			else printf("N\n");
	}else {int mid=(l+r)>>1;
		solve(o<<1,l,mid,p),solve(o<<1|1,mid+1,r,p);
	}
	while(top!=tmp)f[st[top].x]=st[top].x,d[st[top].x]=st[top].d,sz[st[top].x]=st[top].sz,top--;
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)f[i]=i,d[i]=1,sz[i]=1;
	for(int i=1,op,x,y;i<=m;i++){
		scanf("%d%d%d",&op,&x,&y);
		if(x>y)swap(x,y);
		if(op==0)id[x][y]=i;
		else if(op==1)update(1,1,m,id[x][y],i,x,y),id[x][y]=0;
		else q[i].push_back(make_pair(x,y));
	}
	for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(id[i][j])update(1,1,m,id[i][j],m,i,j);
	solve(1,1,m,0);
	return 0;
}