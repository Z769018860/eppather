#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define pi pair<Line,ll>
#define mkp make_pair
#define fr first
#define sc second
const ll INF=3e18;
const int N=2e5+5;
struct Line
{
    ll k,b;int id;
}arr[N];
pi getl(Line p,Line q)
{
    if(p.b<q.b||(p.b==q.b&&p.k<q.k)) swap(p,q);
    if(p.k>=q.k) return mkp(p,INF);
    return mkp(p,(p.b-q.b)/(q.k-p.k));
}
struct node
{
    Line ans;ll x;
    node operator+(node p)
    {
        node r;r.x=min(x,p.x);pi t=getl(ans,p.ans);
        r.x=min(r.x,t.sc),r.ans=t.fr;return r;
    }
}a[N<<2];
ll tag[N<<2];
#define ls (p<<1)
#define rs (p<<1|1)
inline void pushup(int p){a[p]=a[ls]+a[rs];}
void build(int p,int l,int r)
{
    if(l==r){a[p].ans=arr[l],a[p].x=INF;return;}
    int mid=l+r>>1;build(ls,l,mid),build(rs,mid+1,r),pushup(p);
}
inline void pushtag(int p,ll t){a[p].x-=t,a[p].ans.b+=a[p].ans.k*t,tag[p]+=t;}
void upd(int p,ll t)
{
    if(a[p].x>=t) return pushtag(p,t);
    t+=tag[p],tag[p]=0;
    upd(ls,t),upd(rs,t),pushup(p);
}
inline void pushdown(int p)
{
    if(!tag[p]) return;
    pushtag(ls,tag[p]),pushtag(rs,tag[p]),tag[p]=0;
}
void update(int p,int l,int r,int L,int R,ll v)
{
    if(L<=l&&r<=R) return upd(p,v);
    int mid=l+r>>1;pushdown(p);
    if(L<=mid) update(ls,l,mid,L,R,v);
    if(R>mid) update(rs,mid+1,r,L,R,v);
    pushup(p);
}
node query(int p,int l,int r,int L,int R)
{
    if(L<=l&&r<=R) return a[p];
    int mid=l+r>>1;pushdown(p);
    if(R<=mid) return query(ls,l,mid,L,R);
    if(L>mid) return query(rs,mid+1,r,L,R);
    return query(ls,l,mid,L,R)+query(rs,mid+1,r,L,R);
}
void upd(int p,int l,int r,int gl,Line x)
{
    if(l==r){a[p].ans=x;return;}
    int mid=l+r>>1;pushdown(p);
    if(gl<=mid) upd(ls,l,mid,gl,x);
    else upd(rs,mid+1,r,gl,x);
    pushup(p);
}
int n,Q;
struct qu
{
    int p,l,r;ll w;
    inline bool operator<(qu p)const
    {
        return w<p.w;
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);cin>>n>>Q;
    for(int i=1;i<=n;i++) cin>>arr[i].k;
    for(int i=1;i<=n;i++) cin>>arr[i].b;
    for(int i=1;i<=n;i++) arr[i].id=i;
    build(1,1,n);
    while(Q--)
    {
        int op;cin>>op;
        if(op==1)
        {
            ll x;cin>>x;update(1,1,n,1,n,x);
        }
        if(op==2)
        {
            int l,r,k;cin>>l>>r>>k;
            priority_queue<qu> pq;
            node nw=query(1,1,n,l,r);ll ans=0;
            pq.push({nw.ans.id,l,r,nw.ans.b});
            while(k--)
            {
                qu nw=pq.top();pq.pop();ans=nw.w;
                if(nw.p>nw.l) 
                {
                    node nx=query(1,1,n,nw.l,nw.p-1);
                    pq.push({nx.ans.id,nw.l,nw.p-1,nx.ans.b});
                }
                if(nw.p<nw.r)
                {
                    node nx=query(1,1,n,nw.p+1,nw.r);
                    pq.push({nx.ans.id,nw.p+1,nw.r,nx.ans.b});
                }
            }cout<<ans<<"\n";
        }
        if(op==3)
        {
            Line x;cin>>x.id>>x.k>>x.b;
            upd(1,1,n,x.id,x);
        }
    }
    return 0;
}