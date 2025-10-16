#include<bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
const int B=450;
int n,m;vector<int>tr[100004];
pii all[100004];int op[100004],x[100004],y[100004];
int stx[100004],sty[100004],stz[100004],sta;
int fa[100004],rk[100004],p[200004],q[200004],len;
int sz[100004],rs[100004];
int Fa(int x){while(x!=fa[x])x=fa[x];return x;}
bool Merge(int x,int y){
	x=Fa(x),y=Fa(y);if(x==y)return 0;if(rk[x]<rk[y])swap(x,y);
	stx[++sta]=x,sty[sta]=y,stz[sta]=rk[x],p[++len]=x,q[len]=y;
	fa[y]=x,rk[x]=max(rk[x],rk[y]+1);return 1;
}
void Undo(){int x=stx[sta],y=sty[sta];rk[x]=stz[sta--],fa[y]=y,p[++len]=-x,q[len]=y;}
void init(int u){
	bool ADD=0;if(op[u]==1)ADD=Merge(x[u],y[u]);
	if(op[u]==3)p[++len]=u,q[len]=-Fa(x[u]);for(auto&v:tr[u])init(v);if(ADD)Undo();
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++)scanf("%d",&x),all[i]={x,i};
	sort(all+1,all+n+1);
	for(int i=1,v;i<=m;i++){
		scanf("%d",&op[i]);
		if(op[i]==2)scanf("%d",&v),tr[v].emplace_back(i);
		else scanf("%d%d",&x[i],&y[i]),tr[i-1].emplace_back(i);
	}
	iota(fa+1,fa+n+1,1),init(0);
	for(int t=1;t<=n;t+=B){
		memset(sz,0,sizeof(sz));
		for(int i=t;i<min(t+B,n+1);i++)sz[all[i].se]=1;
		for(int i=1;i<=len;i++){
			int u=p[i],v=q[i];
			if(u>0){
				if(v<0){
					if(!rs[u]){
						int w=sz[-v];
						if(y[u]>w)y[u]-=w;
						else rs[u]=t;
					}
				}else sz[u]+=sz[v];
			}else sz[-u]-=sz[v];
		}
	}
	for(int t=1;t<=n;t+=B){
		for(int i=1;i<=len;i++){
			int u=p[i],v=q[i];
			if(u>0){
				if(v<0){
					if(rs[u]==t){
						int p=t;
						while(y[u]-=Fa(all[p].se)==-v)p++;
						rs[u]=p;
					}
				}else fa[v]=u;
			}else fa[v]=v;
		}
	}
	for(int i=1;i<=m;i++)if(op[i]==3)printf("%d\n",rs[i]?all[rs[i]].fi:-1);
}