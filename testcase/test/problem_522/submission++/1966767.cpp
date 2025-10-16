#include<bits/stdc++.h>
#define int long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e5,Mod=998244353;

int n,f[Maxn+5],st[Maxn+5],w[Maxn+5],vis[Maxn+5],top;
struct Node{int x,r,w,id;} h[Maxn+5];
vector<int> v[Maxn+5],q;
inline int F(int x,int y) {x=w[x],y=w[y]; return ((x^y)+x*y)%Mod;}
inline void Add(int x,int y) {v[h[y].id].push_back(h[x].id);}
inline void dfs(int x)
{
    vis[x]=1,q.push_back(x);
    for(auto y:v[x]) if(!vis[y]) dfs(y);
}

signed main()
{
    

    cin>>n;
    For(i,1,n) cin>>h[i].x,h[i].id=i;
    For(i,1,n) cin>>h[i].r;
    For(i,1,n) cin>>h[i].w,w[i]=h[i].w;
    sort(h+1,h+n+1,[&](Node a,Node b){return a.x<b.x;});
    For(i,1,n)
    {
        int res=h[i].x+h[i].r;
        int l=0,r=top; while(l<r)
        {
            int mid=(l+r+1)/2;
            if(h[st[mid]].x+h[st[mid]].r>=h[i].x) l=mid; else r=mid-1;
        } if(l) Add(st[l],i);
        while(top && h[st[top]].x+h[st[top]].r<=res) top--; st[++top]=i;
    } top=0;
    Rof(i,n,1)
    {
        int res=h[i].x-h[i].r;
        int l=0,r=top; while(l<r)
        {
            int mid=(l+r+1)/2;
            if(h[st[mid]].x-h[st[mid]].r<=h[i].x) l=mid; else r=mid-1;
        } if(l) Add(st[l],i);
        while(top && h[st[top]].x-h[st[top]].r>=res) top--; st[++top]=i;
    } sort(h+1,h+n+1,[&](Node a,Node b){return a.r>b.r;});
    
    For(_,1,n)
    {
        int i=h[_].id; dfs(i);
        for(auto x:q) if(x!=i) f[i]=max(f[i],f[x]+F(x,i));
        for(auto x:q) vis[x]=0; q.clear();
    }
    For(i,1,n) printf("%lld\n",f[i]);
    return 0;
}