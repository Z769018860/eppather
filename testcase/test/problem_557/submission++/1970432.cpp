#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e5;

int n,m,tot,ans;
map<int,int> rt;
struct Node{int l,r,k,tag;} t[Maxn*100+5];
#define ls(x) t[x].l
#define rs(x) t[x].r
struct Group{int l,r; mutable int k;};
inline bool operator<(Group a,Group b) {return a.l<b.l;}
set<Group> st;
inline void mk(int p,int siz,int k) {t[p].tag+=k,t[p].k+=siz*k;}
inline void push_up(int p) {t[p].k=t[ls(p)].k+t[rs(p)].k;}
inline void push_down(int p,int l,int r)
{
    if(!t[p].tag) return; int mid=(l+r)>>1;
    if(!ls(p)) ls(p)=++tot; if(!rs(p)) rs(p)=++tot;
    mk(ls(p),mid-l+1,t[p].tag),mk(rs(p),r-mid,t[p].tag),t[p].tag=0;
}
inline void Insert(int &p,int nl,int nr,int l,int r,int k)
{
    if(!p) p=++tot; if(l<=nl && nr<=r) {mk(p,nr-nl+1,k); return;}
    int mid=(nl+nr)>>1; push_down(p,nl,nr);
    if(l<=mid) Insert(ls(p),nl,mid,l,r,k);
    if(r>mid) Insert(rs(p),mid+1,nr,l,r,k);
    push_up(p);
}
inline int Count(int nl,int nr,int l,int r,int p,int k)
{
    
    if(!p) return 0;
    if(l<=nl && nr<=r && t[p].k<k) return -t[p].k;
    if(nl==nr) return nl;
    int mid=(nl+nr)>>1,res=0; push_down(p,nl,nr);
    if(l<=mid) res=Count(nl,mid,l,r,ls(p),k);
    if(res<=0)
    {
        int cur=0;
        if(r>mid) cur=Count(mid+1,nr,l,r,rs(p),k+res);
        if(cur<=0) return res+cur; else return cur;
    }
    else return res;
}
inline void Add(int l,int r,int k)
{st.insert(Group{l,r,k}),Insert(rt[k],1,n,l,r,1);}
inline void Del(set<Group>::iterator it)
{
    int l=it->l,r=it->r,k=it->k;
    Insert(rt[k],1,n,l,r,-1);
}
inline auto Split(int x)
{
    if(x>n) return st.end();
    auto it=st.upper_bound(Group{x,0,0});
    it--; if(x==it->l) return it;
    int l=it->l,r=it->r,k=it->k; st.erase(it);
    st.insert(Group{l,x-1,k}); return st.insert(Group{x,r,k}).first;
}
inline void Modify(int l,int r,int k)
{
    
    auto ir=Split(r+1),il=Split(l);
    for(auto it=il;it!=ir;it++) Del(it);
    st.erase(il,ir),Add(l,r,k);
}
inline int Count(int l,int r,int k,int w)
{
    
    if(rt.find(k)==rt.end()) return 0;
    int res=Count(1,n,l,r,rt[k],w);
    return max(res,0);
}

int main()
{
    

    cin>>n>>m;
    For(i,1,n) {int x; cin>>x; Add(i,i,x);}
    while(m--)
    {
        char op; cin>>op;
        if(op=='M')
        {
            int l,r,k; cin>>l>>r>>k;
            l^=ans,r^=ans,k^=ans,Modify(l,r,k);
        }
        else
        {
            int l,r,k,w; cin>>l>>r>>w>>k;
            l^=ans,r^=ans,k^=ans,w^=ans;
            printf("%d\n",ans=Count(l,r,k,w));
        }
    }
    return 0;
}