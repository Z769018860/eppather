#include<bits/stdc++.h>
#define maxn 300010
#define pr pair<int,int>
using namespace std;
int tot=0,root[maxn];
struct node{
	int lc,rc,siz;
	int val,rad;
}T[maxn<<6];
void update(int rt){
	if(!rt) return;
	T[rt].siz=1;
	if(T[rt].lc) T[rt].siz+=T[T[rt].lc].siz;
	if(T[rt].rc) T[rt].siz+=T[T[rt].rc].siz;
	return;
}
pr split(int rt,int k){
	if(!rt) return make_pair(0,0);
	int p=++tot; T[p]=T[rt];
	if(T[T[p].lc].siz>=k){
		pr tmp=split(T[p].lc,k);
		T[p].lc=tmp.second; update(p);
		return make_pair(tmp.first,p);
	}
	else{
		pr tmp=split(T[p].rc,k-(1+T[T[p].lc].siz));
		T[p].rc=tmp.first; update(p);
		return make_pair(p,tmp.second); 
	}
}
int merge(int u,int v){
	if(!u || !v) return u^v;
	if(T[u].rad>T[v].rad){
		T[u].rc=merge(T[u].rc,v);
		update(u); return u;
	}
	else{
		T[v].lc=merge(u,T[v].lc); 
		update(v); return v;
	}
}
int add(int t,int x,int a){
	int u,v; pr tmp;
	tmp=split(root[t],x-1);
	u=tmp.first, v=tmp.second;
	T[++tot]=(node){0,0,1,a,rand()};
	return merge(merge(u,tot),v);
}
int del(int t,int x){
	int u,v,w; pr tmp;
	tmp=split(root[t],x-1);
	u=tmp.first, v=tmp.second;
	tmp=split(v,1);
	v=tmp.first, w=tmp.second;
	return merge(u,w);
}
int query(int t,int x){
	int u,v,w; pr tmp;
	tmp=split(root[t],x-1);
	u=tmp.first, v=tmp.second;
	tmp=split(v,1);
	v=tmp.first, w=tmp.second;
	return T[v].val;
}
int n;
int main(){
	srand(time(0));
	scanf("%d",&n);
	int op,t,k,x,tim=0;
	while(n--){
		scanf("%d%d",&op,&t);
		if(op==1){
			scanf("%d%d",&k,&x);
			root[++tim]=add(t,k,x);
		}
		if(op==2){
			scanf("%d",&k);
			root[++tim]=del(t,k);
		}
		if(op==3){
			scanf("%d",&k);
			printf("%d\n",query(t,k));
		}
	}
	return 0;
}