#include<bits/stdc++.h>

using namespace std;
template<typename T>
inline bool cmax(T&x,const T& y){return x<y?x=y,1:0;}
template<typename T>
inline bool cmin(T&x,const T& y){return y<x?x=y,1:0;}
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<vector<int> > vii; 
typedef unsigned long long ull;
#define sz(x) (int(x.size()))
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define eb emplace_back
#define em emplace
#define X first
#define Y second
const int mod=998244353;
inline void MOD(int&x){x-=mod,x+=x>>31&mod;}
inline void MOD(ll& x){x-=mod,x+=x>>63&mod;}
inline int add(int x,int y){MOD(x+=y);return x;}
inline int mul(int x,int y){return 1ll*x*y%mod;}
template<typename ... A>inline int mul(const int& x,const A&... p){return 1ll*x*mul(p...)%mod;}
inline ll ksm(ll a,ll p=mod-2){ll ans=1;for(;p;p>>=1,a=a*a%mod)if(p&1)ans=ans*a%mod;return ans;}
typedef long double LD;
constexpr int MAXN=5e5+10;
struct node
{
    int son[2],fa;
    bool rev,col;
    int siz,sumsiz,w;
    ll pre,suf,tot,subsum;
    inline void R()
    {
        rev^=1;
        swap(son[0],son[1]);
        swap(pre,suf);
    }
}t[MAXN];
#define ls t[p].son[0]
#define rs t[p].son[1]
inline bool isroot(int p){return p!=t[t[p].fa].son[0]&&p!=t[t[p].fa].son[1];}
inline void push_up(int p)
{
    t[p].sumsiz=t[ls].sumsiz+t[rs].sumsiz+t[p].siz+t[p].col;
    t[p].tot=t[ls].tot+t[rs].tot+t[p].w;
    t[p].pre=t[ls].pre+t[rs].pre+(t[p].w+t[ls].tot)*(t[rs].sumsiz+t[p].siz+t[p].col)+t[p].subsum;
    t[p].suf=t[rs].suf+t[ls].suf+(t[p].w+t[rs].tot)*(t[ls].sumsiz+t[p].siz+t[p].col)+t[p].subsum;
}
inline void rotate(int x)
{
    int y=t[x].fa,z=t[y].fa;
    if(!isroot(y))t[z].son[y==t[z].son[1]]=x;t[x].fa=z;
    int r=x==t[y].son[1];z=t[x].son[r^1],t[x].son[r^1]=y,t[y].fa=x,t[y].son[r]=z,t[z].fa=y;
    push_up(y);
}
inline void push_down(int p)
{
    if(t[p].rev){if(ls)t[ls].R();if(rs)t[rs].R();t[p].rev=0;}
}
inline void splay(int p)
{
    static int s[MAXN],top;
    s[top=1]=p;int x=p;
    while(!isroot(p))s[++top]=p=t[p].fa;
    while(top)push_down(s[top--]);
    for(int y,z;!isroot(x);rotate(x))
    {
        y=t[x].fa,z=t[y].fa;
        if(!isroot(y))rotate((x==t[y].son[0])!=(y==t[z].son[0])?x:y);
    }
    push_up(x);
}
inline void access(int p)
{
    for(int i=0;p;p=t[i=p].fa)
    {
        splay(p);
        t[p].siz+=t[rs].sumsiz;
        t[p].subsum+=t[rs].pre;
        t[p].subsum-=t[rs=i].pre;
        t[p].siz-=t[rs].sumsiz;
        push_up(p);
    }
}
inline void makeroot(int x){access(x),splay(x),t[x].R();}
inline void link(int x,int y)
{
    makeroot(x),access(y);t[y].son[1]=x,t[x].fa=y;push_up(y);
    splay(x);
}
inline void cut(int x,int y)
{
    makeroot(x),access(y),splay(x);
    t[x].son[1]=t[y].fa=0;push_up(x);
}
map<pii,int>mp;
int main()
{
   
    
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);cout<<fixed<<setprecision(10);
	int n,m,T;cin>>n>>m>>T;int id=n;
    for(int i=1,u,v,w;i<=m;i++)
    {
        cin>>u>>v>>w;
        if(u>v)swap(u,v);
        id++,t[id].w=w,push_up(id),link(u,id),link(v,id);
        mp[{u,v}]=id;
    }   
    while(T--)
    {
        char op;int u;cin>>op>>u;
        if(op=='L')
        {
            int v,w;cin>>v>>w;
            id++;
            if(u>v)swap(u,v);
            t[id].w=w;push_up(id);
            mp[{u,v}]=id;
            link(u,id),link(v,id);
        }
        else if(op=='C')
        {
            int v;cin>>v;
            if(u>v)swap(u,v);
            int p=mp[{u,v}];
            cut(u,p),cut(v,p);
        }
        else if(op=='F')
        {
            access(u),splay(u),t[u].col^=1,push_up(u);
        }
        else
        {
            makeroot(u);
            cout<<t[u].pre<<'\n';
        }
    }

	return 0;
} 
