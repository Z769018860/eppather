




































#pragma GCC optimize(3)
#pragma GCC target("avx")
#pragma GCC target("avx,avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(2)
#include<bits/stdc++.h>

















using namespace std;
#define ll long long
#define int ll
#define pii pair<int,int>
#define vi vector<int>
#define vii vector<pii>
#define pdd pair<double,double>
#define ull unsigned long long
#define pb push_back
#define rep(i,n) for(int i=0;i<(int)(n);++i)
#define all(s) (s).begin(),(s).end()
#define repd(i,n) for(int i=(int)(n)-1;i>=0;--i)
#define forr(i,a,b,c) for(int i=(int)(a);i<=(int)(b);i+=(int)(c))
#define forn(i,p,n) for(int i=(int)(p);i<=(int)(n);++i)
#define ford(i,p,n) for(int i=(int)(n);i>=(int)(p);--i)
#define foreach(i,c) for(__typeof(c.begin())i=(c.begin());i!=(c).end();++i)
#define PI acos(-1)
#define Endl(x) cout<<x<<endl;
#define Blank(x) cout<<x<<" ";
#define modcg(x) if(x>=mod)x-=mod;
#define modcl(x) if(x<0)x+=mod;
#define lowbit(x) x&(-x)
string int_to_string(ll n)
{
	string s="";
	while(n)
	{
		ll now=n%10;
		s+=now+'0';
		n/=10;
	}
	reverse(s.begin(),s.end());
	return s;
}
ll string_to_int(string s)
{
	ll n=0;
	rep(i,s.size())
	{
		n*=10;
		n+=s[i]-'0';
	}
	return n;
}
mt19937 GeN(chrono::system_clock::now().time_since_epoch().count());
int Rand(int l,int r)
{
	uniform_int_distribution<>RAND1(l,r);
	return RAND1(GeN);
}
struct Fastmod
{
	int mod,b;
	typedef __int128 lll;
	void init(int m)
	{
		mod=m;
		b=((lll)1<<64)/mod;
	}
	int operator()(ull a)
	{
		int q=((lll)a*b)>>64,r=a-q*mod;
		modcg(r);
		return r;
	}
}MOD;
int mul(int a,int b)
{
	return MOD(a*b);
}
const int dx[]={-1,0,1,0};
const int dy[]={0,-1,0,1};
const int month[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};


