#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define re register
#define gc getchar
#define pc putchar
#define cs const
#define st static

inline
int getint(){
	st int num;
	st char c;
	for(c=gc();!isdigit(c);c=gc());
	for(num=0;isdigit(c);c=gc())num=(num<<1)+(num<<3)+(c^48);
	return num;
}

inline
void outint(int a){
	st char ch[13];
	if(a==0)return (void)pc('0');
	while(a)ch[++ch[0]]=(a-a/10*10)^48,a/=10;
	while(ch[0])pc(ch[ch[0]--]);
}

int n,m;
int s,t;
int nxt[21000],to[21000],cap[21000],ecnt=1;
int last[205];
int low[21000];
int in[205];

inline
void addedge(int u,int v,int l,int r){
	nxt[++ecnt]=last[u],last[u]=ecnt,to[ecnt]=v,cap[ecnt]=r-l,low[ecnt]=l;
	nxt[++ecnt]=last[v],last[v]=ecnt,to[ecnt]=u,cap[ecnt]=0;
}

int lev[205];
int cur[205];

inline
bool BFS(){
	memset(lev,-1,sizeof lev);
	for(int re i=s;i<=t;++i)cur[i]=last[i];
	queue<int> q;
	q.push(s),lev[s]=0;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int re e=last[u],v=to[e];e;e=nxt[e],v=to[e]){
			if(lev[v]==-1&&cap[e]){
				lev[v]=lev[u]+1;
				if(v==t)return true;
				q.push(v);
			}
		}
	}
	return false;
}

inline
int Dinic(int u,int flow){
	if(u==t)return flow;
	int ans=0;
	for(int &e=cur[u],v=to[e];e;e=nxt[e],v=to[e]){
		if(cap[e]&&lev[v]>lev[u]){
			int delta=Dinic(v,min(cap[e],flow-ans));
			if(delta){
				cap[e]-=delta;
				cap[e^1]+=delta;
				ans+=delta;
				if(ans==flow)return ans;
			}
		}
	}
	lev[u]=-1;
	return ans; 
}

inline
int maxflow(){
	int ans=0;
	while(BFS())ans+=Dinic(s,1<<30);
	return ans;
}

inline
bool solve(){
	maxflow();
	for(int re e=last[s],v=to[e];e;e=nxt[e],v=to[e]){
		if(cap[e])return false;
	}
	return true;
}

int main(){
	n=getint();
	t=n+1;
	m=getint();
	for(int re i=1;i<=m;++i){
		int u=getint(),v=getint(),l=getint(),r=getint();
		addedge(u,v,l,r);
		in[u]+=l;
		in[v]-=l;
	}
	for(int re i=1;i<=n;++i){
		if(in[i]>0)addedge(i,t,0,in[i]);
		if(in[i]<0)addedge(s,i,0,-in[i]);
	}
	if(solve()){
		puts("YES");
		for(int re i=1;i<=m;++i){
			outint(cap[(i<<1)|1]+low[(i<<1)]);
			pc('\n');
		}
	}
	else puts("NO");
	return 0;
}