#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>
const int N=1e6+7;
typedef long long ll;
std::vector<int> to[N];
int U[N],V[N],cnt[N],s[N],n;
ll k;char st[N];std::set<int> r;
inline void adp(int x){if(!cnt[x]++)r.erase(x);}
inline void dlp(int x){if(!--cnt[x])r.insert(x);}
inline void del(int x){if(st[x]!=2)dlp(x);if(st[x]==1)for(int v:to[x])dlp(v);}
inline void chg(int x,char w,bool dl=1)
{
	if(dl)del(x);st[x]=w;if(w!=2)adp(x);
	if(w==1)for(int v:to[x])adp(v);
}
ll f[N][2];bool vis[N];
inline ll mul(ll x,ll y){return (__int128)x*y>k?k+1:x*y;}
void dfs(int i,int l)
{

	f[i][0]=f[i][1]=vis[i]=1;
	for(int v:r)if(v!=l&&std::find(
		to[i].begin(),to[i].end(),v)!=to[i].end())

		dfs(v,i),f[i][1]=mul(f[i][1],f[v][0]),
		f[i][0]=mul(f[i][0],f[v][0]+f[v][1]);
}
ll dp()
{
	if(r.size()>=120)return k+1;ll ans=1;


	for(int v:r)if(!vis[v])dfs(v,0),ans=mul(ans,f[v][0]+f[v][1]);
	for(int v:r)vis[v]=0;

	return ans;
}
int gtpr(int m)
{
	if(!m)return 0;
	ll rea=0;int pr=m;
	if((rea=dp()-1)>=k)return m;
	else k-=rea;
	for(;pr;--pr)
	{
		chg(s[pr],0);
		for(int j=s[pr]+1;j<=s[pr+1];++j)chg(j,2);
		if((rea=dp()-1)>=k)return pr-1;
		else k-=rea;
	}
	return -1;
}
int main()
{
	scanf("%d%lld",&n,&k);ll rea=0;
	for(int i=1;i<n;++i)scanf("%d",U+i);for(int i=1;i<n;++i)scanf("%d",V+i);
	for(int i=1;i<n;++i)to[++U[i]].push_back(++V[i]),to[V[i]].push_back(U[i]);
	for(int i=1;i<=n;++i)r.insert(i),std::sort(to[i].begin(),to[i].end());
	int m;scanf("%d",&m);for(int i=1;i<=m;++i)scanf("%d",s+i),chg(++s[i],1,0);std::sort(s+1,s+m+1);
	for(int i=s[m]+1;i<=n;++i)st[i]=2;for(int i=0;i<m;++i)for(int j=s[i]+1;j<s[i+1];++j)chg(j,0,0);
	int pr=gtpr(m);if(pr==-1)return 0;s[m+1]=s[m];

	for(int i=s[pr+1]+1;i<=n;++i)
	{

		if(!k)break;if(cnt[i]){chg(i,0);continue;}
		if((chg(i,1),rea=dp())<k)k-=rea,chg(i,0);
		else --k;
	}
	for(int i=1;i<=n;++i)if(st[i]==1)printf("%d ",i-1);
	return 0;
}