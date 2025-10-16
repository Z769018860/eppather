#include <cstdio>
#include <vector>
#define N 15010
#define inf 0x3f3f3f3f
using std::vector;
int n,v,ONLINE;
struct query
{
    int op,v,w,e;
}q[N];
struct val{int sz,val;};
struct seg
{
    int l,r;
    vector<val> v;
}T[N*4];
void init(int l,int r,int o)
{
    T[o].l=l,T[o].r=r;
    if(l!=r)
    {
        int mid=(l+r)/2;
        init(l,mid,o<<1);
        init(mid+1,r,o<<1|1);
    }
}
void ins(int l,int r,val v,int o)
{
    if(T[o].l==l&&T[o].r==r) return T[o].v.push_back(v);
    int mid=(T[o].l+T[o].r)/2;
    if(r<=mid) ins(l,r,v,o<<1);
    else if(l>mid) ins(l,r,v,o<<1|1);
    else ins(l,mid,v,o<<1),ins(mid+1,r,v,o<<1|1);
}
int ans1[N],ans2[N];
int max(int x,int y) {return x>y?x:y;}
void dfs(vector<int> f,int o)
{
    for(auto i:T[o].v) for(int j=v;j>=i.sz;j--)
        f[j]=max(f[j],f[j-i.sz]+i.val);
    if(T[o].l==T[o].r)
    {
        int x=T[o].l;
        if(q[x].op==2)
        {
            ans1[x]=(f[q[x].v]>=0);
            if(ans1[x]) ans2[x]=f[q[x].v];
            int last=(ans1[x]^ans2[x])*ONLINE;
            for(int i=x+1;i<=n;i++)
            {
                if(q[i].op==1) ins(i,q[i].e-last,{q[i].v-last,q[i].w-last},1);
                else {q[i].v-=last; break;}
            }
        }
    }
    else dfs(f,o<<1),dfs(f,o<<1|1);
}
int main()
{
    scanf("%d%d%d",&n,&v,&ONLINE);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&q[i].op,&q[i].v);
        if(q[i].op==1) scanf("%d%d",&q[i].w,&q[i].e);
    }
    init(1,n,1);
    for(int i=1;i<=n&&q[i].op==1;i++)
        ins(i,q[i].e,{q[i].v,q[i].w},1);
    vector<int> f(v+1);
    for(int i=1;i<=v;i++) f[i]=-inf;
    dfs(f,1);
    for(int i=1;i<=n;i++) if(q[i].op==2)
        printf("%d %d\n",ans1[i],ans2[i]);
}