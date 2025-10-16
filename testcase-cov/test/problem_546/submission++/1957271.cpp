#include <bits/stdc++.h>
using namespace std;
const int N=1.1e5+5,M=3.1e5+5,K=(N<<7);
int n,m,k,Q,px[N],py[N],tmpx[M],tmpy[M];
vector<int> xp[M],yp[M],xu[M],yu[M],idx[M],idy[M],lpx[M],lpy[M];
int tot,tp[M],lp[M],rp[M],ps[M];
int rtx[N],rty[N],ls[K],rs[K],ti[K],nwt;
int head[K],to[K],nxt[K],cnt,wi[K],dis[K];bool vis[K];
void add(int u,int v,int w)
{
    if(!u||!v) return;
    to[++cnt]=v,nxt[cnt]=head[u],head[u]=cnt,wi[cnt]=w;
}
inline int newnode(int p=0)
{
    ++tot;ls[tot]=ls[p],rs[tot]=rs[p];return tot;
}
void update(int &p,int nw,int l,int r,int gl,int x)
{
    if(l==r){p=x;return;}
    int mid=l+r>>1;p=newnode(nw),ti[p]=nwt;
    if(gl<=mid) update(ls[p],ls[nw],l,mid,gl,x);
    else update(rs[p],rs[nw],mid+1,r,gl,x);
}
void linkt(int p,int l,int r)
{
    int mid=l+r>>1;if(l==r||ti[p]!=nwt) return;
    if(ls[p]) add(p,ls[p],0),linkt(ls[p],l,mid);
    if(rs[p]) add(p,rs[p],0),linkt(rs[p],mid+1,r);
}
void link(int p,int l,int r,int L,int R,int u)
{
    int mid=l+r>>1; if(!p||L>R) return;
    if(L<=l&&r<=R) return add(u,p,1);
    if(L<=mid) link(ls[p],l,mid,L,R,u);
    if(R>mid) link(rs[p],mid+1,r,L,R,u);
}
inline int getx(int x,int y)
{
    return idx[x][upper_bound(lpx[x].begin(),lpx[x].end(),y)-lpx[x].begin()-1];
}
inline int gety(int x,int y)
{
    return idy[y][upper_bound(lpy[y].begin(),lpy[y].end(),x)-lpy[y].begin()-1];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);cin>>n>>m>>k>>Q;
    for(int i=1;i<=k;i++) cin>>px[i]>>py[i];
    int cx=0,cy=0,sx,sy,stx,sty;cin>>sx>>sy;
    ++k,px[k]=sx,py[k]=sy;
    for(int i=1;i<=k;i++)
    {
        tmpx[++cx]=px[i],tmpy[++cy]=py[i];
        if(px[i]>1) tmpx[++cx]=px[i]-1;
        if(py[i]>1) tmpy[++cy]=py[i]-1;
    }tmpx[++cx]=n,tmpy[++cy]=m;
    sort(tmpx+1,tmpx+cx+1),n=unique(tmpx+1,tmpx+cx+1)-tmpx-1;
    sort(tmpy+1,tmpy+cy+1),m=unique(tmpy+1,tmpy+cy+1)-tmpy-1;
    for(int i=1;i<=k;i++)
    {
        px[i]=lower_bound(tmpx+1,tmpx+n+1,px[i])-tmpx;
        py[i]=lower_bound(tmpy+1,tmpy+m+1,py[i])-tmpy;
        if(i<k) xp[px[i]].push_back(py[i]),yp[py[i]].push_back(px[i]);
    }
    for(int i=1;i<=n;i++)
    {
        int ls=0;sort(xp[i].begin(),xp[i].end());
        for(auto p:xp[i])
        {
            if(p>ls+1) 
            {
                ++tot,tp[tot]=0,lp[tot]=ls+1,rp[tot]=p-1,ps[tot]=i;
                yu[ls+1].push_back(tot),yu[p].push_back(-tot);
                idx[i].push_back(tot);lpx[i].push_back(ls+1);
            }ls=p;
        }
        if(ls<m) 
        {
            ++tot,tp[tot]=0,lp[tot]=ls+1,rp[tot]=m,ps[tot]=i;
            yu[ls+1].push_back(tot),yu[m+1].push_back(-tot);
            idx[i].push_back(tot);lpx[i].push_back(ls+1);
        }
    }
    for(int i=1;i<=m;i++)
    {
        int ls=0;sort(yp[i].begin(),yp[i].end());
        for(auto p:yp[i])
        {
            if(p>ls+1) 
            {
                ++tot,tp[tot]=1,lp[tot]=ls+1,rp[tot]=p-1,ps[tot]=i;
                xu[ls+1].push_back(tot),xu[p].push_back(-tot);
                idy[i].push_back(tot);lpy[i].push_back(ls+1);
            }ls=p;
        }
        if(ls<n) 
        {
            ++tot,tp[tot]=1,lp[tot]=ls+1,rp[tot]=n,ps[tot]=i;
            xu[ls+1].push_back(tot),xu[n+1].push_back(-tot);
            idy[i].push_back(tot);lpy[i].push_back(ls+1);
        }
    }
    for(int i=1;i<=n;i++)
    {
        rtx[i]=rtx[i-1],nwt=i;
        for(auto p:xu[i])
            update(rtx[i],rtx[i],1,m,ps[abs(p)],p<0?0:p);
        linkt(rtx[i],1,m);
        for(auto p:idx[i])
            link(rtx[i],1,m,lp[p],rp[p],p);
    }
    for(int i=1;i<=m;i++)
    {
        rty[i]=rty[i-1],nwt=i;
        for(auto p:yu[i])
            update(rty[i],rty[i],1,n,ps[abs(p)],p<0?0:p);
        linkt(rty[i],1,n);
        for(auto p:idy[i])
            link(rty[i],1,n,lp[p],rp[p],p);
    }stx=getx(px[k],py[k]),sty=gety(px[k],py[k]);
    for(int i=1;i<=tot;i++) dis[i]=-1;
    deque<int> q;dis[stx]=dis[sty]=0;
    q.push_back(stx),q.push_back(sty);
    while(!q.empty())
    {
        int u=q.front();q.pop_front();
        if(vis[u]) continue; vis[u]=1;
        for(int i=head[u];i;i=nxt[i])
        {
            int v=to[i];
            if(dis[v]>dis[u]+wi[i]||dis[v]==-1)
            {
                dis[v]=dis[u]+wi[i];
                if(wi[i]) q.push_back(v);
                else q.push_front(v);
            }
        }
    }
    while(Q--)
    {
        int x,y,xx,yy;cin>>x>>y;
        x=lower_bound(tmpx+1,tmpx+n+1,x)-tmpx;
        y=lower_bound(tmpy+1,tmpy+m+1,y)-tmpy;
        xx=getx(x,y),yy=gety(x,y);
        cout<<min(dis[xx],dis[yy])<<"\n";
    }
    return 0;
}