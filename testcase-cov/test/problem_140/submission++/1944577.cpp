#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
inline int read(){
	char ch=getchar();
	while(!isdigit(ch) && ch!='-') ch=getchar();
	int x=0,ff=1; if(ch=='-') ff=-1,ch=getchar();
	while(isdigit(ch)) x=(x<<3) + (x<<1) + (ch^48),ch=getchar();
	return x*ff;
}
const int N=1e4+5,inf=1e9+5;
int n,m,rT,bd[N],fa[N],pre[N]; int isr[N];
struct node{
	int lc,rc,d,v,tv,tg;
	void addt(int x){
		tg+=x; v+=x;
	}
} a[N];
void pushdn(int p){
	if(a[p].tg){
		if(a[p].lc) a[a[p].lc].addt(a[p].tg);
		if(a[p].rc) a[a[p].rc].addt(a[p].tg);
		a[p].tg=0;
	}
}
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
int merge(int u,int v){
	if(!u || !v) return u|v;
	if(a[u].v>a[v].v) swap(u,v);
	a[v].addt(-a[u].tg); a[u].rc=merge(a[u].rc,v);
	if(a[a[u].lc].d<a[a[u].rc].d) swap(a[u].lc,a[u].rc);
	a[u].d=a[a[u].rc].d+1; return u;
}
void popt(int &p){
	pushdn(p); p=merge(a[p].lc,a[p].rc);
}
node*qtop(int x){
	while(bd[x] && getfa(a[bd[x]].tv)==x) popt(bd[x]);
	if(!bd[x]) {puts("-1"); exit(0);}
	a[bd[x]].tv=getfa(a[bd[x]].tv); return &a[bd[x]];
}
void link(int u,int v){
	u=getfa(u); v=getfa(v);
	if(u!=v) bd[v]=merge(bd[u],bd[v]),fa[u]=v;
}
int main(){
	n=read(); m=read(); rT=read(); isr[rT]=rT; a[0].d=-1; node*bf;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		a[i].v=w; a[i].tv=u; bd[v]=merge(bd[v],i);
	} 
	for(int i=1;i<=n*2;i++) fa[i]=i;
	int ans=0,ct=n;
	for(int i=1;i<=n;++i){
		int j=i;
		while(!isr[j]){
			while(!isr[j]){
				isr[j]=i,j=(bf=qtop(j))->tv;
				ans+=bf->v;
			}
			if(isr[j]!=i) break;
			while(~isr[j]){
				isr[j]=-1; j=pre[j]=(bf=qtop(j))->tv;
				bf->addt(-bf->v); 
			}
			++ct;
			while(isr[j]!=i) isr[j]=i,link(j,ct),j=pre[j];
			j=ct;
		}
	}
	printf("%d",ans);
	return 0;
}