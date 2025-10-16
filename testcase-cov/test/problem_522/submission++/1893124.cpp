#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=3e5+5;
const int M=5e6+5;
const int mod=998244353;
struct node
{
	int xi,ri,vi,id;
	bool operator<(const node &b)const{return xi<b.xi;}
}s[N];
struct did
{
	int to,next;
}e[2*M];
int n,h[N],cnt,dp[N],d[N],rez[N],ans[N];
int fqr[N];
vector<int>v[N];
priority_queue<int>q;
void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].next=h[x];
	h[x]=cnt;
}
void build_graph()
{
	for(int i=1;i<=n;i++)
	{
		int kong=i-1;
		while(kong>=1&&s[kong].xi>=s[i].xi-s[i].ri)
		{

			kong--;
		}
		++kong;
		
		for(int j=kong;j<=i-1;j++)add(j,i),d[j]++,v[i].push_back(j);
		kong=i+1;
		while(kong<=n&&s[kong].xi<=s[i].xi+s[i].ri)kong++;
		--kong;
		
		for(int j=i+1;j<=kong;j++)add(j,i),d[j]++,v[i].push_back(j);
	}
}
int work(int x,int y)
{
	return ((x^y)%mod+x*y%mod)%mod;
}
void dfs(int x,int kong)
{
	if(fqr[x]==kong)return ;
	fqr[x]=kong;
	if(kong!=x)dp[kong]=max(dp[kong],dp[x]+work(s[x].vi,s[kong].vi));
	for(int i=h[x];i;i=e[i].next)
	{
		int y=e[i].to;
		
		dfs(y,kong);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);cout.tie(NULL);
	#ifdef LOCAL
    freopen("test.in", "r", stdin);
    freopen("test.out", "w", stdout);
    #endif
	cin>>n;
	for(int i=1;i<=n;i++)cin>>s[i].xi,s[i].id=i;
	for(int i=1;i<=n;i++)cin>>s[i].ri;
	for(int i=1;i<=n;i++)cin>>s[i].vi;
	sort(s+1,s+1+n);
	build_graph();
	
	
	for(int i=1;i<=n;i++)if(!d[i])q.push(i);
	while(!q.empty())
	{
		int x=q.top();
		q.pop();
		dfs(x,x);
		ans[s[x].id]=dp[x];
		for(int i=0;i<v[x].size();i++)
		{
			int y=v[x][i];
			d[y]--;
			if(!d[y])q.push(y);
		}
	}
	for(int i=1;i<=n;i++)cout<<ans[i]<<'\n';
	return 0;
}
