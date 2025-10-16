
#include<iostream>
#include<deque>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
namespace lly
{
    constexpr int N=5e4+5,inf=1e9;
    int bx[N<<1],by[N<<1],tx=0,ty=0;
    struct pt{int x,y;}a[N];
    vector<int>pposx[N<<1],pposy[N<<1],pidx[N<<1],pidy[N<<1],plx[N<<1],ply[N<<1],xau[N<<1],xdu[N<<1],yau[N<<1],ydu[N<<1];
    struct line{int tp,pos,l,r;}ll[N*12];
    struct edge{int to,nxt,w;}e[N<<8];
    int head[N<<8],cnt=0,tot=0,dis[N<<8];bool vis[N<<8];
    inline void add(int u,int v,int w){if(u&&v) e[++cnt]=(edge){v,head[u],w},head[u]=cnt;}
    namespace prt
    {
        struct node{int lson,rson,id;}tree[N<<8];
        #define now tree[ro]
        #define lsc now.lson
        #define rsc now.rson
        inline void update(int&ro,int pre,int l,int r,int p,int x,int id)
        {
            if(l==r) return ro=x,void();
            ro=++tot;now=tree[pre];now.id=id;
            int mid=(l+r)>>1;
            if(p<=mid) update(lsc,tree[ro].lson,l,mid,p,x,id);
            else update(rsc,tree[ro].rson,mid+1,r,p,x,id);
        }
        inline void link(int ro,int l,int r,int ql,int qr,int p)
        {
            if(!ro||ql>qr) return;
            if(ql<=l&&r<=qr) return add(p,ro,1);
            int mid=(l+r)>>1;
            if(ql<=mid) link(lsc,l,mid,ql,qr,p);
            if(qr>mid) link(rsc,mid+1,r,ql,qr,p);
        }
        inline void link(int ro,int l,int r,int id)
        {
            if(!ro||now.id!=id) return;
            int mid=(l+r)>>1;
            add(ro,now.lson,0);add(ro,now.rson,0);
            link(lsc,l,mid,id);link(rsc,mid+1,r,id);
        }
    }
    int rootx[N<<1],rooty[N<<1];
    inline int getx(int x,int y){return pidx[x][upper_bound(plx[x].begin(),plx[x].end(),y)-plx[x].begin()-1];}
    inline int gety(int x,int y){return pidy[y][upper_bound(ply[y].begin(),ply[y].end(),x)-ply[y].begin()-1];}
    inline void work()
    {
        ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
        int n,m,_k,_q;cin>>n>>m>>_k>>_q;
        for(int i=1;i<=_k+1;i++)
        {
            int x,y;cin>>x>>y;
            bx[++tx]=x;by[++ty]=y;
            if(x-1) bx[++tx]=x-1;
            if(y-1) by[++ty]=y-1;
            a[i%(_k+1)]=(pt){x,y};
        }
        bx[++tx]=n;by[++ty]=m;
        sort(bx+1,bx+tx+1);sort(by+1,by+ty+1);
        n=tx=static_cast<int>(unique(bx+1,bx+tx+1)-bx-1);
        m=ty=static_cast<int>(unique(by+1,by+ty+1)-by-1);
        for(int i=0;i<=_k;i++)
            a[i].x=static_cast<int>(lower_bound(bx+1,bx+n+1,a[i].x)-bx),
            a[i].y=static_cast<int>(lower_bound(by+1,by+ty+1,a[i].y)-by);
        for(int i=1;i<=n;i++) pposx[i].push_back(0),pposx[i].push_back(m+1);
        for(int i=1;i<=m;i++) pposy[i].push_back(0),pposy[i].push_back(n+1);
        for(int i=1;i<=_k;i++) pposx[a[i].x].push_back(a[i].y),pposy[a[i].y].push_back(a[i].x);
        for(int i=1;i<=n;i++)
        {
            sort(pposx[i].begin(),pposx[i].end());
            for(int j=1;j<static_cast<int>(pposx[i].size());j++)
            {
                if(pposx[i][j]<=pposx[i][j-1]+1) continue;
                int l=pposx[i][j-1]+1,r=pposx[i][j]-1;
                ++tot;pidx[i].push_back(++tot);plx[i].push_back(l);
                ll[tot]=(line){0,i,l,r};
                yau[l].push_back(tot);ydu[r+1].push_back(tot);
            }
        }
        for(int i=1;i<=m;i++)
        {
            sort(pposy[i].begin(),pposy[i].end());
            for(int j=1;j<static_cast<int>(pposy[i].size());j++)
            {
                if(pposy[i][j]<=pposy[i][j-1]+1) continue;
                int l=pposy[i][j-1]+1,r=pposy[i][j]-1;
                ++tot;pidy[i].push_back(++tot);ply[i].push_back(l);
                ll[tot]=(line){1,i,l,r};
                xau[l].push_back(tot);xdu[r+1].push_back(tot);
            }
        }
        
        for(int i=1;i<=n;i++)
        {
            rootx[i]=rootx[i-1];
            for(const int j:xdu[i]) prt::update(rootx[i],rootx[i],1,m,ll[j].pos,0,i);
            for(const int j:xau[i]) prt::update(rootx[i],rootx[i],1,m,ll[j].pos,j,i);
            prt::link(rootx[i],1,m,i);
            for(const int j:pidx[i]) prt::link(rootx[i],1,m,ll[j].l,ll[j].r,j);
        }
        for(int i=1;i<=m;i++)
        {
            rooty[i]=rooty[i-1];
            for(const int j:ydu[i]) prt::update(rooty[i],rooty[i],1,n,ll[j].pos,0,i);
            for(const int j:yau[i]) prt::update(rooty[i],rooty[i],1,n,ll[j].pos,j,i);
            prt::link(rooty[i],1,n,i);
            for(const int j:pidy[i]) prt::link(rooty[i],1,n,ll[j].l,ll[j].r,j);
        }
        int s1=getx(a[0].x,a[0].y),s2=gety(a[0].x,a[0].y);
        memset(dis,0x3f,sizeof(dis));dis[s1]=dis[s2]=0;
        deque<int>q;q.push_back(s1);q.push_back(s2);
        while(!q.empty())
        {
            int u=q.front();q.pop_front();
            if(vis[u]) continue;
            vis[u]=true;
            for(int i=head[u];i;i=e[i].nxt)
            {
                int v=e[i].to;if(dis[v]<=dis[u]+e[i].w) continue;
                dis[v]=dis[u]+e[i].w;
                if(e[i].w) q.push_back(v);
                else q.push_front(v);
            }
        }
        while(_q--)
        {
            int rx,ry,vx,vy;cin>>rx>>ry;
            rx=static_cast<int>(lower_bound(bx+1,bx+n+1,rx)-bx);
            ry=static_cast<int>(lower_bound(by+1,by+m+1,ry)-by);
            vx=getx(rx,ry),vy=gety(rx,ry);int ans=min(dis[vx],dis[vy]);
            cout<<(ans>inf?-1:ans)<<"\n";
        }
    }
}
int main()
{
    #ifdef llydebug
    freopen(".in","r",stdin);
    #endif
    lly::work();
    return 0;
}