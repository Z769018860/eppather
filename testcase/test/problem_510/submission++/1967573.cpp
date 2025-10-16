
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
namespace lly
{
    constexpr int N=2e5+5;
    namespace sgt
    {
        struct node{int lc,rc,w;}tree[N<<5];
        #define now tree[ro]
        #define lsc now.lc
        #define rsc now.rc
        int tot=0;
        inline void update(int&ro,int l,int r,int pos,int k)
        {
            int mid=(l+r)>>1;if(!ro) ro=++tot;
            now.w^=k;if(l==r) return;
            if(pos<=mid) update(lsc,l,mid,pos,k);
            else update(rsc,mid+1,r,pos,k);
        }
        inline int query(int ro,int l,int r,int pos)
        {
            if(!ro||l==r) return now.w;
            int mid=(l+r)>>1;
            if(pos<=mid) return query(lsc,l,mid,pos);
            else return query(rsc,mid+1,r,pos)^tree[lsc].w;
        }
    }
    int k;int fa[N][32];
    inline int lbt(int x){return x>>__lg(x&(-x));}
    inline int locate(int d)
    {
        int x=lbt(d%k);d/=k;
        for(int i=0;i<=30;i++) if(d&(1<<i)) x=fa[x][i];
        return x;
    }
    inline void init()
    {
        int t=lbt(k);
        for(int i=1;i<t;i+=2) fa[i][0]=lbt(i+t);
        for(int j=1;j<=30;j++)
            for(int i=1;i<t;i+=2)
                fa[i][j]=fa[fa[i][j-1]][j-1];
    }
    map<int,int>b2,root[35];
    inline void work()
    {
        ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
        int n,m;cin>>n>>m>>k;init();int bt=(k&(-k))-1;
        while(m--)
        {
            int op,x,rt=1,tt=0;cin>>op>>x;
            while(x%k==0) x/=k,rt*=k,++tt;
            if(op==1)
            {
                int vl;cin>>vl;
                while(x*rt<=n&&(x&bt)) 
                {
                    b2[x*rt]^=vl;x+=x%k;
                    while(x%k==0) x/=k,rt*=k,++tt;
                }
                if(x*rt<=n) sgt::update(root[tt][locate(x)],1,n,x*rt,vl);
            }
            else
            {
                int ans=0;
                while(x)
                {
                    if(x&bt) ans^=b2[x*rt];
                    else ans^=sgt::query(root[tt][locate(x)],1,n,x*rt);
                    x-=x%k;if(!x) break;
                    while(x%k==0) x/=k,rt*=k,++tt;
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