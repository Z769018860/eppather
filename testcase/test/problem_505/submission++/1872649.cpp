#include <bits/stdc++.h>
#define int long long
#define db double
#define pb push_back
using namespace std;
const int inf=(int)(2e16);
const int N=1002;
struct node {
	int x,y,w,r;
}a[N];
struct node2 {
	int x,y,w;
}b[N];
struct edge {
	int nex,to,w;
}e[N*N*20];
bool vis[N];
vector<int>vec[N<<2];
int n,m,S=0,T,hea[N<<2],cnt=1;

void add_edge(int x,int y,int z) {
	e[++cnt].nex=hea[x]; e[cnt].to=y; e[cnt].w=z; hea[x]=cnt;
}

void add(int x,int y,int z) {
	add_edge(x,y,z); add_edge(y,x,0);
}

void clr() {
	for(int i=1;i<=n;i++) vector<int>().swap(vec[i]);
	for(int i=0;i<=T;i++) hea[i]=0;
	cnt=1;
	for(int i=0;i<=m;i++) vis[i]=0;
}

queue<int>q;
int dis[N<<2],chea[N<<2];
bool bfs() {
	for(int i=0;i<=T;i++) chea[i]=hea[i],dis[i]=0;
	dis[S]=1; q.push(S);
	while(!q.empty()) {
		int x=q.front(); q.pop();
		for(int i=hea[x];i;i=e[i].nex) {
			int y=e[i].to;
			if(e[i].w&&!dis[y]) {
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return dis[T];
}

int dfs(int x,int Lim) {
	if(x==T||!Lim) return Lim;
	int flow=0,fl;
	for(int i=chea[x];i&&Lim;i=e[i].nex) {
		chea[x]=i; int y=e[i].to;
		if(dis[y]==dis[x]+1&&e[i].w) {
			fl=dfs(y,min(Lim,e[i].w));
			if(!fl) continue ;
			Lim-=fl; flow+=fl; e[i].w-=fl; e[i^1].w+=fl;
		}
	}
	return flow;
}

void sol() {
	cin>>n>>m;
	S=0; T=n+m+1;
	for(int i=1;i<=n;i++) {
		cin>>a[i].x>>a[i].y>>a[i].w>>a[i].r;
	}
	for(int i=1;i<=m;i++) {
		cin>>b[i].x>>b[i].y>>b[i].w;
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			int dis=(a[i].x-b[j].x)*(a[i].x-b[j].x)+(a[i].y-b[j].y)*(a[i].y-b[j].y);
			if(dis<=a[i].r*a[i].r) vec[i].pb(j),vis[j]=1;
		}
	}
	int Lim=a[1].w,all=0,fl=0;
	for(int x:vec[1]) Lim+=b[x].w,b[x].w=0;
	for(int i=1;i<=m;i++) if(b[i].w&&vis[i]) add(S,i,b[i].w),all+=b[i].w;
	for(int i=2;i<=n;i++) if(Lim-a[i].w>0) add(i+m,T,Lim-a[i].w);
	for(int i=2;i<=n;i++)
		for(int x:vec[i])
			add(x,i+m,inf);
	while(bfs()) fl+=dfs(S,inf);
	for(int i=2;i<=n;i++)
		if(a[i].w>Lim) {
			cout<<"qaq\n"; clr(); return ;
		}
	if(fl!=all) {
		cout<<"qaq\n";
	} else {
		cout<<"ZQC! ZQC!\n";
	}
	clr();
}

signed main() {
	cin.tie(0); ios::sync_with_stdio(false);
	int T; cin>>T; while(T--) sol();
	return 0;
}