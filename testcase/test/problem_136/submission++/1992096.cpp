#include <bits/stdc++.h>
#define ll long long
#define rll register ll
#define cll const ll
#define N 200005
using namespace std;
inline ll read()
{
    rll x=0;bool f=1;register char c=getchar();
    while(c<48||c>57){if(c=='-') f=0;c=getchar();}
    while(c>=48&&c<=57){x=x*10+(c^48);c=getchar();}
    return f?x:-x;
}
inline void write(ll x)
{
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+48);
}
ll n=read(),m=read(),k=read(),ts,idx,d[N],f[N],s[N],w[N],v[N],h[N],ne[N],ft[N],to[N],son[N],top[N];
bitset<N> vis;
struct edge{ll x,y,z;}e[N];
inline bool cmp(edge x,edge y){return x.z<y.z;}
inline ll find(ll x)
{
	if(x==f[x]) return x;
	return f[x]=find(f[x]);
}
inline void add(ll x,ll y){v[++idx]=y,ne[idx]=h[x],h[x]=idx;}
inline void dfs1(ll x)
{
	s[x]=1,vis[x]=1;
	for(rll i=h[x];~i;i=ne[i])
	{
		cll y=v[i];
		if(y==ft[x]) continue;
		ft[y]=x,d[y]=d[x]+1;
		dfs1(y),s[x]+=s[y];
		if(s[y]>s[son[x]]) son[x]=y;
	}
}
inline void dfs2(ll x,ll tp)
{
	top[x]=tp;
	if(son[x]) dfs2(son[x],tp);
	for(rll i=h[x];~i;i=ne[i])
	{
		cll y=v[i];
		if(y!=ft[x]&&y!=son[x]) dfs2(y,y);
	}
}
inline ll LCA(ll x,ll y)
{
	while(top[x]!=top[y])
	{
		if(!x||!y) return 0;
		if(d[top[x]]>d[top[y]]) x=ft[top[x]];
		else y=ft[top[y]];
	}
	if(d[x]>d[y]) swap(x,y);
	return x;
}
int main()
{
	memset(h,-1,sizeof h);
	memset(w,-0x3f,sizeof w);
	for(rll i=1;i<=n+m;i++) f[i]=i;
    for(rll i=1;i<=m;i++)
    	e[i].x=read(),e[i].y=read(),e[i].z=read();
    sort(e+1,e+m+1,cmp);
    for(rll i=1,x,y;i<=m;i++)
    {
    	x=find(e[i].x),y=find(e[i].y);
    	if(x!=y)
    	{
    		w[++n]=e[i].z;
    		add(n,x),add(x,n);
    		add(n,y),add(y,n);
    		f[x]=f[y]=n;
		}
	}
	for(rll i=n;i>=1;i--)
		if(!vis[i])
			dfs1(i),dfs2(i,i);
	while(k--)
	{
		cll s=read(),t=read(),ans=w[LCA(s,t)];
		
		if(ans<=-1e18) puts("-1");
		else write(ans),putchar('\n');
	}
    return 0;
}