#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5,M=1e9+7;
struct Edge{
	int u,v,w,nxt;
	bool operator<(const Edge t)const{
		return w<t.w;
	}
}e[N];
int n,m,q,A,B,C,P,swq,po,tot,idx,hd[N],f[N],rt[N],val[N],dep[N],dfn[N],pos[N],st[N][21];
vector<Edge>eg;
void adde(int u,int v){
	e[++po]={u,v,0,hd[u]},hd[u]=po;
}
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
void kruskal(){
	sort(eg.begin(),eg.end());
	tot=n;
	for(int i=1;i<=n;i++)f[i]=rt[i]=i;
	for(int i=0;i<m;i++){
		int fu=find(eg[i].u),fv=find(eg[i].v),w=eg[i].w;
		if(fu!=fv){
			val[++tot]=w;
			adde(tot,rt[fu]),adde(tot,rt[fv]);
			f[fu]=fv,rt[fv]=tot;
		}
	}
}
void dfs(int u,int fa){
	dfn[++idx]=u,pos[u]=idx,dep[u]=dep[fa]+1;
	for(int i=hd[u];i;i=e[i].nxt)
		dfs(e[i].v,u),dfn[++idx]=u;
}
int rnd(){return A=(A*B+C)%P;}
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin>>u>>v>>w;
		eg.push_back({u,v,w,0});
	}
	kruskal(),dfs(tot,0);
	for(int i=1;i<=idx;i++)st[i][0]=i;
	for(int s=1;s<=__lg(idx);s++)
		for(int i=1;i+(1<<s)-1<=idx;i++){
			int L=st[i][s-1],R=st[i+(1<<(s-1))][s-1];
			st[i][s]=dep[dfn[L]]<dep[dfn[R]]?L:R;
		}
	cin>>q>>A>>B>>C>>P;
	while(q--){
		int u=rnd()%n+1,v=rnd()%n+1,l=pos[u],r=pos[v];
		if(l>r)swap(l,r);
		int s=__lg(r-l+1),L=st[l][s],R=st[r-(1<<s)+1][s];
		swq=(swq+(dep[dfn[L]]<dep[dfn[R]]?val[dfn[L]]:val[dfn[R]]))%M;
	}
	cout<<swq;
	return 0;
}