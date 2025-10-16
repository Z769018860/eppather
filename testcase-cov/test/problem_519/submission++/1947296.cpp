

#include<bits/stdc++.h>
using namespace std;
int const N=1e5+10;
int const B=1500;
int n,m,ct,gd[N],id[N],bel[N],g[N],fa[N],rr[N],siz[N],ans[N],b[N],L[N],R[N],sm[N][N/B+5];
struct node{int x,y,id;};
vector<node>a[N];
vector<int>c[N];
inline int find(int x){return (x==fa[x])?x:find(fa[x]);}
inline int qry(int x,int y){
	x=find(x);
	if (y>siz[x]) return -1;
	int t=1,mm=0;
	while (mm+sm[x][t]<y) mm+=sm[x][t],++t;
	for (int i=rr[t-1]+1;;++i){
		mm+=(find(id[i])==x);
		if (mm==y) return b[id[i]];
	}
}
inline void dfs(int x){
	int fx=find(L[x]),fy=find(R[x]);
	if (siz[fx]>siz[fy]) swap(fx,fy);
	if (fx!=fy){
		fa[fx]=fy,siz[fy]+=siz[fx];
		for (int i=1;i<=bel[n];++i) sm[fy][i]+=sm[fx][i];
	}
	for (auto j:a[x])
		ans[j.id]=qry(j.x,j.y);
	for (auto v:c[x]) dfs(v);
	if (fx!=fy){
		fa[fx]=fx,siz[fy]-=siz[fx];
		for (int i=1;i<=bel[n];++i) sm[fy][i]-=sm[fx][i];
	}
}
void solve(){
	cin>>n>>m;
	for (int i=1;i<=n;++i) cin>>b[i],id[i]=fa[i]=i,siz[i]=1;
	sort(id+1,id+n+1,[](int x,int y){return b[x]<b[y];});
	for (int i=1;i<=n;++i) g[id[i]]=i;
	for (int i=1;i<=n;++i) bel[i]=(i-1)/B+1,rr[bel[i]]=i;
	for (int i=1;i<=n;++i) ++sm[i][bel[g[i]]];
	int la=0,sm=0;
	while (m--){
		int op;cin>>op;
		if (op==1){
			int x,y;cin>>x>>y;
			++ct,L[ct]=x,R[ct]=y,c[la].push_back(ct),la=ct;
		}
		if (op==2){
			int x;cin>>x;
			if (!x) la=0;else la=gd[x];
		}
		if (op==3){
			int x,y;cin>>x>>y,++sm;
			a[la].push_back((node){x,y,sm});
		}
		gd[++gd[0]]=la;
	}
	dfs(0);
	for (int i=1;i<=sm;++i) cout<<ans[i]<<'\n';
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	
	while (t--) solve();
	cerr<<"Running Time: "<<(double)clock()/CLOCKS_PER_SEC<<" s\n";
	return 0;
}