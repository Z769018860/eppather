#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
#include<queue>
const int K=50007,V=50*K,E=298*K,N=22*K;



int cx[K],cy[K],cxs[K],xs[K*2],xfi[K*2],ys[K*2],yfi[K*2],xc,yc;
std::vector<int> xv[K*2],yv[K*2];
int hd[V][2],nx[E],vx[E],ds[V],ec,pv;bool vs[V];
inline void add(int u,int v,bool t){nx[++ec]=hd[u][t];vx[ec]=v;hd[u][t]=ec;}
inline void zadd(int u,int v){add(u+pv,v+pv,0);}
int ls[N],rs[N],T0,tc;
inline void badd(int x,int s){zadd(x<<1,s<<1);zadd(s<<1|1,x<<1|1);}
inline void bedd(int x){badd(x,ls[x]);badd(x,rs[x]);}
const auto&cmpx=[](int p,int q){return cx[p]<cx[q];};
const auto&cmpy=[](int p,int q){return cy[p]<cy[q];};
void build(int l,int r,int&k)
{
	k=++tc;if(l==r){add((k<<1)+pv,xfi[l],1);add(xfi[l],(k<<1|1)+pv,1);return;}
	int mid=(l+r)>>1;build(l,mid,ls[k]);build(mid+1,r,rs[k]);bedd(k);
}
void qry(int p,int L,int R,int l,int r,int k)
{
	if(L<=l&&r<=R)return add(p,(k<<1)+pv,0),add((k<<1|1)+pv,p,0);
	int mid=(l+r)>>1;
	if(L<=mid)qry(p,L,R,l,mid,ls[k]);
	if(R>mid)qry(p,L,R,mid+1,r,rs[k]);
}
void upd(int p,int v,int l,int r,int&k)
{
	ls[++tc]=ls[k];rs[tc]=rs[k];k=tc;if(l==r){add((k<<1)+pv,v,1);add(v,(k<<1|1)+pv,1);return;}
	int mid=(l+r)>>1;if(p<=mid)upd(p,v,l,mid,ls[k]);else upd(p,v,mid+1,r,rs[k]);bedd(k);
}
void cons(int sx,int sy,int&A0,int&A1)
{
	cx[50001]=sx=std::upper_bound(xs+1,xs+xc+1,sx)-xs-1;
	cy[50001]=sy=std::upper_bound(ys+1,ys+yc+1,sy)-ys-1;
	A0=xfi[sx]+std::lower_bound(xv[sx].begin(),xv[sx].end(),50001,cmpy)-xv[sx].begin();
	A1=yfi[sy]+std::lower_bound(yv[sy].begin(),yv[sy].end(),50001,cmpx)-yv[sy].begin();
}
inline void prt(int x){printf("%d\n",x>=1e9?-1:x);}
int main()
{


	int n,m,k,q,sx,sy,A0,A1;
	scanf("%d%d%d%d",&n,&m,&k,&q);
	xs[++xc]=1;ys[++yc]=1;
	for(int i=1;i<=k;++i)
	{
		scanf("%d%d",cx+i,cy+i);
		xs[++xc]=cx[i];if(cx[i]<n)xs[++xc]=cx[i]+1;
		ys[++yc]=cy[i];if(cy[i]<m)ys[++yc]=cy[i]+1;
	}
	scanf("%d%d",&sx,&sy);xs[++xc]=sx;ys[++yc]=sy;if(sx<n)xs[++xc]=sx+1;if(sy<m)ys[++yc]=sy+1;
	std::sort(xs+1,xs+xc+1);xc=std::unique(xs+1,xs+xc+1)-xs-1;
	std::sort(ys+1,ys+yc+1);yc=std::unique(ys+1,ys+yc+1)-ys-1;
	for(int i=1;i<=k;++i)
	{
		cx[i]=std::lower_bound(xs+1,xs+xc+1,cx[i])-xs;
		cy[i]=std::lower_bound(ys+1,ys+yc+1,cy[i])-ys;
		xv[cx[i]].push_back(i);yv[cy[i]].push_back(i);
	}
	for(int i=1;i<=xc;++i)
	{
		std::sort(xv[i].begin(),xv[i].end(),cmpy);
		for(int j=0;j<xv[i].size();++j)cxs[xv[i][j]]=j;
	}
	for(int i=1;i<=yc;++i)std::sort(yv[i].begin(),yv[i].end(),cmpx);
	xfi[1]=1;for(int i=1;i<=xc;++i)xfi[i+1]=xfi[i]+xv[i].size()+1;
	yfi[1]=xfi[xc+1];for(int i=1;i<=yc;++i)yfi[i+1]=yfi[i]+yv[i].size()+1;
	pv=yfi[yc+1]-2;build(1,xc,T0);
	for(int i=1;i<=yc;++i)
	{
		int sz=yv[i].size();
		for(int j=0,lm=1,rm;j<=sz;++j,lm=rm+2)
		{
			int p=(j==sz?xc+1:cx[yv[i][j]]);rm=p-1;

			if(lm<=rm)qry(yfi[i]+j,lm,rm,1,xc,T0);
			if(j<sz)upd(p,xfi[p]+cxs[yv[i][j]]+1,1,xc,T0);
		}

	}

	memset(ds,0x3f,sizeof ds);cons(sx,sy,A0,A1);
	std::deque<int> que;que.push_back(A0);que.push_back(A1);
	ds[A0]=ds[A1]=0;while(!que.empty())
	{
		int i=que.front();que.pop_front();if(vs[i])continue;vs[i]=1;
		for(int t=hd[i][0],v;t;t=nx[t])if(ds[v=vx[t]]>ds[i])ds[v]=ds[i],que.push_front(v);
		for(int t=hd[i][1],v;t;t=nx[t])if(ds[v=vx[t]]>ds[i]+1)ds[v]=ds[i]+1,que.push_back(v);
	}
	while(q--)scanf("%d%d",&sx,&sy),cons(sx,sy,A0,A1),prt(std::min(ds[A0],ds[A1]));
	return 0;
}