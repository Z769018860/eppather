bool _Start;
#include <bits/stdc++.h>
using namespace std;
#define il inline
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
Tp il void read(T& x) {
	x=0;bool f=0;char c=getchar();
	for(;!isdigit(c);c=getchar()) f|=c=='-';
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	x=(f?-x:x);
}Ts il void read(T& x,_T&... y) {read(x),read(y...);}
const int N=1e5+5;
int n;
struct Splay {
	int s[2],fa,siz,key;
}t[N];int rt,idx;
#define ls(x) t[x].s[0]
#define rs(x) t[x].s[1]
#define fa(x) t[x].fa
il int newnode(int x) {t[++idx].key=x,t[idx].siz=1;return idx;}
il void upd(int x) {t[x].siz=t[ls(x)].siz+t[rs(x)].siz+1;}
il void clear(int x) {ls(x)=rs(x)=fa(x)=t[x].siz=t[x].key=0;}
il bool get(int x) {return x==rs(fa(x));}
il void rotate(int x) {
	int y=fa(x),z=fa(y),c=get(x);
	if(t[x].s[c^1]) fa(t[x].s[c^1])=y;
	t[y].s[c]=t[x].s[c^1],t[x].s[c^1]=y,fa(y)=x,fa(x)=z;
	if(z) t[z].s[y==t[z].s[1]]=x;
	upd(y),upd(x);
}
il void splay(int x) {
	for(int f;f=fa(x);rotate(x))
		if(fa(f)) rotate(get(f)==get(x)?f:x);
	rt=x;
}
il void ins(int x) {
	int p=rt,f=0;
	while(p) {
		f=p;
		p=t[p].s[x>t[p].key];
	}
	p=newnode(x),fa(p)=f,t[f].s[x>t[f].key]=p;
	splay(p);
}
il void del(int x) {
	int p=rt,f=0;
	while(p&&t[p].key!=x) {
		f=p;
		p=t[p].s[x>t[p].key];
	}
	if(!p) {
		splay(f);
		return ;
	}
	splay(p);int cur=ls(p);
	if(!cur) {
		rt=rs(p),fa(rt)=0,clear(p);
		return ;
	}
	while(rs(cur)) cur=rs(cur);
	rs(cur)=rs(p),fa(rs(p))=cur,fa(ls(p))=0,clear(p);
	upd(cur),splay(cur);
}
il int rnk(int x) {
	int ans=1,p=rt,f;
	while(p) {
		f=p;
		if(t[p].key<x) ans+=t[ls(p)].siz+1,p=rs(p);
		else p=ls(p);
	}
	return splay(f),ans;
}
il int kth(int k) {
	int p=rt;
	while(p) {
		int siz=t[ls(p)].siz+1;
		if(siz==k) break;
		else if(siz>k) p=ls(p);
		else k-=siz,p=rs(p);
	}
	return splay(p),t[p].key;
}
il int pre(int x) {
	int p=rt,ans,f;
	while(p) {
		f=p;
		if(t[p].key>=x) p=ls(p);
		else ans=t[p].key,p=rs(p);
	}
	return splay(f),ans;
}
il int suc(int x) {
	int p=rt,ans,f;
	while(p) {
		f=p;
		if(t[p].key<=x) p=rs(p);
		else ans=t[p].key,p=ls(p);
	}
	return splay(f),ans;
}
bool _End;
int main() {
	fprintf(stderr,"Memory: %.4lf Mib\n",abs(&_End-&_Start)/1048576.0);
	read(n);
	ins(-2e9),ins(2e9);
	for(int i=1;i<=n;i++) {
		int op,x;read(op,x);
		if(op==0) ins(x); 
		if(op==1) del(x);
		if(op==2) printf("%d\n",kth(x+1));
		if(op==3) printf("%d\n",rnk(x)-2);
		if(op==4) printf("%d\n",pre(x)==-2e9?-1:pre(x));
		if(op==5) printf("%d\n",suc(x)==2e9?-1:suc(x));
	}
	return 0;
}
