#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5+2,inf=1e9;

int n,m,q,cnt[Maxn+5],a[Maxn+5];
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

struct Node{int l,r,id,mn; ll ra,lb;} t[Maxn*4+5]; ll tag[Maxn*4+5];
inline void mk(int p,int k) {t[p].mn+=k,tag[p]+=k;}
inline void push_down(int p)
{if(tag[p]) mk(ls(p),tag[p]),mk(rs(p),tag[p]),tag[p]=0;}
inline ll GetA(int l,int r,int p,int k)
{
    if(l==r) return 1ll*l*max(0,k-t[p].mn);
    int mid=(l+r)>>1; push_down(p);
    if(k>=t[ls(p)].mn) return GetA(l,mid,ls(p),k)+t[p].ra;
    else return GetA(mid+1,r,rs(p),k);
}
inline ll GetB(int l,int r,int p,int k)
{
    if(l==r) return (l+1)*(t[p].mn<k);
    int mid=(l+r)>>1; push_down(p);
    if(k>=t[rs(p)].mn) return GetB(mid+1,r,rs(p),k)+t[p].lb;
    else return GetB(l,mid,ls(p),k);
}
inline Node operator+(Node a,Node b)
{
    Node c; c.l=a.l,c.r=b.r,c.id=a.id/2,c.mn=min(a.mn,b.mn);
    c.ra=GetA(b.l,b.r,b.id,a.mn),c.lb=GetB(a.l,a.r,a.id,b.mn);
    return c;
}
inline void push_up(int p) {t[p]=t[ls(p)]+t[rs(p)];}
inline void Build(int l,int r,int p)
{
    if(l==r)
    {
        t[p].l=l,t[p].r=r,t[p].id=p;
        t[p].mn=l,t[p].ra=t[p].lb=0; return;
    }
    int mid=(l+r)>>1; Build(l,mid,ls(p)),Build(mid+1,r,rs(p)),push_up(p);
}
inline void Modify(int nl,int nr,int l,int r,int p,int k)
{
    if(l<=nl && nr<=r) {mk(p,k); return;}
    int mid=(nl+nr)>>1; push_down(p);
    if(l<=mid) Modify(nl,mid,l,r,ls(p),k);
    if(r>mid) Modify(mid+1,nr,l,r,rs(p),k);
    push_up(p);
}
vector<Node> v;
inline void Count(int nl,int nr,int l,int r,int p)
{
    if(l<=nl && nr<=r) {v.push_back(t[p]); return;}
    int mid=(nl+nr)>>1; push_down(p);
    if(l<=mid) Count(nl,mid,l,r,ls(p));
    if(r>mid) Count(mid+1,nr,l,r,rs(p));
}
inline void Work(int l,int r)
{vector<Node>().swap(v),Count(0,n,l,r,1);}
inline ll A(int l,int r)
{
    ll ans=0; if(l==r) ans+=1ll*cnt[l]*l;
    int id=max(l,r-1); Work(l,id);
    int mn=inf; for(auto i:v) mn=min(mn,i.mn); Work(id+1,n);
    for(auto i:v) ans+=GetA(i.l,i.r,i.id,mn),mn=min(mn,i.mn);
    return ans;
}
inline ll Count(int l,int r)
{
    ll ans=0; if(l>r) ans=l;
    int mn=inf,id=min(l,r); Work(id,r);
    for(auto i:v) mn=min(mn,i.mn); Work(0,id-1);
    reverse(v.begin(),v.end());
    for(auto i:v) ans+=GetB(i.l,i.r,i.id,mn),mn=min(mn,i.mn);
    return ans;
}

int main()
{
    

    cin>>m>>q; n=m*2; Build(0,n,1);
    For(i,1,m) cin>>a[i],cnt[a[i]]++,Modify(0,n,a[i],n,1,-1);
    while(q--)
    {
        int op,l,r; cin>>op>>l>>r;
        if(op==1)
        {
            Modify(0,n,a[l],n,1,1),Modify(0,n,r,n,1,-1);
            cnt[a[l]]--,a[l]=r,cnt[r]++;
        }
        else
        {
            ll s1=A(l,r),s2=Count(l,r-1)-Count(l,n);
            printf("%lld\n",s1+s2);
        }
    }
    return 0;
}