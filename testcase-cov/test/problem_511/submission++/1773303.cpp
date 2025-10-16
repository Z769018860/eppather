#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
using namespace std;
const ll MAXN=1e6+10,INF=1.5e18;

ll add(ll x,ll y){
	return (x+y>=INF)?(INF):(x+y);
}
ll mult(ll x,ll y){
	if(!x || !y)return 0;
	else return (x >= (INF+y-1)/y) ? (INF) : (x*y);
}

typedef array<ll,2> vec;
typedef array<ll,4> mat;
const mat I = {1,0,0,1};

vec operator*(const vec V,const mat A){
	vec Z;
	Z[0] = add(mult(V[0],A[0]),mult(V[1],A[2]));
	Z[1] = add(mult(V[0],A[1]),mult(V[1],A[3]));
	return Z;
}
mat operator*(const mat A,const mat B){
	mat C;
	C[0] = add(mult(A[0],B[0]),mult(A[1],B[2]));
	C[1] = add(mult(A[0],B[1]),mult(A[1],B[3]));
	C[2] = add(mult(A[2],B[0]),mult(A[3],B[2]));
	C[3] = add(mult(A[2],B[1]),mult(A[3],B[3]));
	return C;
}

struct T1{ 
	vector<mat> t;
	void init(int n){
		t.resize((n<<2)+10,I);
	}
	void pushup(int x){
		t[x] = t[rc(x)] * t[lc(x)];
	}
	void mdf(int x,int l,int r,int pos,mat v){
		if(l==r)return (void)(t[x] = v);
		int mid=(l+r)>>1;
		(pos<=mid)?(mdf(lc(x),l,mid,pos,v)):(mdf(rc(x),mid+1,r,pos,v));
		pushup(x);
	}
	mat qry(int x,int l,int r,int ql,int qr){
		if(ql>qr)return I;
		if(ql<=l && qr>=r)return t[x];
		int mid=(l+r)>>1;
		mat ret=I;
		if(qr>mid)ret = ret*qry(rc(x),mid+1,r,ql,qr);
		if(ql<=mid)ret = ret*qry(lc(x),l,mid,ql,qr);
		return ret;
	}
}sF[MAXN];

struct T2{
	vector<ll>t;
	void init(int n){
		t.resize((n<<2)+5,1);
	}
	void pushup(int x){
		t[x] = mult(t[lc(x)],t[rc(x)]);
	}
	void mdf(int x,int l,int r,int pos,ll v){
		if(l==r)return (void)(t[x] = v);
		int mid=(l+r)>>1;
		(pos<=mid)?(mdf(lc(x),l,mid,pos,v)):(mdf(rc(x),mid+1,r,pos,v));
		pushup(x);
	}
	ll qry(){return t[1];}
}sG[MAXN][2];

ll n,k;
vector<int>e[MAXN];

ll S[MAXN],cur;
ll T[MAXN],num;

int a[MAXN],b[MAXN];

int sz[MAXN],son[MAXN],fa[MAXN];
int dfn[MAXN],top[MAXN],leaf[MAXN],dtot;

int len[MAXN],dep[MAXN];

ll f[MAXN][2],g[MAXN][2];

int cnt[MAXN],idx[MAXN];

