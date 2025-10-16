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
const int N=4e5+5,M=1e5+5;
int n,m,K,A,B,C,P;
long long ans,val[N];
il int rnd() {return A=(A*B+C)%P;}
struct edge {
	int x,y,c,pre;
}eg[M],a[N<<1];int alen,last[N];
il void ins(int x,int y) {
	a[++alen]=edge{x,y,0,last[x]};
	last[x]=alen;
}
il bool cmp(edge x,edge y) {return x.c<y.c;}
int fa[N];
int findfa(int k) {return fa[k]=(fa[k]==k?k:findfa(fa[k]));}
void krk() {
	sort(eg+1,eg+1+m,cmp);
	int cnt=n;
	for(int i=1;i<=m;i++) {
		int fx=findfa(eg[i].x),fy=findfa(eg[i].y);
		if(fx==fy) continue;
		fa[fx]=fa[fy]=++cnt;
		val[cnt]=eg[i].c;
		ins(cnt,fx),ins(cnt,fy);
		if(cnt==2*n-1) return ;
	}
}
int dep[N],dfn[N<<1],pos[N],tot,st[(N<<1)+5][21],rev[(N<<1)+5][21];
void dfs(int x,int d) {
	dfn[++tot]=x;
	dep[tot]=d;
	pos[x]=tot;
	for(int k=last[x];k;k=a[k].pre) {
		int y=a[k].y;
		if(!pos[y]) {
			dfs(y,d+1);
			dfn[++tot]=x,dep[tot]=d;
		}
	}
}
int lg[N];
void init() {
	for(int i=2;i<=tot;i++) lg[i]=lg[i>>1]+1;
	for(int i=1;i<=tot;i++) st[i][0]=dep[i],rev[i][0]=dfn[i];
	for(int i=1;i<=lg[tot];i++) {
		for(int j=1;j+(1<<i)-1<=tot;j++) {
			if(st[j][i-1]<st[j+(1<<i-1)][i-1]) {
				st[j][i]=st[j][i-1];
				rev[j][i]=rev[j][i-1];
			}
			else {
				st[j][i]=st[j+(1<<i-1)][i-1];
				rev[j][i]=rev[j+(1<<i-1)][i-1];
			}
		}
	}
}
int LCA(int l,int r) {
	int k=lg[r-l+1];
	return st[l][k]<st[r-(1<<k)+1][k]?rev[l][k]:rev[r-(1<<k)+1][k];
}
bool _End;
int main() {
	fprintf(stderr,"Memory: %.4lf Mib\n",abs(&_End-&_Start)/1048576.0);
	read(n,m);
	for(int i=1;i<=m;i++) read(eg[i].x,eg[i].y,eg[i].c);
	for(int i=1;i<=2*n;i++) fa[i]=i;
	krk();
	dfs(2*n-1,0),init();
	read(K,A,B,C,P);
	while(K--) {
		int x=rnd()%n+1,y=rnd()%n+1;
		if(x==y) continue;
		ans=(ans+val[LCA(min(pos[x],pos[y]),max(pos[x],pos[y]))])%1000000007;
	}
	printf("%lld",ans);
	return 0;
}
