
#include<iostream>
#include<queue>
using namespace std;
namespace lly
{
    constexpr int N=2e5+5;using ll=long long;constexpr ll inf=1e18;
    struct{int k;ll b;}a[N];
    struct line{int id,k;ll b;line()=default;line(int _id):id(_id),k(a[id].k),b(a[id].b){}};
    struct dat{line x;ll y;dat()=default;dat(int id):x(id),y(inf){}};
    inline dat operator+(dat x,dat y)
    {
        dat res;res.y=min(x.y,y.y);
        if(x.x.k<y.x.k||(x.x.k==y.x.k&&(x.x.b<y.x.b))) swap(x,y);
        if(x.x.b>=y.x.b) res.x=x.x;
        else res.x=y.x,res.y=min(res.y,(y.x.b-x.x.b)/(x.x.k-y.x.k));
        return res;
    }
    inline void operator+=(dat&x,ll y){x.x.b+=x.x.k*y;x.y-=y;}
    namespace KTT
    {
        struct node{int l,r;dat w;ll tag;}tree[N<<2];
        #define now tree[ro]
        #define lsc ro<<1
        #define rsc ro<<1|1
        #define ls tree[lsc]
        #define rs tree[rsc]
        inline void push_up(int ro){now.w=ls.w+rs.w;}
        inline void push_tag(int ro,ll k){now.tag+=k;now.w+=k;}
        inline void push_down(int ro){if(now.tag)push_tag(lsc,now.tag),push_tag(rsc,now.tag),now.tag=0;}
        inline void build(int ro,int l,int r)
        {
            now.l=l,now.r=r;if(l==r) return now.w=dat(l),void();
            int mid=(l+r)>>1;build(lsc,l,mid);build(rsc,mid+1,r);
            push_up(ro);
        }
        inline void solve(int ro,ll k)
        {
            if(k<=now.w.y) return push_tag(ro,k);
            k+=now.tag;now.tag=0;
            solve(lsc,k);solve(rsc,k);
            push_up(ro);
        }
        inline void update(int ro,int l,int r,ll k)
        {
            if(l<=now.l&&now.r<=r) return solve(ro,k);
            int mid=(now.l+now.r)>>1;push_down(ro);
            if(l<=mid) update(lsc,l,r,k);
            if(r>mid) update(rsc,l,r,k);
            push_up(ro);
        }
        inline void update(int ro,int pos)
        {
            if(now.l==now.r) return now.w=dat(pos),void();
            int mid=(now.l+now.r)>>1;push_down(ro);
            if(pos<=mid) update(lsc,pos);
            else update(rsc,pos);
            push_up(ro);
        }
        inline dat query(int ro,int l,int r)
        {
            if(l==now.l&&now.r==r) return now.w;
            int mid=(now.l+now.r)>>1;push_down(ro);
            if(r<=mid) return query(lsc,l,r);
            else if(l>mid) return query(rsc,l,r);
            else return query(lsc,l,mid)+query(rsc,mid+1,r);
        }
    }
    struct data{int l,r,p;ll w;};
    inline bool operator<(const data&x,const data&y){return x.w<y.w;}
    inline void work()
    {
        ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
        int n,m;cin>>n>>m;
        for(int i=1;i<=n;i++) cin>>a[i].k;
        for(int i=1;i<=n;i++) cin>>a[i].b;
        KTT::build(1,1,n);
        while(m--)
        {
            int op,x;cin>>op;
            if(op==1)  cin>>x,KTT::update(1,1,n,x);
            else if(op==3) cin>>x>>a[x].k>>a[x].b,KTT::update(1,x);
            else
            {
                int l,r,c;cin>>l>>r>>c;
                priority_queue<data>q;ll ans=0;
                auto push=[&q](const int ql,const int qr)
                {
                    if(ql>qr) return;
                    dat t=KTT::query(1,ql,qr);
                    q.push((data){ql,qr,t.x.id,t.x.b});
                };
                push(l,r);
                for(int i=1;i<=c;i++)
                {
                    data tp=q.top();q.pop();
                    push(tp.l,tp.p-1);push(tp.p+1,tp.r);
                    ans=tp.w;
                }
                cout<<ans<<"\n";
            }
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