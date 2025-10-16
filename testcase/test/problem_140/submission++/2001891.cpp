#include<cstdio>
#include<algorithm>
const int N=107,M=10007+N;typedef long long ll;
int ls[M],rs[M],vl[M],tg[M],ds[M],pr[M];
int rt[N*2],fa[N*2],vc;int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
inline void tadd(int x,int v){vl[x]+=v;tg[x]+=v;}
inline void push(int x){if(tg[x])tadd(ls[x],tg[x]),tadd(rs[x],tg[x]),tg[x]=0;}
int merge(int x,int y)
{
	if(!x||!y)return x|y;
	if(vl[x]>vl[y])std::swap(x,y);push(x);rs[x]=merge(rs[x],y);
	if(ds[rs[x]]>ds[ls[x]])std::swap(ls[x],rs[x]);ds[x]=ds[rs[x]]+1;return x;
}
inline int dels(int x){push(x);return merge(ls[x],rs[x]);}
int sta[N],tp;bool via[N*2];
int sol(int r)
{
	int ans=0;sta[++tp]=r;via[r]=1;
	while(rt[sta[tp]])
	{
		int v=sta[tp],e=rt[v],u=find(pr[e]);
		if(u==v){rt[v]=dels(e);continue;}
		if(!via[u]){sta[++tp]=u;via[u]=1;continue;}
		int p=++vc;fa[p]=p;
		while(via[u])
		{
			int i=sta[tp--];via[i]=0;
			int vlt=vl[rt[i]];tadd(rt[i],-vlt);rt[p]=merge(rt[p],dels(rt[i]));
			if(find(i)!=find(r)){if(vlt>1e6)return -1;ans+=vlt;}
			fa[i]=p;
		}
		sta[++tp]=p;via[p]=1;
	}
	return ans;
}
int main()
{
	int n,m,r,x;scanf("%d%d%d",&n,&m,&r);vc=n;
	for(int i=1;i<=n;++i)pr[i]=(i==1?n:i-1),vl[i]=1e9,rt[i]=fa[i]=i;
	for(int i=1;i<=m;++i)scanf("%d%d%d",pr+n+i,&x,vl+n+i),rt[x]=merge(rt[x],n+i);
	printf("%d",sol(r));
	return 0;
}