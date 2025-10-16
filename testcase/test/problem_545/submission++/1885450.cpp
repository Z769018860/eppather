#include<bits/stdc++.h>
#define db double
#define int ll
#define ll long long
#define ull unsigned long long
#define pb emplace_back
#define MP make_pair
#define pii pair<int, int>
#define vec vector<int>
#define fi first
#define se second
#define ls k<<1
#define rs k<<1|1
#define CLK (double)clock()/(double)CLOCKS_PER_SEC
using namespace std;
mt19937 rnd(time(0));
inline int read(){
    register int x=0,f=1;
    register char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
inline void write(register int x){
    if(x<0){putchar('-');x=-x;}
    if(x>9)write(x/10);
    putchar(x%10+'0');
}
namespace IO {
  #define iL (1 << 20)
  #define gc() iS == iT ? iT = (iS = ibuf) + fread(ibuf, 1, iL, stdin), iS == iT ? EOF : *iS++ : *iS++
  char ibuf[iL], *iS = ibuf + iL, *iT = ibuf + iL;
  template<class T> inline void read(T &x) {
    char c = gc(); bool f = 0; x = 0;
    while(!isdigit(c)) {f |= c == '-'; c = gc();}
    while(isdigit(c)) {x = (x << 1) + (x << 3) + (c & 15); c = gc();}
    if(f) x = -x;
  }
  #undef iL
  #undef gc
}
using namespace IO;
const int N=100+5,M=1e6+5,inf=1e9;
int n,m,k,org,cntp[40],cntq[40],del[40];
int lowbit(int x){return x&(-x);}
namespace MCMF{
	int s,t,maxflow,ans,cnt=1,to[M],w[M],f[M],nxt[M],first[N],cur[N];
	int dis[N],vis[N];
	inline void add(int x,int y,int wgh,int flow){
		to[++cnt]=y,w[cnt]=wgh,f[cnt]=flow,nxt[cnt]=first[x],first[x]=cnt;
		to[++cnt]=x,w[cnt]=0,f[cnt]=-flow,nxt[cnt]=first[y],first[y]=cnt;
	}
	inline bool SPFA(){
		for(int i=1;i<=t;i++)dis[i]=inf,vis[i]=0,cur[i]=first[i];
		queue<int>q;q.push(s),dis[s]=0;
		while(!q.empty()){
			int x=q.front();q.pop();
			vis[x]=0;
			for(int i=first[x];i;i=nxt[i]){
				int y=to[i];
				if(w[i]&&dis[y]>dis[x]+f[i]){
					dis[y]=dis[x]+f[i];
					if(!vis[y])vis[y]=1,q.push(y);
				}
			}	
		}
		return dis[t]<0;
	}
	inline int dinic(int x,int flow){
		if(x==t||!flow)return maxflow+=flow,flow;
		int rest=flow;vis[x]=1;
		for(int i=cur[x];i&&rest;i=nxt[i]){
			int y=to[i];cur[x]=i;
			if(!vis[y]&&w[i]&&dis[y]==dis[x]+f[i]){
				int in=dinic(y,min(rest,w[i]));
				if(!in)dis[y]=0;
				w[i]-=in,w[i^1]+=in;
				rest-=in,ans+=in*f[i];
			}
		}
		vis[x]=0;
		return flow-rest;
	}
	inline void Solve(){
		while(SPFA())dinic(s,inf);
	} 
}using namespace MCMF;
const int siz=1.2e6+5;
int p[siz],q[siz];
int get(int x){return __builtin_ctz(x&-x);}
void MAIN(){
    int lim=31;
    s=lim*2+1,t=s+3;
    read(n);
    for(int i=1;i<=n;i++)read(p[i]),cntp[get(p[i])+1]++,org+=lowbit(p[i]);
    read(m);
    for(int i=1;i<=m;i++)read(q[i]),cntq[get(q[i])+1]++;
   	read(k);
    sort(p+1,p+1+n),sort(q+1,q+1+m);
    for(int i=1,j=1;i<=n;i++){
        while(j<=m&&q[j]<p[i])j++;if(j>m)break;
        int v=get(p[i])+1;
        if(p[i]==q[j])del[v]++,j++;
    }
    
    
    add(s,s+1,k,0);add(t-1,t,k,0);
    for(int i=1;i<=lim;i++)add(s+1,i,cntp[i],-(1<<i-1)),add(i+lim,t-1,cntq[i],1<<i-1);
    for(int i=1;i<=lim;i++){
		add(i,i+lim,del[i],-(1<<i-1));
		for(int j=1;j<i;j++)add(i,j+lim,inf,0);
	}
    Solve();cout<<org+ans;
}
signed main(){
   
	
    int T=1;while(T--)MAIN();

    return 0;
}