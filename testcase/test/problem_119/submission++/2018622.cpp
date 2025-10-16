#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m,s,t;
int to[12410],nxt[12410],h[2510],val[12410],tot;
int vis[2510],dis[2510];
priority_queue<pair<int,int> >q;

void add(int x,int y,int w){
	to[++tot]=y,nxt[tot]=h[x],val[tot]=w,h[x]=tot;
}

void dij(int x){
	memset(dis,0x3f,sizeof(dis));
	dis[x]=0;
	q.push(make_pair(0,x));
	while(!q.empty()){
		int q1=q.top().second,q2=-q.top().first;
		q.pop();
		if(vis[q1])continue;
		vis[q1]=1;
		for(int i=h[q1];i;i=nxt[i])
			if(q2+val[i]<dis[to[i]]){
				dis[to[i]]=q2+val[i];
				q.push(make_pair(-dis[to[i]],to[i]));
			}
	}
}

signed main(){
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,z);
	}
	dij(s);
	cout<<dis[t];
	return 0;
}