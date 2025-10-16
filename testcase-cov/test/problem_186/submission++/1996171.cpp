#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int mx=3e5+5;
struct node{
	int ch[2],fa,val,tag,sum;
} a[mx];
int n,m;
void push_up(int p){
	a[p].sum=a[a[p].ch[0]].sum^a[p].val^a[a[p].ch[1]].sum;
}
void mktag(int p,int tag){
	if(tag){
		a[p].tag^=1;
		swap(a[p].ch[0],a[p].ch[1]);
	}
}
void push_down(int p){
	if(a[p].ch[0]) mktag(a[p].ch[0],a[p].tag);
	if(a[p].ch[1]) mktag(a[p].ch[1],a[p].tag);
	a[p].tag=0;
}
bool which(int p){
	return a[a[p].fa].ch[1]==p;
}
bool is_rt(int p){
	return a[a[p].fa].ch[0]!=p&&a[a[p].fa].ch[1]!=p;
}
void rotate(int x){
	int y=a[x].fa,z=a[y].fa;bool chk=which(x);
	if(!is_rt(y))
		a[z].ch[which(y)]=x;
	a[y].ch[chk]=a[x].ch[chk^1];
	if(a[x].ch[chk^1])
		a[a[x].ch[chk^1]].fa=y;
	a[x].ch[chk^1]=y;
	a[y].fa=x;a[x].fa=z;
	push_up(y);push_up(x);
}
void update(int p){
	if(!is_rt(p))
		update(a[p].fa);
	push_down(p);
}
void splay(int p){
	update(p);
	for(int i=a[p].fa;!is_rt(p);i=a[p].fa){
		if(!is_rt(i))
			rotate(which(i)==which(p)?i:p);
		rotate(p);
	}
}
void access(int x){
	for(int y=0;x;y=x,x=a[x].fa)
		splay(x),a[x].ch[1]=y,push_up(x);
}
void mk_rt(int x){
	access(x);splay(x);mktag(x,1);
}
int find_rt(int x){
	access(x);splay(x);
	while(a[x].ch[0])
		push_down(x),x=a[x].ch[0];
	splay(x);
	return x;
}
void split(int x,int y){
	mk_rt(x);access(y);splay(y);
}
void link(int x,int y){
	mk_rt(x);
	if(find_rt(y)==x)
		return ;
	a[x].fa=y;
}
void cut(int x,int y){
	mk_rt(x);
	if(x!=find_rt(y)||a[x].ch[1]!=y||a[y].ch[0])
		return ;
	a[x].ch[1]=a[y].fa=0;
	push_up(x);
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;++i)
		scanf("%lld",&a[i].val),a[i].sum=a[i].val;
	for(int i=1;i<=m;++i){
		int opt,x,y;
		scanf("%lld%lld%lld",&opt,&x,&y);
		if(opt==0)
			split(x,y),printf("%lld\n",a[y].sum);
		else if(opt==1)
			link(x,y);
		else if(opt==2)
			cut(x,y);
		else
			splay(x),a[x].val=y,push_up(x);
	}
	return 0;
}