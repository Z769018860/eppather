#include <iostream>
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n;
int lowbit(int x){
	return x&-x;
} 
int tree[2000020];
int root,cnt=0,L[2000020],R[2000020];
struct Node{
	int Nxt,to;
}l[2000020];
int h[2000020];
int val[2000020];
int treer[2000020];
void link(int u,int v){
	l[++cnt]=Node{h[u],v};h[u]=cnt;
	l[++cnt]=Node{h[v],u};h[v]=cnt;
}
void DFS(int x,int f){
	
	treer[cnt]=x;
	L[x]=cnt++;
	for(int i=h[x],v;i;i=l[i].Nxt){
		v=l[i].to;
		
		if(v==f)continue;
		if(v!=f){
			DFS(v,x);
		}
	}
	R[x]=cnt;
	return;
}
void add(int x,int d){
	for(int i=x;i<=n;i+=lowbit(i))tree[i]+=d;
}
int query(int x){
	int ans=0;
	for(int i=x;i>0;i-=lowbit(i))ans+=tree[i];
	return ans;
}
signed main(){
	int m,x,y,rt;
	cin>>n>>m>>rt;
	for(int i=1;i<=n;i++){
		cin>>val[i];
	}
	for(int i=1;i<n;i++){
		cin>>x>>y;
		link(x,y);
	}	
	cnt=1;
	DFS(rt,rt);
	for(int i=1;i<cnt;i++){
		add(i,val[treer[i]]);
		
	}
	int aa,bb,cc;
	while(m--){
		cin>>aa;
		if(aa==1){
			cin>>bb>>cc;
			add(L[bb],cc);
		}
		if(aa==2){
			cin>>bb;
			
			cout<<query(R[bb]-1)-query(L[bb]-1)<<endl;
		}
	}
	return 0;
	}