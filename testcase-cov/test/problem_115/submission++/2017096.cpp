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
const int M=2e4+5,N=405,inf=1e9;
struct edge{
	int from,to,val;
} dis[M<<2];
int head[N],gn,cur[N],S,T,tot=1,fd[N];
void add_edge(int u,int v,int w){ 
	dis[++tot]={head[u],v,w},head[u]=tot; }
void AddE(int u,int v,int w){ add_edge(u,v,w); add_edge(v,u,0); }
bool bfs(){
	for(int i=1;i<=gn;i++) fd[i]=-1,cur[i]=head[i];
	fd[S]=0; queue<int> q; q.push(S);
	while(!q.empty()){
		int u=q.front(); q.pop();
		for(int i=head[u];i;i=dis[i].from) if(dis[i].val){
			int v=dis[i].to;
			if(!~fd[v]) fd[v]=fd[u]+1,q.push(v);
		}
	} return ~fd[T];
}
int dfs(int u,int fl){
	if(u==T || !fl) return fl;
	int ud=0;
	for(int &i=cur[u];i;i=dis[i].from) if(dis[i].val){
		int v=dis[i].to; if(fd[v]!=fd[u]+1) continue;
		int bf=dfs(v,min(fl,dis[i].val));
		dis[i].val-=bf; dis[i^1].val+=bf; ud+=bf; fl-=bf;
		if(!fl) break;
	} return ud;
}
int n,m,eb[M],ed[M],ans,din[N],dout[N];
int main(){
	n=read(); m=read(); gn=n; S=++gn; T=++gn;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),L=read(),R=read();
		dout[u]+=L; din[v]+=L; ed[i]=tot+2; eb[i]=L; AddE(u,v,R-L);
	}
	for(int i=1;i<=n;i++)
		if(din[i]>dout[i]) AddE(S,i,din[i]-dout[i]),ans+=din[i]-dout[i];
		else AddE(i,T,dout[i]-din[i]);
	while(bfs()) ans-=dfs(S,inf);
	if(ans) {puts("NO"); return 0;}
	puts("YES");
	for(int i=1;i<=m;i++) printf("%d\n",dis[ed[i]].val+eb[i]);
	return 0;
}