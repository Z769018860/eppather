#include<bits/stdc++.h>
using namespace std;
#define N 505050
const int inf=0x3f3f3f3f;
int dep[N],val,cnt,sum,vv[N],cur[N],pp,d,num,tot=1,head[N],ver[N],nxt[N],n,v[N],s,t,m,cost[N];
struct node{
	int x,y,r,w;
}fd[N],p[N],b[N]; 
void ad(int u,int v,int w){
	nxt[++tot]=head[u],ver[head[u]=tot]=v;cost[tot]=w;
}
void add(int u,int v,int w){
	ad(u,v,w);ad(v,u,0);
}
bool bfs(){
	for(int i=1;i<=num;i++)dep[i]=0;
	dep[s]=1;dep[t]=0;
	queue<int>q;q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=head[u];i;i=nxt[i]){
			int v=ver[i];
			if(dep[v]==0&&cost[i]>0){
				dep[v]=dep[u]+1;q.push(v);
			}
		}
	}
	return dep[t]!=0;
}
int dfs(int u,int now){
	if(u==t)return now;
	int flow=0;
	for(int &i=cur[u];i;i=nxt[i]){
		int v=ver[i];
		if(dep[v]==dep[u]+1&&cost[i]>0){
			int tmp=dfs(v,min(now,cost[i]));
			if(!tmp)continue;
			now-=tmp;flow+=tmp;
			cost[i]-=tmp;cost[i^1]+=tmp;
			if(!now)return flow;
		}
	}
	return flow;
}
int solve(){
	int ans=0;
	while(bfs()){


		for(int i=1;i<=num;i++)cur[i]=head[i];
		ans+=dfs(s,inf);

	}
	return ans;
}
bool check(int i,int j,node fd[]){
	return p[i].r*p[i].r>=(p[i].x-fd[j].x)*(p[i].x-fd[j].x)+(p[i].y-fd[j].y)*(p[i].y-fd[j].y);
}
void init(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>p[i].x>>p[i].y>>p[i].w>>p[i].r;
	val+=p[1].w;
	for(int i=1;i<=m;i++)cin>>fd[i].x>>fd[i].y>>fd[i].w;
	for(int i=1;i<=m;i++)v[i]=0;
	for(int i=1;i<=m;i++){
		if(check(1,i,fd)){
			v[i]=1;val+=fd[i].w;
		}
	}
	int m1=0,flag=0;
	for(int i=1;i<=m;i++)if(!v[i])b[++m1]=fd[i],sum+=fd[i].w;
	m=m1,s=1,t=n+m+1,num=t;
	for(int i=2;i<=n;i++)flag|=(val<p[i].w),add(s,i,max(0,val-p[i].w));
	for(int i=1;i<=m;i++)add(i+n,t,b[i].w);
	for(int i=2;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(check(i,j,b)){
				add(i,j+n,inf);
				v[j]=1;
			}
		}
	}
	for(int i=1;i<=m;i++)if(!v[i])sum-=b[i].w;
    cout<<((solve()==sum&&flag==0)?"ZQC! ZQC!":"qaq")<<"\n";
}
void clear(){
	for(int i=1;i<=tot;i++)head[i]=v[i]=vv[i]=dep[i]=cur[i]=ver[i]=nxt[i]=cost[i]=0;
	tot=1;val=sum=num=pp=d=0;
}
void ed(){
	clear();
	init();

}
int main(){
	int t;cin>>t;
	while(t--)ed();
}
