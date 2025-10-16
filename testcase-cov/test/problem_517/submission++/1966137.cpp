#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;

int n,m,q,tga,a[Maxn+5],sum[Maxn+5][30];

struct Trie
{
    int tot,tag,t[Maxn*30+5][2],siz[Maxn*30+5],sum[Maxn*30+5][30];
    inline void Insert(int x)
    {
        int p=0; Rof(i,29,0)
        {
            int op=(x>>i)&1;
            if(!t[p][op]) t[p][op]=++tot;
            p=t[p][op],++siz[p];
            For(j,0,29) if(x&(1<<j)) sum[p][j]++;
        }
    }
    inline ll GetSum(int x)
    {
        ll res=0; For(i,0,29)
        {
            ll now=0; if(tga&(1<<i)) now=siz[x]-sum[x][i]; else now=sum[x][i];
            res+=(now<<i);
        } return res;
    }
    inline ll Count(int x)
    {
        if(!x) return 0ll;
        int p=0; ll res=0;
        Rof(i,29,0)
        {
            int l=0,r=1; if(tag&(1<<i)) swap(l,r);
            if(x<=siz[t[p][l]]) p=t[p][l];
            else
            {
                res+=GetSum(t[p][l]);
                x-=siz[t[p][l]],p=t[p][r];
            }
        } res+=GetSum(p)/siz[p]*x; return res;
    }
    inline int Size() {return siz[t[0][0]]+siz[t[0][1]];}
} T;

inline void Insert(int x)
{x^=tga,a[++m]=x; For(i,0,29) sum[m][i]=sum[m-1][i]+((x>>i)&1);}
inline ll GetSum(int x)
{
    ll res=0; For(i,0,29)
    {
        ll now=0; if(tga&(1<<i)) now=x-sum[x][i]; else now=sum[x][i];
        res+=(now<<i);
    } return res;
}
inline ll Solve(int x)
{
    if(x<=T.Size()) return T.Count(x);
    return T.Count(T.Size())+GetSum(x-T.Size());
}
inline void Trans() {T.tag=tga; For(i,1,m) T.Insert(a[i]); m=0;}

int main()
{
    

    cin>>n; For(i,1,n) {int x; cin>>x; Insert(x);}
    cin>>q; while(q--)
    {
        int op,x,y; cin>>op;
        if(op==1) cin>>x,Insert(x);
        if(op==2) cin>>x>>y,printf("%lld\n",Solve(y)-Solve(x-1));
        if(op==3) cin>>x,tga^=x;
        if(op==4) Trans();
    }
    return 0;
}