#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5;

int n,m,k,all,tot,f[Maxn+5][32];
struct Node{int l,r,k;} t[Maxn*100+5];
#define lowbit(x) (x&-x)
#define ls(x) t[x].l
#define rs(x) t[x].r

map<int,int> mp;
map<pair<int,int>,int> rt;
inline void Insert(int &p,int l,int r,int pos,int k)
{
    if(!p) p=++tot; t[p].k^=k; if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) Insert(ls(p),l,mid,pos,k);
    else Insert(rs(p),mid+1,r,pos,k);
}
inline int Count(int p,int l,int r,int k)
{
    if(!p) return 0; if(r<=k) return t[p].k;
    int mid=(l+r)>>1,res=Count(ls(p),l,mid,k);
    if(k>mid) res^=Count(rs(p),mid+1,r,k); return res;
}
inline int Get(int x) {while(!(x&1)) x>>=1; return x;}
inline int Find(int x)
{
    int w=Get(x%k),y=x/k;
    for(int i=0;(1<<i)<=y;++i) if(y&(1<<i)) w=f[w][i]; return w;
}
inline void Init()
{
    int w=Get(k); all=lowbit(k)-1;
    for(int i=1;i<=w;i+=2) f[i][0]=Get(i+w);
    For(j,1,29) for(int i=1;i<=w;i+=2) f[i][j]=f[f[i][j-1]][j-1];
}

int main()
{
    

    cin>>n>>m>>k; Init();
    while(m--)
    {
        int op,x,y,p=1; cin>>op;
        if(op==1)
        {
            cin>>x>>y; while(x%k==0) x/=k,p*=k;
            
            while(x*p<=n && x&all)
            {
                
                mp[x*p]^=y,x+=(x%k);
                while(x%k==0) x/=k,p*=k;
            } if(x<=n) Insert(rt[make_pair(Find(x),p)],1,n,x*p,y);
        }
        else
        {
            int ans=0; cin>>x;
            while(x%k==0) x/=k,p*=k;
            while(x)
            {
                if(x&all) ans^=mp[x*p];
                else ans^=Count(rt[make_pair(Find(x),p)],1,n,x*p);
                x-=(x%k); if(!x) break; while(x%k==0) x/=k,p*=k;
            } printf("%d\n",ans);
        }
    }
    return 0;
}