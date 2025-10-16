#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e5,inf=1e9,eps=3e8;

int n,m,X[Maxn+5],Y[Maxn+5],tp[Maxn+5][3];
int h[Maxn+5],qr[Maxn+5][2],ans[Maxn+5];

struct BIT
{
    int t[Maxn+5];
    #define lowbit(x) (x&-x)
    inline void Add(int x,int y) {while(x<=n) t[x]+=y,x+=lowbit(x);}
    inline int Count(int x) {int res=1; while(x) res+=t[x],x-=lowbit(x); return res;}
} BT;

int rt,tot,tag;
struct Node{int l,r,k;} t[Maxn*60+5];
#define ls(x) t[x].l
#define rs(x) t[x].r
inline void Insert(int &p,int l,int r,int pos,int k)
{
    if(!p) t[p=++tot]=Node{0,0,0}; t[p].k+=k; if(l==r) return;
    int mid=(l+r)>>1;
    if(pos<=mid) Insert(ls(p),l,mid,pos,k);
    else Insert(rs(p),mid+1,r,pos,k);
}
inline int Count(int p,int nl,int nr,int l,int r)
{
    if(!p) return 0; if(l<=nl && nr<=r) return t[p].k;
    int mid=(nl+nr)>>1,res=0;
    if(l<=mid) res+=Count(ls(p),nl,mid,l,r);
    if(r>mid) res+=Count(rs(p),mid+1,nr,l,r);
    return res;
}
inline void Modify(int l,int r,int k)
{
    if(l>r) swap(l,r); l-=tag,r-=tag;
    
    Insert(rt,0,inf,l+eps,k),Insert(rt,0,inf,r+eps,-k);
}
inline int Work() {return Count(rt,0,inf,0,eps-tag);}
inline int Get(int x) {return BT.Count(x);}
inline int Check(int a,int b) {return max(a,b)>=0 && min(a,b)<=0;}
inline void Solve()
{
    rt=tot=tag=0;
    memset(BT.t,0,sizeof(BT.t)); For(i,1,n) BT.Add(i,h[i]);
    For(i,2,n) Modify(Get(i-1),Get(i),1);
    for(int i=1,it=1,cur=Check(Get(0),Get(1));i<=m;++i)
    {
        
        if(qr[i][0]==1)
        {
            if(it==1) continue;
            cur-=Check(Get(it),Get(it-1));
            Modify(Get(it),Get(it-1),1),it--;
        }
        if(qr[i][0]==2)
        {
            if(it==n) continue;
            cur+=Check(Get(it),Get(it+1));
            Modify(Get(it),Get(it+1),-1),it++;
        }
        if(qr[i][0]==3)
        {
            cur-=Check(Get(it),Get(it-1));
            int dlt=qr[i][1]-h[it]; h[it]=qr[i][1];
            BT.Add(it,dlt),cur+=Check(Get(it),Get(it-1)),tag+=dlt;
        }
        if(qr[i][0]==4)
        {
            
            
            
            ans[i]+=cur+Work();
        }
    }
}

int main()
{
    

    cin>>n;
    For(i,1,n) cin>>X[i]>>Y[i];
    cin>>m;
    For(i,1,m)
    {
        char op; cin>>op;
        if(op=='B') tp[i][0]=1;
        if(op=='F') tp[i][0]=2;
        if(op=='C') {tp[i][0]=3; cin>>tp[i][1]>>tp[i][2];}
        if(op=='Q') tp[i][0]=4;
    }
    For(i,1,m) qr[i][0]=tp[i][0],qr[i][1]=tp[i][1];
    For(i,1,n) h[i]=X[i];
    Solve();
    For(i,1,m) qr[i][0]=tp[i][0],qr[i][1]=tp[i][2];
    For(i,1,n) h[i]=Y[i];
    Solve();
    For(i,1,m) if(tp[i][0]==4) printf("%d\n",ans[i]);
    return 0;
}