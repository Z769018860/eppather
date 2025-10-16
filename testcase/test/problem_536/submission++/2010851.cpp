#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
#include<queue> 
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=40005;
const int oo=1e9;
int m,c,n1,n2;
struct Card{
	int x;int y;
}a[N],b[N];

inline void read(int &x)
{
	int f=1;char c;
	for(x=0,c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') f=-1;
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48); x*=f;
}
inline int mn(int _x,int _y){return _x<_y?_x:_y;}
inline int mx(int _x,int _y){return _x>_y?_x:_y;}
inline int ab(int _x){return _x<0?-_x:_x;}

struct node{
	int nxt;int to;int flow;
}e[N*30];
int head[N*3],tot;int S,T;
int dep[N*3],cur[N*3];queue<int> Q;
inline void add(int from,int to,int flow){
	e[++tot].to=to;e[tot].flow=flow;
	e[tot].nxt=head[from];head[from]=tot;
}
inline void lnk(int from,int to,int flow){
	add(from,to,flow);add(to,from,0);return ;
}
inline bool bfs(int s,int t){
	for(int i=0;i<=t;i++){ 
		cur[i]=head[i];dep[i]=-1;
	}
	Q.push(s);dep[s]=1;
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].to;
			if(dep[v]==-1&&e[i].flow){
				dep[v]=dep[x]+1;Q.push(v);
			}
		}
	} 
	if(dep[t]==-1) return false;
	return true;
}
inline int dfs(int x,int flow,int t){
	if(x==t||flow<=0) return flow;
	int overflow=flow,tmp;
	for(int &i=cur[x];i;i=e[i].nxt){
		int v=e[i].to;
		if(dep[v]==dep[x]+1&&e[i].flow){
			tmp=dfs(v,mn(flow,e[i].flow),t);
			if(tmp<=0) dep[v]=-1;
			e[i].flow-=tmp;e[i^1].flow+=tmp;
			flow-=tmp;
			if(flow<=0) break;
		}
	}
	return overflow-flow;
}

bool tag[N*3],vis[N*3];


int main()
{
	read(m);read(c);
	read(n1);
	for(int i=1;i<=n1;i++){read(a[i].x);read(a[i].y);}
	read(n2);
	for(int i=1;i<=n2;i++){read(b[i].x);read(b[i].y);}
	S=0;T=n1+n2+m+c+1;tot=1;
	for(int i=1;i<=n1;i++){
		lnk(S,i,1);
		lnk(i,n1+n2+a[i].x,1);
		lnk(i,n1+n2+m+a[i].y,1);
	} 
	for(int i=1;i<=n2;i++){
		lnk(n1+i,T,1);
		lnk(n1+n2+b[i].x,n1+i,1);
		lnk(n1+n2+m+b[i].y,n1+i,1);
	}
	while(bfs(S,T)) dfs(S,oo,T);
	for(int i=head[S];i;i=e[i].nxt){
		int v=e[i].to;
		if(1<=v&&v<=n1){
			if(e[i].flow==0) tag[v]=true;
			else{Q.push(v);vis[v]=true;}
		}
	}
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(int i=head[x];i;i=e[i].nxt){
			int v=e[i].to;
			if(v==S||v==T||vis[v]) continue;
			if(e[i].flow){
				vis[v]=true;Q.push(v);
			}
		}
	}
	
	for(int i=1;i<=n1;i++){ 
		if(!tag[i]||(tag[i]&&vis[i])) puts("0");
		else puts("1");
	}
	return 0;
}

