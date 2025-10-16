bool _Start;
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
Tp il void read(T& x) {
	x=0;bool f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}Ts il void read(T& x,_T&... y) {read(x),read(y...);}
const int N=2010,M=1e5+5;
int n,m,K,bl[N],tot;
struct edge {
	int x,y,c,pre;
}eg[M],a[N<<1];int alen,last[N];
il void ins(int x,int y) {
	a[++alen]=edge{x,y,0,last[x]};
	last[x]=alen;
}
il bool cmp(edge x,edge y) {return x.c<y.c;}
int fa[N],val[N],rt[N];
int findfa(int k) {return fa[k]=(fa[k]==k?k:findfa(fa[k]));}
void krk() {
	sort(eg+1,eg+1+m,cmp);
	int cnt=n;
	for(int i=1;i<=m;i++) {
		int fx=findfa(eg[i].x),fy=findfa(eg[i].y);
		if(fx==fy) continue;
		fa[fx]=fa[fy]=++cnt;
		val[cnt]=eg[i].c;
		ins(fx,cnt),ins(cnt,fx);
		ins(fy,cnt),ins(cnt,fy);
		rt[bl[eg[i].x]]=cnt;
	}
}
int dep[N],par[N][15],MD;
void dfs(int x,int _fa) {
	dep[x]=dep[_fa]+1,par[x][0]=_fa;
	for(int i=1;i<=MD;i++)
		par[x][i]=par[par[x][i-1]][i-1];
	for(int k=last[x];k;k=a[k].pre) {
		int y=a[k].y;
		if(y==_fa) continue;
		dfs(y,x);
	}
}
int LCA(int x,int y) {
	if(dep[x]>dep[y]) swap(x,y);
	for(int i=MD;i>=0;i--)
		if(dep[par[y][i]]>=dep[x]) y=par[y][i];
	if(x==y) return x;
	for(int i=MD;i>=0;i--)
		if(par[x][i]!=par[y][i])
			x=par[x][i],y=par[y][i];
	return par[x][0];
}
bool _End;
int main() {
	fprintf(stderr,"Memory: %.4lf Mib\n",abs(&_End-&_Start)/1048576.0);
	read(n,m,K);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++) {
		read(eg[i].x,eg[i].y,eg[i].c);
		if(findfa(eg[i].x)!=findfa(eg[i].y)) fa[findfa(eg[i].x)]=findfa(eg[i].y);
	}
	for(int i=1;i<=n;i++) {
		if(bl[i]) continue;
		bl[i]=++tot;
		for(int j=1;j<=n;j++)
			if(findfa(i)==findfa(j)) bl[j]=tot;
	}
	for(int i=1;i<=2*n;i++) fa[i]=i;
	krk();
	MD=log2(2*n-1)+1;
	for(int i=1;i<=tot;i++) dfs(rt[i],0);
	while(K--) {
		int x,y;read(x,y);
		if(bl[x]!=bl[y]) puts("-1");
		else printf("%d\n",val[LCA(x,y)]);
	}
	return 0;
}