void dfs1(int u){
	sz[u] = 1;
	dep[u] = dep[fa[u]]+1;
	for(auto v:e[u])if(v!=fa[u]){
		fa[v]=u,dfs1(v);
		sz[u] += sz[v];
		if(sz[v] > sz[son[u]])son[u]=v;
	}
}
void dfs2(int u,int node){
	dfn[u]=++dtot;
	top[u]=node;
	if(son[u])dfs2(son[u],node);
	else{
		leaf[node]=u;
		f[u][0] = a[u],f[u][1] = b[u];
		g[u][0] = g[u][1] = 1;
		return;
	}
	f[u][0] = mult(a[u],add(f[son[u]][0],f[son[u]][1]));
	f[u][1] = mult(b[u],f[son[u]][0]);

	g[u][0] = g[u][1] = 1;
	for(auto v:e[u])if(v!=fa[u] && v!=son[u]){
		dfs2(v,v);
		idx[v] = ++cnt[u];
		g[u][0] = mult(g[u][0],f[v][0]);
		g[u][1] = mult(g[u][1],add(f[v][0],f[v][1]));
	}

	f[u][0] = mult(f[u][0],g[u][1]);
	f[u][1] = mult(f[u][1],g[u][0]);

	sG[u][0].init(cnt[u]),sG[u][1].init(cnt[u]);
	for(auto v:e[u])if(v!=fa[u] && v!=son[u]){
		sG[u][0].mdf(1,1,cnt[u],idx[v],f[v][0]);
		sG[u][1].mdf(1,1,cnt[u],idx[v],add(f[v][0],f[v][1]));
	}
}

int IDX(int x){
	return dep[x] - dep[top[x]] + 1;
}

mat GA(int u){
	return (mat){mult(a[u],g[u][1]),mult(b[u],g[u][0]),mult(a[u],g[u][1]),0};
}

vec F(int u){
	int l=leaf[top[u]];
	return (vec){a[l],b[l]} * sF[u].t[1];
}
void mdf(int u,int va,int vb){
	a[u] = va,b[u] = vb;
	if(u!=leaf[top[u]])sF[top[u]].mdf(1,1,len[top[u]]-1,IDX(u),GA(u));
	u=top[u];
	while(u>1){
		vec now=F(u);

		sG[fa[u]][0].mdf(1,1,cnt[fa[u]],idx[u],now[0]);
		sG[fa[u]][1].mdf(1,1,cnt[fa[u]],idx[u],add(now[0],now[1]));
		g[fa[u]][0] = sG[fa[u]][0].qry();
		g[fa[u]][1] = sG[fa[u]][1].qry();
		sF[top[fa[u]]].mdf(1,1,len[top[fa[u]]]-1,IDX(fa[u]),GA(fa[u]));

		u=top[fa[u]];
	}
}

int main(){

	ios::sync_with_stdio(false);
	cin>>n>>k;
	int u[MAXN],v[MAXN];
	rep(i,1,n-1)cin>>u[i],u[i]++;
	rep(i,1,n-1)cin>>v[i],v[i]++;
	rep(i,1,n-1)e[u[i]].push_back(v[i]),e[v[i]].push_back(u[i]);

	cin>>cur;
	rep(i,1,cur)cin>>S[i],S[i]++;
	sort(S+1,S+1+cur);

	rep(i,1,n)a[i]=1,b[i]=0;
	rep(i,1,cur)a[S[i]]=0,b[S[i]]=1;

	dfs1(1);
	dfs2(1,1);

	rep(i,1,n)if(top[i] == i){
		len[i] = dep[leaf[i]] - dep[i] + 1;
		sF[i].init(len[i]);
	}

	rep(i,1,n)if(i!=leaf[top[i]])sF[top[i]].mdf(1,1,len[top[i]]-1,IDX(i),GA(i));
	


	per(i,cur,0){  
		if(i==cur){
			rep(j,S[cur]+1,n)mdf(j,1,1);
		}else{
			mdf(S[i+1],1,0);
			if(i!=cur-1){
				rep(j,S[i+1]+1,S[i+2])mdf(j,1,1);
			}
		}
		vec now=F(1);
		ll ways=add(now[0],now[1]) - 1;
		if(ways<k){
			k-=ways;
			continue;
		}
		int lim=(i==cur) ? (S[cur]+1) : (S[i+1]+1);

		rep(j,1,i)T[++num] = S[j];
		rep(j,lim,n){
			mdf(j,0,1);
			vec now=F(1);
			ll ways=add(now[0],now[1]);
			if(ways < k){
				k-=ways;
				mdf(j,1,0);
				continue;
			}
			T[++num] = j;
			k--;
			if(!k)break;
		}	
		break;
	}

	
	rep(i,1,num)cout<<T[i]-1<<" ";
    return 0;
}