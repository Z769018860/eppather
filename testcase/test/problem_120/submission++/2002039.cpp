#include<bits/stdc++.h>
using namespace std;
const double alp=1-sqrt(2)/2;
int n,t,k,v,p,x,y,z,m,tot,rt[300001],ls[9600001],rs[9600001],val[9600001],siz[9600001];
int node(int x,int k=-1e9){
	int u=++tot;
	ls[u]=ls[x],rs[u]=rs[x],val[u]=val[x],siz[u]=siz[x];
	if(k!=-1e9) val[u]=k,siz[u]=1;
	return u;
}
void push_up(int x){
	if(ls[x]) siz[x]=siz[ls[x]]+siz[rs[x]];
}
int merge(int x,int y){
	if(!x||!y) return x|y;
	int all=siz[x]+siz[y];
	if(min(siz[x],siz[y])>=alp*all){
		int u=node(0);
		ls[u]=x,rs[u]=y,push_up(u);
		return u;
	}
	if(siz[x]>=siz[y]){
		if(siz[ls[x]]>=alp*all) return merge(ls[x],merge(rs[x],y));
		return merge(merge(ls[x],ls[rs[x]]),merge(rs[rs[x]],y));
	}
	else{
		if(siz[rs[y]]>=alp*all) return merge(merge(x,ls[y]),rs[y]);
		return merge(merge(x,ls[ls[y]]),merge(rs[ls[y]],rs[y]));
	}
}
void split(int u,int k,int &x,int &y){
	if(!k) return (void)(x=0,y=u);
	if(siz[u]==1) return (void)(x=u,y=0);
	if(siz[ls[u]]<=k) split(rs[u],k-siz[ls[u]],x,y),x=merge(ls[u],x);
	else split(ls[u],k,x,y),y=merge(y,rs[u]);
}
int query(int x,int k){
	if(siz[x]==1) return val[x];
	if(k<=siz[ls[x]]) return query(ls[x],k);
	else return query(rs[x],k-siz[ls[x]]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&p,&t,&k);
		if(p==1){
			scanf("%d",&v);
			split(rt[t],k-1,x,y);
			rt[++m]=merge(merge(x,node(0,v)),y);
		}
		else if(p==2){
			split(rt[t],k-1,x,y);
			split(y,1,y,z);
			rt[++m]=merge(x,z);
		}
		else printf("%d\n",query(rt[t],k));
	}
	return 0;
}