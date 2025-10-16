#include<iostream>
#include<queue>
using namespace std;
const int N=100010,M=1000010;
long long head[N],ver[M],edge[M],Next[M],dis[N],n,m,s,t,tot;
bool vis[N];
priority_queue<pair<long long,int>>q;
void add(int x,int y,int z){
	ver[++tot]=y,edge[tot]=z,Next[tot]=head[x],head[x]=tot;
}
void dijkstra(){
	for(int i=1;i<=n;i++){
		dis[i]=1e18;
		vis[i]=0;
	}
	dis[s]=0;
	q.push(make_pair(0,s));
	while(q.size()){
		int x=q.top().second;
		q.pop();
		if(vis[x])continue;
		vis[x]=1;
		for(int i=head[x];i;i=Next[i]){
			int y=ver[i],z=edge[i];
			if(dis[y]>dis[x]+z){
				dis[y]=dis[x]+z;
				q.push(make_pair(-dis[y],y));
			}
		}
	}
}
int main()
{
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);add(y,x,z);
	}
	dijkstra();
	cout<<dis[t]<<endl;
	return 0;
}