#include <bits/stdc++.h>
using namespace std;
const int N=15005;
const int INF=1e9+7;
struct node
{
    int a[N];
    node(){a[0]=0;for(int i=1;i<N;i++) a[i]=-INF;}
    inline void operator=(node &p){memcpy(a,p.a,sizeof(a));}
    inline void add(int wi,int val)
    {
        for(int i=N-1;i>=wi;i--)
            a[i]=max(a[i],a[i-wi]+val);
    }
}nw;
int op[N],wi[N],val[N],ed[N],lstans;
vector<int> arr[N<<2];
#define ls (p<<1)
#define rs (p<<1|1)
void insert(int p,int l,int r,int L,int R,int id)
{
    if(L>R) return;
    if(L<=l&&r<=R) return arr[p].push_back(id);
    int mid=(l+r)>>1;
    if(L<=mid) insert(ls,l,mid,L,R,id);
    if(R>mid) insert(rs,mid+1,r,L,R,id);
}
int T,q;
void solve(int p,int l,int r)
{
    node tmp=nw;int mid=(l+r)>>1;
    for(auto x:arr[p])
        nw.add(wi[x],val[x]);
    if(l==r)
    {
        wi[l]-=lstans*T,val[l]-=lstans*T,ed[l]-=lstans*T;
        if(op[l]==1) insert(1,1,q,l+1,ed[l],l);
        else
        {
            int res1=(nw.a[wi[l]]<0?0:1),res2=(res1?nw.a[wi[l]]:0);
            cout<<res1<<" "<<res2<<"\n";lstans=(res1^res2);
        }
    }
    else solve(ls,l,mid),solve(rs,mid+1,r);
    nw=tmp;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);cin>>q>>T>>T;
    for(int i=1;i<=q;i++)
    {
        cin>>op[i];
        if(op[i]==1) cin>>wi[i]>>val[i]>>ed[i];
        else cin>>wi[i];
    }solve(1,1,q);
    return 0;
}