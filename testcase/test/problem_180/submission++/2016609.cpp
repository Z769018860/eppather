#include<bits/stdc++.h>

#define ll long long
#define mk make_pair
#define fi first
#define se second

using namespace std;

inline int read(){
	int x=0,f=1;char c=getchar();
	for(;(c<'0'||c>'9');c=getchar()){if(c=='-')f=-1;}
	for(;(c>='0'&&c<='9');c=getchar())x=x*10+(c&15);
	return x*f;
}

const int mod=998244353;
int ksm(int x,ll y,int p=mod){
	int ans=1;y%=(p-1);
	for(int i=y;i;i>>=1,x=1ll*x*x%p)if(i&1)ans=1ll*ans*x%p;
	return ans%p;
}
int inv(int x,int p=mod){return ksm(x,p-2,p)%p;}
mt19937 rnd(20070819);
int randint(int l,int r){return rnd()%(r-l+1)+l;}
void add(int &x,int v){x+=v;if(x>=mod)x-=mod;}
void Mod(int &x){if(x>=mod)x-=mod;}
int cmod(int x){if(x>=mod)x-=mod;return x;}

template<typename T>void cmax(T &x,T v){x=max(x,v);}
template<typename T>void cmin(T &x,T v){x=min(x,v);}

const int N=4e6+5;
const int M=N*2;
int n,d;
int G[M],st[N],ed[N],deg[N],tot=1,id[N];
bool used[M];
int ml[N],mr[N],rev[M];
vector<int>nodes[N];

void argu_L(int x);
void argu_R(int x,int pre);

void argu_L(int x){
	while(1){
		int p=randint(st[x],ed[x]);
		if(p==ml[x])continue;
		ml[x]=p,argu_R(G[p],rev[p]);break;
	}
}
void argu_R(int x,int pre){
	if(!mr[x]){mr[x]=pre;return ;}
	int y=G[mr[x]];mr[x]=pre,argu_L(y);
}

signed main(void){

#ifndef ONLINE_JUDGE
	freopen("in.in","r",stdin);
#endif

	n=read(),d=read();
	auto Rec=[&](vector<int>&A){sort(A.begin(),A.end());A.resize(unique(A.begin(),A.end())-A.begin());};
	auto adde=[&](int u,int v){deg[u]++,deg[v]++;};
	auto inse=[&](int u,int v){G[--st[u]]=v;return st[u];};
	for(int i=1;i<=n;i++){
		nodes[i].resize(d);
		for(int j=0;j<d;j++)nodes[i][j]=read();
		Rec(nodes[i]);
		for(int j:nodes[i])adde(i,j+n);
	}
	for(int i=1;i<=2*n;i++)deg[i]+=deg[i-1],st[i]=deg[i]+1,ed[i]=deg[i];
	for(int i=1;i<=n;i++)for(int j:nodes[i]){
		int lx=inse(i,j+n),rx=inse(j+n,i);
		rev[lx]=rx,rev[rx]=lx;
	}
	
	for(int i=1;i<=n;i++)id[i]=i;shuffle(id+1,id+n+1,rnd);
	for(int i=1;i<=n;i++)argu_L(id[i]);
	
	for(int i=1;i<=n;i++)cout<<G[ml[i]]-n<<" \n"[i==n];

	return 0;
}
