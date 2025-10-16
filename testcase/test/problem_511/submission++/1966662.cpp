#include<bits/stdc++.h>
#define ll long long
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=1e6;
const ll inf=1e18+5;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,cur,len[Maxn+5]; ll m,g[Maxn+5][2],f[Maxn+5][2];
int fa[Maxn+5],dep[Maxn+5],siz[Maxn+5],son[Maxn+5];
int dfn[Maxn+5],top[Maxn+5],cnt[Maxn+5],id[Maxn+5];
int s,st[Maxn+5],typ[Maxn+5];
vector<int> v[Maxn+5],ans;
#define ls(x) (x<<1)
#define rs(x) (x<<1|1)

inline ll add(ll a,ll b) {return (a+b>=inf)?inf:a+b;}
inline ll mul(ll a,ll b)
{
    if(!a || !b) return 0;
    return (b>=(inf+a-1)/a)?inf:a*b;
}
struct Matrix{ll a,b,c,d;} idt,h[Maxn+5];
inline Matrix operator*(Matrix x,Matrix y)
{
    return Matrix{add(mul(x.a,y.a),mul(x.b,y.c)),add(mul(x.a,y.b),mul(x.b,y.d)),
                  add(mul(x.c,y.a),mul(x.d,y.c)),add(mul(x.c,y.b),mul(x.d,y.d))};
}
struct SegTree
{
    vector<Matrix> t;
    inline void Set(int x) {t.resize(x*4+3);}
    inline void push_up(int p) {t[p]=t[ls(p)]*t[rs(p)];}
    inline void Modify(int l,int r,int p,int pos,int k)
    {
        if(l==r) {t[p]=h[k]; return;}
        int mid=(l+r)>>1;
        if(pos<=mid) Modify(l,mid,ls(p),pos,k);
        else Modify(mid+1,r,rs(p),pos,k);
        push_up(p);
    }
} T[Maxn+5];
struct BIT
{
    vector<ll> t;
    inline void Set(int x) {t.resize(x*4+3);}
    inline void push_up(int p) {t[p]=mul(t[ls(p)],t[rs(p)]);}
    inline void Modify(int l,int r,int p,int pos,ll k)
    {
        if(l==r) {t[p]=k; return;}
        int mid=(l+r)>>1;
        if(pos<=mid) Modify(l,mid,ls(p),pos,k);
        else Modify(mid+1,r,rs(p),pos,k);
        push_up(p);
    }
} BT[Maxn+5][2];

inline void Get(int x)
{
    if(typ[x]==1) h[x].a=h[x].b=0; else h[x].a=h[x].b=g[x][1];
    if(typ[x]==2) h[x].c=h[x].d=0; else h[x].c=g[x][0],h[x].d=0;
    T[top[x]].Modify(1,len[top[x]],1,dfn[x]-dfn[top[x]]+1,x);
}
inline void dfs1(int x,int f)
{
    fa[x]=f,siz[x]=1,dep[x]=dep[f]+1;
    for(auto y:v[x]) if(y!=f)
    {
        dfs1(y,x),siz[x]+=siz[y];
        son[x]=(siz[y]>siz[son[x]]?y:son[x]);
    }
}
inline void dfs2(int x,int t)
{
    dfn[x]=++cur,top[x]=t,g[x][0]=g[x][1]=1;
    if(son[x]) dfs2(son[x],t);
    else
    {
        len[top[x]]=dfn[x]-dfn[top[x]]+1;
        T[top[x]].Set(len[top[x]]);
    }
    for(auto y:v[x]) if(y!=fa[x] && y!=son[x])
    {
        id[y]=++cnt[x],dfs2(y,y);
        g[x][0]=mul(g[x][0],f[y][0]);
        g[x][1]=mul(g[x][1],add(f[y][0],f[y][1]));
    }
    f[x][0]=g[x][1],f[x][1]=g[x][0];
    if(son[x]) f[x][0]=mul(f[x][0],add(f[son[x]][0],f[son[x]][1])),
               f[x][1]=mul(f[x][1],f[son[x]][0]);
}
inline void Init()
{
    cin>>n>>m; static int X[Maxn+5],Y[Maxn+5];
    For(i,1,n-1) X[i]=read()+1; For(i,1,n-1) Y[i]=read()+1;
    For(i,1,n-1) v[X[i]].push_back(Y[i]),v[Y[i]].push_back(X[i]);
    idt=Matrix{1ll,0ll,0ll,1ll};
    s=read(); For(i,1,s) st[i]=read()+1;
}
inline void ModifyG(int x)
{
    if(!cnt[x]) {g[x][0]=g[x][1]=1; return;}
    For(i,0,1) g[x][i]=BT[x][i].t[1];
}
inline void ModifyF(int x)
{
    auto res=T[x].t[1]; f[x][0]=res.a,f[x][1]=res.c;
    
    if(!id[x]) return;
    BT[fa[x]][0].Modify(1,cnt[fa[x]],1,id[x],f[x][0]);
    BT[fa[x]][1].Modify(1,cnt[fa[x]],1,id[x],add(f[x][0],f[x][1]));
}
inline void Modify(int x)
{
    while(x)
    {
        int t=top[x]; Get(x),ModifyF(t);
        if(fa[t]) ModifyG(fa[t]); x=fa[t];
    }
}
inline ll GetAll() {return add(T[1].t[1].a,T[1].t[1].c);}
inline void Solve(int x)
{
	if(x==s+1)
	{
		For(i,1,s)
		{
			For(j,st[i-1]+1,st[i]-1) typ[j]=2,Modify(j);
			typ[st[i]]=1,Modify(st[i]),ans.push_back(st[i]);
		}
		For(i,st[s]+1,n)
		{
			typ[i]=1,Modify(i); ll res=GetAll();
			if(res<m) m-=res,typ[i]=2,Modify(i);
			else m--,ans.push_back(i);
			if(!m) break;
		}
		return;
	}
    For(i,1,x-1)
    {
        For(j,st[i-1]+1,st[i]-1) typ[j]=2,Modify(j);
        typ[st[i]]=1,Modify(st[i]),ans.push_back(st[i]);
    } For(i,st[x-1]+1,st[x]) typ[i]=2,Modify(i);
    For(i,st[x]+1,n) typ[i]=0,Modify(i);
    For(i,st[x]+1,n)
    {
        typ[i]=1,Modify(i); ll res=GetAll();
        if(res<m) m-=res,typ[i]=2,Modify(i);
        else m--,ans.push_back(i);
		if(!m) break;
    }
}

int main()
{
    
    

    Init(),dfs1(1,0),dfs2(1,1),sort(st+1,st+s+1);
    For(i,1,n) if(cnt[i]) {For(j,0,1) BT[i][j].Set(cnt[i]);}
    For(i,2,n) if(id[i])
    {
        BT[fa[i]][0].Modify(1,cnt[fa[i]],1,id[i],f[i][0]);
        BT[fa[i]][1].Modify(1,cnt[fa[i]],1,id[i],add(f[i][0],f[i][1]));
    }
    For(i,1,n) Get(i);
    static ll num[Maxn+5]; 
    For(i,1,s)
    {
        For(j,st[i-1]+1,st[i]) typ[j]=2,Modify(j);
        num[i]=max(GetAll()-1,0ll),typ[st[i]]=1,Modify(st[i]);
    }
	num[s+1]=max(GetAll()-1,0ll);
    Rof(i,s+1,1) {if(num[i]>=m) {Solve(i); break;} m-=num[i];}
    for(auto i:ans) printf("%d ",i-1); printf("\n");
    return 0;
}