
#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
namespace lly
{
    constexpr int N=1.5e4+5;
    struct dat{int op,v,w,r;}a[N];
    int f[25][N],m,d,ans;
    namespace sgt
    {
        struct node{int l,r;vector<int>id;}tree[N<<2];
        #define now tree[ro]
        #define lsc ro<<1
        #define rsc ro<<1|1
        #define ls tree[lsc]
        #define rs tree[rsc]
        inline void build(int ro,int l,int r)
        {
            now.l=l,now.r=r;if(l==r) return;
            int mid=(l+r)>>1;build(lsc,l,mid);build(rsc,mid+1,r);
        }
        inline void update(int ro,int l,int r,int k)
        {
            if(l<=now.l&&now.r<=r) return now.id.push_back(k),void();
            int mid=(now.l+now.r)>>1;
            if(l<=mid) update(lsc,l,r,k);
            if(r>mid) update(rsc,l,r,k);
        }
        inline void dfs(int ro,int dep)
        {
            memcpy(f[dep],f[dep-1],sizeof(int[m+1]));
            for(int i:now.id)
            {
                int v=a[i].v,w=a[i].w;
                for(int j=m;j>=v;j--) f[dep][j]=max(f[dep][j],f[dep][j-v]+w);
            }
            if(now.l==now.r) 
            {
                int tp=ans*d,id=now.l;
                a[id].v-=tp;a[id].w-=tp;a[id].r-=tp;
                if(a[id].op==1) sgt::update(1,id+1,a[id].r,id);
                else if(f[dep][a[id].v]<0) cout<<"0 0\n",ans=0;
                else cout<<"1 "<<f[dep][a[id].v]<<"\n",ans=f[dep][a[id].v]^1;
            }
            else dfs(lsc,dep+1),dfs(rsc,dep+1);
        }
    }
    inline void work()
    {
        ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);
        int n;cin>>n>>m>>d;memset(f[0],-0x3f,sizeof(int[m+1]));f[0][0]=0;
        for(int i=1;i<=n;i++){cin>>a[i].op>>a[i].v;if(a[i].op==1) cin>>a[i].w>>a[i].r;}
        sgt::build(1,1,n);sgt::dfs(1,1);
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