
#include<bits/stdc++.h>
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
	while(isdigit(c)){x=(x<<3)+(x<<1)+(c^48);c=getchar();}
	return f==1?x:-x;
}
const int N=3e5+4;
int n,m,rev[N],fa[N],ch[N][2],s[N],a[N];
int st[N],top=0;
inline bool getson(int p){
	return ch[fa[p]][1]==p;
}
inline bool isroot(int p){
	return ch[fa[p]][getson(p)]!=p;
}
inline void pushdown(int p){
	if(!rev[p])return;
	swap(ch[p][0],ch[p][1]);
	rev[ch[p][0]]^=1;rev[ch[p][1]]^=1;
	rev[p]^=1;
}
inline void pushup(int p){
	top=1;st[1]=p;
	for(int i=p;!isroot(i);i=fa[i])st[++top]=fa[i];
	for(int i=top;i;i--)pushdown(st[i]);
}
inline void pushnow(int p){
	s[p]=s[ch[p][0]]^s[ch[p][1]]^a[p];
}
inline void rotate(int p){
	int f=fa[p],g=fa[f],r=getson(p);
	if(!isroot(f))ch[g][getson(f)]=p;fa[p]=g;
	ch[f][r]=ch[p][r^1];if(ch[f][r])fa[ch[f][r]]=f;
	ch[p][r^1]=f;fa[f]=p;
	pushnow(f);pushnow(p);
}
inline void splay(int p){
	pushup(p);
	for(;!isroot(p);rotate(p))
		if(!isroot(fa[p]))rotate(getson(p)==getson(fa[p])?fa[p]:p);
}
inline void access(int p){
	for(int pre=0;p;pre=p,p=fa[p]){
		splay(p);ch[p][1]=pre;
		pushnow(p);
	}
}
inline void makeroot(int p){
	access(p);splay(p);rev[p]^=1;
}
inline int find(int p){
	access(p);splay(p);
	while(ch[p][0])p=ch[p][0];
	return p;
}
inline void link(int u,int v){
	makeroot(u);fa[u]=v;
}
inline void cut(int u,int v){
	makeroot(u);access(v);splay(v);
	if(fa[u]==v&&!ch[u][1])ch[v][0]=fa[u]=0;pushnow(v);
}
inline int query(int u,int v){
	makeroot(u);access(v);splay(v);
	return s[v];
}
inline void change(int x,int v){
	splay(x);a[x]=v;
}
int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)s[i]=a[i]=read();
	int r,x,y;
	while(m--){
		r=read();x=read();y=read();
		switch(r){
			case 0:printf("%d\n",query(x,y));break;
			case 1:if(find(x)!=find(y))link(x,y);break;
			case 2:if(find(x)==find(y))cut(x,y);break;
			case 3:change(x,y);
		}
	}
	return 0;
}
