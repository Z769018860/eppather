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
const int N=105,M=1e4+5,inf=1e9+5;
struct edge{
	int u,v,w;
} e[M];
int bd[N],inw[N],lp[N],st[N],tp,vis[N];
int ZhuLiu(int n,int m,int rT){
	int ans=0; e[0].w=inf;
	while(1){
		for(int i=1;i<=n;i++) inw[i]=inf,lp[i]=0;
		for(int i=1;i<=m;i++)
			if(e[i].u!=e[i].v && e[i].w<inw[e[i].v]) inw[e[i].v]=e[i].w,lp[e[i].v]=e[i].u; 
		for(int i=1;i<=n;i++) if(i!=rT && inw[i]==inf) return -1;
		for(int i=1;i<=n;i++) vis[i]=bd[i]=0;
		int gn=0;
		for(int i=1;i<=n;i++) if(i!=rT){
			ans+=inw[i]; int x=i; tp=0;
			while(!vis[x]){
				vis[x]=i; st[++tp]=x;
				x=lp[x];
			}
			if(vis[x]!=i) continue;
			++gn;
			while(1){
				bd[st[tp]]=gn;
				if(st[tp--]==x) break;
			}
		}
		for(int i=1;i<=n;i++) if(!bd[i]) bd[i]=++gn;
		for(int i=1;i<=m;i++){
			int v=e[i].v;
			e[i].u=bd[e[i].u]; e[i].v=bd[e[i].v];
			if(e[i].u!=e[i].v) e[i].w-=inw[v];
		}
		if(n==gn) break; else  n=gn,rT=bd[rT];
	}
	return ans;
}
int main(){
	int n=read(), m=read(), rT=read();
	for(int i=1;i<=m;i++) e[i]={read(),read(),read()};
	printf("%d\n",ZhuLiu(n,m,rT));
	return 0;
}