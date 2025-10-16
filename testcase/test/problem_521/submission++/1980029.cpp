#include<bits/stdc++.h>
#define int long long 
using namespace std;
int num,num1;
int hd[500005],hd1[500005];
int n,u,v;
int du[500005],in[500005];
bool vis[500005];
vector<pair<int,int> >xl;
queue<int>dl;
priority_queue<int,vector<int>,greater<int> >p;
struct P{int nxt,to;}line[1000006],line1[1000006];
void add(int x,int y){
	++num;
	line[num]={hd[x],y};
	hd[x]=num;
	return ;
}
void add1(int x,int y){
	++num1;
	line1[num1]={hd1[x],y};
	hd1[x]=num1;
	return;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	
	cin>>n;
	for(int i=1;i<n;++i){
		cin>>u>>v;
		add(u,v);
		add(v,u);
		++du[u],++du[v];
	}
	for(int i=1;i<=n;++i)
		if(du[i]==1)dl.push(i);
	while(dl.size()){
		int tp=dl.front();
		dl.pop();
		if(vis[tp])continue;
		int mat=0;
		for(int i=hd[tp];i;i=line[i].nxt){
			int to=line[i].to;
			if(vis[to])continue;
			mat=to;
			vis[to]=vis[tp]=1;
			xl.push_back({to,tp});
			break;
		}
		for(int i=hd[mat];i;i=line[i].nxt){
			int to=line[i].to;
			if(vis[to])continue;
			--du[to];
			if(du[to]==1)dl.push(to);
		}
	}
	for(int i=1;i<=n;++i)
		if(!vis[i]){
			cout<<-1<<'\n';
			return 0;
		}
	for(auto x:xl){
		int tp1=x.first,tp2=x.second;
		for(int i=hd[tp1];i;i=line[i].nxt){
			int to=line[i].to;
			if(to==tp2)continue;
			add1(tp2,to);
			++in[to];
		}
		for(int i=hd[tp2];i;i=line[i].nxt){
			int to=line[i].to;
			if(to==tp1)continue;
			add1(tp1,to);
			++in[to];
		}
	}
	for(int i=1;i<=n;++i)
		if(!in[i])p.push(i);
	while(p.size()){
		int tp=p.top();
		cout<<tp<<' ';
		p.pop();
		for(int i=hd1[tp];i;i=line1[i].nxt){
			int to=line1[i].to;
			--in[to];
			if(!in[to])p.push(to);
		}
	}
	return 0;
}