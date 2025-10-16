#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
  char buf[MAXSIZE], *p1, *p2;
  char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
  IO() : p1(buf), p2(buf), pp(pbuf) {}

  ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
  char gc() {
#if DEBUG  
    return getchar();
#endif
    if (p1 == p2) p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
    return p1 == p2 ? ' ' : *p1++;
  }

  bool blank(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
  }

  template <class T>
  void read(T &x) {
    double tmp = 1;
    bool sign = 0;
    x = 0;
    char ch = gc();
    for (; !isdigit(ch); ch = gc())
      if (ch == '-') sign = 1;
    for (; isdigit(ch); ch = gc()) x = x * 10 + (ch - '0');
    if (ch == '.')
      for (ch = gc(); isdigit(ch); ch = gc())
        tmp /= 10.0, x += tmp * (ch - '0');
    if (sign) x = -x;
  }

  void read(char *s) {
    char ch = gc();
    for (; blank(ch); ch = gc())
      ;
    for (; !blank(ch); ch = gc()) *s++ = ch;
    *s = 0;
  }

  void read(char &c) {
    for (c = gc(); blank(c); c = gc())
      ;
  }

  void push(const char &c) {
#if DEBUG  
    putchar(c);
#else
    if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
    *pp++ = c;
#endif
  }

  template <class T>
  void write(T x) {
    if (x < 0) x = -x, push('-');  
    static T sta[35];
    T top = 0;
    do {
      sta[top++] = x % 10, x /= 10;
    } while (x);
    while (top) push(sta[--top] + '0');
  }

  template <class T>
  void write(T x, char lastChar) {
    write(x), push(lastChar);
  }
} io;
int a[1000005];
vector<int>G[1000005];
int dfn[1000005],adfn[1000005],siz[1000005],dep[1000005],f[1000005],hson[1000005],top[1000005];
long long c[1000005],cc[1000005];
int n,m,r;
void dfs(int x,int fa){
	siz[x]=1;
	for(int i=0; i<G[x].size(); i++){
		int y=G[x][i];
		if(y==fa){continue;}
		dep[y]=dep[x]+1;f[y]=x;
		dfs(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[hson[x]])hson[x]=y;
	}
}void dfs2(int x,int fa,int t){
	top[x]=t;dfn[x]=++dfn[0];
	if(hson[x]==0){return;}
	dfs2(hson[x],x,t);
	for(int i=0; i<G[x].size(); i++){
		int y=G[x][i];
		if(y==fa||y==hson[x]){continue;}
		dfs2(y,x,y);
	}
}int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])swap(x,y);
		int tx=top[x],ty=top[y];
		y=f[top[y]];
	}if(dep[x]>dep[y])swap(x,y);
	return x;
}
int lowbit(int x){return x&-x;}

void add(int x,long long a){for(int i=x; i<=n; i+=lowbit(i))c[i]+=a,cc[i]+=a*x;}
long long sum(int x){long long ans=0,ans1=0;for(int i=x; i; i-=lowbit(i))ans+=c[i],ans1+=cc[i];return ans*(x+1)-ans1;}
void upd(int l,int r,int k){add(l,k),add(r+1,-k);}
long long query(int l,int r){return sum(r)-sum(l-1);}
long long query_path(int x,int y){
	long long ans=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])swap(x,y);
		int tx=top[x],ty=top[y];
		ans+=query(dfn[ty],dfn[y]);
		y=f[top[y]];
	}if(dep[x]>dep[y])swap(x,y);
	ans+=query(dfn[x],dfn[y]);
	return ans;
}
int main(){
	io.read(n),io.read(m),io.read(r);
	for(int i=1; i<=n; i++)io.read(a[i]);
	dep[r]=1;
	for(int i=1; i<n; i++){
		int x,y;
		io.read(x),io.read(y);
		G[x].push_back(y);
		G[y].push_back(x);
	}dfs(r,r),dfs2(r,r,r);
	for(int i=1; i<=n; i++){
		upd(dfn[i],dfn[i],a[i]); 
	}
	while(m--){
		int op,x,a;
		io.read(op),io.read(x),io.read(a);
		if(op==1){
			upd(dfn[x],dfn[x],a);
		}else if(op==2){
			upd(dfn[x],dfn[x]+siz[x]-1,a);
		}else{
			io.write(query_path(x,a),'\n');

		}
	}
	return 0;
}