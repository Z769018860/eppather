#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;

int n,m,a[Maxn+5],t[Maxn*4+5];
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline void push_up(int p) {t[p]=__gcd(t[ls(p)],t[rs(p)]);}
inline void Build(int l,int r,int p)
{
    if(l==r) {t[p]=a[l]; return;}
    int mid=(l+r)>>1; Build(l,mid,ls(p)),Build(mid+1,r,rs(p)),push_up(p);
}
inline void Modify(int l,int r,int p,int pos,int k)
{
    if(l==r) {t[p]=k; return;}
    int mid=(l+r)>>1;
    if(pos<=mid) Modify(l,mid,ls(p),pos,k);
    else Modify(mid+1,r,rs(p),pos,k);
    push_up(p);
}
inline int Count(int nl,int nr,int l,int r,int p)
{
    if(l<=nl && nr<=r) return t[p];
    int mid=(nl+nr)>>1,res=0;
    if(l<=mid) res=__gcd(res,Count(nl,mid,l,r,ls(p)));
    if(r>mid) res=__gcd(res,Count(mid+1,nr,l,r,rs(p)));
    return res;
}
inline ll FindP(int nl,int nr,int l,int r,int p,int k)
{
    if(r<nl || l>nr) return 0ll;
    if(k && t[p]%k==0) return 1ll*k*(min(nr,r)-max(nl,l)+1);
    if(nl==nr) return __gcd(k,t[p]);
    int mid=(nl+nr)>>1,res=__gcd(k,t[ls(p)]);
    return FindP(nl,mid,l,r,ls(p),k)+FindP(mid+1,nr,l,r,rs(p),res);
}
inline ll FindS(int nl,int nr,int l,int r,int p,int k)
{
    if(r<nl || l>nr) return 0ll;
    if(k && t[p]%k==0) return 1ll*k*(min(nr,r)-max(nl,l)+1);
    if(nl==nr) return __gcd(k,t[p]);
    int mid=(nl+nr)>>1,res=__gcd(k,t[rs(p)]);
    return FindS(mid+1,nr,l,r,rs(p),k)+FindS(nl,mid,l,r,ls(p),res);
}
inline int Count(int l,int r) {return Count(1,n,l,r,1);}
inline ll GetPre(int x,int y)
{if(x>y) return 0ll; else return FindP(1,n,x,y,1,0);}
inline ll GetSuf(int x,int y)
{if(x>y) return 0ll; else return FindS(1,n,x,y,1,0);}

int main()
{
    

    cin>>n>>m; For(i,1,n) cin>>a[i]; Build(1,n,1);
    while(m--)
    {
        int x,k; cin>>x>>k; a[x]=k,Modify(1,n,1,x,k);
        int l=0,r=n-1; while(l<r)
        {
            int mid=(l+r+1)/2;
            if(Count(1,mid)>=Count(mid+1,n)) l=mid; else r=mid-1;
        }
        ll ans=GetPre(l+1,n-1)+GetSuf(2,l+1)+Count(1,n);
        printf("%lld\n",ans);
    }
    return 0;
}