const int MAXN=1e6+10,INF=2e18;
int Mul(int x,int y)
{
	if(y&&x>INF/y)
	{
		return INF;	
	} 
	return x*y;
}
struct matrix
{
	int a[2][2];
	void init()
	{
		rep(i,2)
		{
			rep(j,2)
			{
				a[i][j]=0;
			}
		}
	}
	matrix operator*(const matrix &M)const
	{
		matrix N;
		N.init();
		rep(i,2)
		{
			rep(j,2)
			{
				rep(k,2)
				{
					N.a[i][j]+=Mul(a[i][k],M.a[k][j]);
					N.a[i][j]=min(N.a[i][j],INF);
				}
			}
		}
		return N;
	}
	matrix operator^(const matrix &M)const
	{
		matrix N;
		rep(i,2)
		{
			rep(j,2)
			{
				N.a[i][j]=a[i][j]*M.a[i][j];
			}
		}
		return N;
	}
	void output()
	{
		cout<<"matrix"<<endl; 
		rep(i,2)
		{
			rep(j,2)
			{
				cout<<a[i][j]<<" ";
			}
			cout<<endl; 
		}
	}
}M[3],I;
void init()
{
	rep(i,3)
	{
		M[i].init();
	}
	I.init();
	rep(i,2)
	{
		I.a[i][i]=1;
		rep(j,2)
		{
			M[2].a[i][j]=1;
		}
	}

	M[2].a[1][1]=0;
	M[0]=M[1]=M[2];
	rep(i,2)
	{
		rep(j,2)
		{
			M[i^1].a[j][i]=0;
		}
	}






}
struct node
{
	int ls=0,rs=0;
	matrix val;
};
struct SegT
{
	node seg[MAXN<<2];	
	int head;
	void push_up(int now)
	{
		seg[now].val=seg[seg[now].ls].val*seg[seg[now].rs].val;	
	} 
	void build(int &now,int l,int r)
	{
		if(!now)
		{
			now=++head;
		}
		if(l==r)
		{
			seg[now].val=I;
			return;
		}
		int mid=(l+r)>>1;
		build(seg[now].ls,l,mid);
		build(seg[now].rs,mid+1,r);
		push_up(now);
	} 
	void update(int &now,int l,int r,int down,matrix val)
	{
		if(!now)
		{
			now=++head;
		}

		if(l==r)
		{
			seg[now].val=val;

			return;
		}
		int mid=(l+r)>>1;
		if(down<=mid)
		{
			update(seg[now].ls,l,mid,down,val);
		}
		else
		{
			update(seg[now].rs,mid+1,r,down,val);
		}
		push_up(now);
	}
}T;
vi v[MAXN];
int dep[MAXN];
int fa[MAXN];
int sz[MAXN];
int son[MAXN];
void dfs1(int now)
{
	dep[now]=dep[fa[now]]+1;
	sz[now]=1;
	for(int u:v[now])
	{
		if(u==fa[now])
		{
			continue;
		}
		fa[u]=now;
		dfs1(u);
		sz[now]+=sz[u];
		if(sz[u]>sz[son[now]])
		{
			son[now]=u;
		}
	}
}
int top[MAXN];
int len1[MAXN],len2[MAXN];
int down1[MAXN],down2[MAXN];
void dfs2(int now)
{
	if(son[now])
	{
		top[son[now]]=top[now];
		dfs2(son[now]);
	}
	down2[now]=dep[now]-dep[top[now]]+1;
	len2[top[now]]++;
	int cnt=0;
	for(int u:v[now])
	{
		if(u==fa[now]||u==son[now])
		{
			continue;
		}
		top[u]=u;
		down1[u]=++cnt;
		len1[now]++;
		dfs2(u);
	}
}
int root1[MAXN],root2[MAXN];
matrix N;
int n,k,m;
int s[MAXN];
int ban[MAXN];
void dfs(int now)
{

	for(int u:v[now])
	{
		if(u==fa[now])
		{
			continue;
		}
		dfs(u);
	}
	N.init();
	N.a[0][0]=N.a[1][0]=T.seg[root1[now]].val.a[1][1];
	N.a[0][1]=N.a[1][1]=T.seg[root1[now]].val.a[0][0];
	N=N^M[ban[now]];






	T.update(root2[top[now]],1,len2[top[now]],down2[now],N);

	if(fa[now]&&now==top[now])
	{
		N.init();
		N.a[0][0]=T.seg[root2[now]].val.a[0][0];
		N.a[1][1]=T.seg[root2[now]].val.a[0][1]+N.a[0][0];
		N.a[1][1]=min(N.a[1][1],INF);




		T.update(root1[fa[now]],1,len1[fa[now]],down1[now],N);



	}	

}
void update(int now,int val)
{
	ban[now]=val;
	N.init();
	N.a[0][0]=N.a[1][0]=T.seg[root1[now]].val.a[1][1];
	N.a[0][1]=N.a[1][1]=T.seg[root1[now]].val.a[0][0];
	N=N^M[ban[now]];
	T.update(root2[top[now]],1,len2[top[now]],down2[now],N);
	now=top[now];
	while(fa[now])
	{
		N.init();
		N.a[0][0]=T.seg[root2[now]].val.a[0][0];
		N.a[1][1]=T.seg[root2[now]].val.a[0][1]+N.a[0][0];
		N.a[1][1]=min(N.a[1][1],INF);
		T.update(root1[fa[now]],1,len1[fa[now]],down1[now],N);
		now=fa[now];
		N.init();
		N.a[0][0]=N.a[1][0]=T.seg[root1[now]].val.a[1][1];
		N.a[0][1]=N.a[1][1]=T.seg[root1[now]].val.a[0][0];
		N=N^M[ban[now]];
		T.update(root2[top[now]],1,len2[top[now]],down2[now],N);
		now=top[now];
	}	
}
int qurey()
{

	return min(T.seg[root2[1]].val.a[0][1]+T.seg[root2[1]].val.a[0][0],INF);
}
void solve()
{
	init();
	cin>>n>>k;
	vi x(n-1),y(n-1);
	rep(i,n-1)
	{
		cin>>x[i];
	}
	rep(i,n-1)
	{
		cin>>y[i];
	}
	rep(i,n-1)
	{
		x[i]++,y[i]++;
		v[x[i]].pb(y[i]);
		v[y[i]].pb(x[i]);
	}
	dfs1(1);
	top[1]=1;
	dfs2(1);
	T.seg[0].val=I;





	cin>>m;
	forn(i,1,n)
	{
		ban[i]=2;
		down2[i]=len2[top[i]]-down2[i]+1;
	}
	forn(i,1,m)
	{
		cin>>s[i];
		s[i]++;
		ban[s[i]]=1;
	}
	sort(s+1,s+1+m); 
	rep(i,m)
	{
		forn(j,s[i]+1,s[i+1]-1)
		{
			ban[j]=0;
		}
	}





	forn(i,1,n)
	{
		if(len1[i])
		{
			T.build(root1[i],1,len1[i]);

		}
		if(len2[i])
		{
			T.build(root2[i],1,len2[i]);
		}
	}

	dfs(1);

	ford(i,0,m)
	{
		int val=qurey()-1;







		if(val>=k)
		{
			m=i;
			break;
		}
		else
		{
			if(i)
			{
				k-=val;
				update(s[i],0);
				if(i<m)
				{
					forn(j,s[i]+1,s[i+1])
					{
						update(j,2);
					}
				}
			}
			else
			{
				return;
			}
		}
	}






	forn(j,1,n)
	{
		if(ban[j]!=2)
		{
			continue;
		}
		k--;
		update(j,1);
		int val=qurey()-1;


		if(k<=val)
		{
			s[++m]=j;
		}
		else
		{
			k-=val;
			update(j,0);
		}
		if(!k)
		{
			break;
		}
	}
	forn(i,1,m)
	{
		cout<<s[i]-1<<" ";
	}
	cout<<endl;
}
signed main()
{
    cin.tie(0);
    cout.tie(0);
	std::ios::sync_with_stdio(false);

#ifdef Hank2007
	freopen("41.in","r",stdin);

#endif
  	  	int TEST_CASE=1;

  	while(TEST_CASE--)
  	{
  		solve();
  	}
  	return 0;
}
