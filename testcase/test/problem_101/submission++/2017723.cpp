#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+ch-'0',ch=getchar();
	return x*f;
}
const ll N=1000010,inf=0x3f3f3f3f3f3f3f3f;
ll n,m,S,T,flow,d[N];
ll head[N],nxt[N<<1],ver[N<<1],edge[N<<1],tot,now[N];
void add(ll x,ll y,ll z){
	ver[++tot]=y,edge[tot]=z,nxt[tot]=head[x],head[x]=tot;
	ver[++tot]=x,edge[tot]=0,nxt[tot]=head[y],head[y]=tot;
}
queue<ll> Q;
bool bfs(){
	memset(d,0,sizeof(d));
	while(Q.size())Q.pop();
	Q.push(S),d[S]=1,now[S]=head[S];
	while(Q.size()){
		ll x=Q.front();Q.pop();
		for(ll i=head[x];i;i=nxt[i])
			if(!d[ver[i]]&&edge[i]){
				now[ver[i]]=head[ver[i]];
				d[ver[i]]=d[x]+1,Q.push(ver[i]);
				if(ver[i]==T)return 1;
			}
	}
	return 0;
}
ll dinic(ll x,ll flow){
	if(x==T)return flow;ll rest=flow;
	for(ll i=now[x],k;i&&rest;i=nxt[i]){
		now[x]=i;
		if(edge[i]&&d[ver[i]]==d[x]+1){
			k=dinic(ver[i],min(edge[i],rest));
			if(!k)d[ver[i]]=0;
			edge[i]-=k,edge[i^1]+=k,rest-=k;
		}
	}
	return flow-rest;
}
void MaxFlow(){while(bfs())flow+=dinic(S,inf);}
int main(){
	n=read(),m=read(),S=read(),T=read(),tot=1;
	for(ll i=1,x,y,z;i<=m;i++)
		x=read(),y=read(),z=read(),add(x,y,z);
	MaxFlow(),printf("%lld\n",flow);
	return 0;
}