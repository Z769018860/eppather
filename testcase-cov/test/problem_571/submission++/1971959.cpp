#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5,Maxk=1e7;

struct SAT
{
    int n,dfn[Maxk+5],low[Maxk+5],st[Maxk+5];
    int vis[Maxk+5],col[Maxk+5],top,cur,tmp;
    vector<int> v[Maxk+5];
    inline void Tarjan(int x)
    {
        dfn[x]=low[x]=++cur,st[++top]=x,vis[x]=1;
        for(auto y:v[x])
        {
            if(!dfn[y]) Tarjan(y),low[x]=min(low[x],low[y]);
            else if(vis[y]) low[x]=min(low[x],dfn[y]);
        } if(dfn[x]==low[x])
        {
            ++tmp; while(1)
            {
                int y=st[top--]; vis[y]=0,col[y]=tmp;
                if(x==y) break;
            }
        }
    }
} G;
inline void Add(int x,int y) {G.v[x].push_back(y);}

int n,m,q,nn,L0,R0,B,qr[Maxn+5][2][2];
int X[Maxn+5],Y[Maxn+5],Z[Maxn+5];
int rt,mx,sum,vis[Maxn+5],siz[Maxn+5],dep[Maxn+5];
vector<int> w[Maxn+5],vec,f,g;
vector<pair<int,int>> v[Maxn+5];

inline void Add(int x,int y,int z)
{
    X[++m]=x,Y[m]=y,Z[m]=z;
    v[x].emplace_back(m,z),v[y].emplace_back(m,z);
}
inline int Build(int l,int r)
{
    if(l==r) return vec[l];
    int mid=(l+r)>>1,id=++nn;
    Add(id,Build(l,mid),l==mid),Add(id,Build(mid+1,r),mid+1==r);
    return id;
}
inline void dfs0(int x,int f)
{
    vector<int>().swap(vec);
    for(auto y:w[x]) if(y!=f) vec.push_back(y);
    if(!vec.empty())
    {
        int k=Build(0,vec.size()-1);
        Add(x,k,vec.size()==1);
    }
    for(auto y:w[x]) if(y!=f) dfs0(y,x);
}
inline void Init()
{
    cin>>n>>q>>L0>>R0; B=R0-L0+1;
    For(i,1,n-1)
    {
        int a,b; cin>>a>>b;
        w[a].push_back(b),w[b].push_back(a);
    }
    nn=n,dfs0(1,0),G.n=n*2,m=n,n=nn;
    For(i,1,q)
    {
        int x,k; cin>>x>>k;
        if(k==0) qr[x][0][0]=1; if(k==1) qr[x][0][1]=1;
        if(k==2) qr[x][1][0]=1; if(k==3) qr[x][1][1]=1;
    }
}
inline void GetRt(int x,int f)
{
    siz[x]=1; for(auto [id,z]:v[x]) if(!vis[id])
    {
        int y=X[id]^Y[id]^x; if(y==f) continue;
        GetRt(y,x),siz[x]+=siz[y]; int res=max(siz[y],sum-siz[y]);
        if(res<mx) mx=res,rt=id;
    }
}
inline void dfs1(int x,int fa,int d)
{
    dep[x]=d,f.push_back(x);
    for(auto [id,z]:v[x]) if(!vis[id])
    {
        int y=X[id]^Y[id]^x; if(y==fa) continue;
        dfs1(y,x,d+z);
    }
}
int p1[Maxn+5][2],s1[Maxn+5][2];
int p2[Maxn+5][2],s2[Maxn+5][2];
int tot,L[Maxn+5],R[Maxn+5],idx[Maxn+5];
inline void dfs(int id)
{
    if(!id) return; f.clear(),g.clear();
    vis[id]=1,dfs1(X[id],0,Z[id]),swap(f,g),dfs1(Y[id],0,0);
    
    
    
    For(_,0,1)
    {
        swap(f,g); int mx=0; for(auto i:g) mx=max(mx,dep[i]);
        if(!mx) {tot=1,L[1]=R[1]=0;}
        else
        {
            tot=mx/B; For(i,1,tot) L[i]=R[i-1]+1,R[i]=i*B;
            if(R[tot]<mx) ++tot,L[tot]=R[tot-1]+1,R[tot]=mx; L[1]=0;
        }
        For(i,1,tot) For(j,L[i],R[i]) idx[j]=i;
        For(i,1,tot)
        {
            For(j,L[i],R[i]) For(k,0,1) p1[j][k]=++G.n,p2[j][k]=++G.n,assert(G.n<=Maxk);
            For(j,L[i],R[i]) For(k,0,1) s1[j][k]=++G.n,s2[j][k]=++G.n,assert(G.n<=Maxk);
            For(j,L[i],R[i]-1) For(k,0,1)
                Add(p1[j+1][k],p1[j][k]),Add(p2[j][k],p2[j+1][k]);
            For(j,L[i],R[i]-1) For(k,0,1)
                Add(s1[j][k],s1[j+1][k]),Add(s2[j+1][k],s2[j][k]);
        }
        for(auto i:g) if(i<=m)
        {
            int k=dep[i];
            For(j,0,1) Add(p1[k][j],i+j*m),Add(i+j*m,p2[k][j]);
            For(j,0,1) Add(s1[k][j],i+j*m),Add(i+j*m,s2[k][j]);
        }
        for(auto i:f) if(i<=m)
        {
            int d=dep[i],l=max(0,L0-d),r=min(mx,R0-d);
            if(l>r) continue;
            if(idx[l]==idx[r])
            {
                if(l==L[idx[l]])
                {
                    For(a,0,1) For(b,0,1) if(qr[i][a][b])
                        Add(i+a*m,p1[r][b]),Add(p2[r][b^1],i+(!a)*m);
                }
                else
                {
                    assert(r==R[idx[r]]);
                    For(a,0,1) For(b,0,1) if(qr[i][a][b])
                        Add(i+a*m,s1[l][b]),Add(s2[l][b^1],i+(!a)*m);
                }
            }
            else
            {
                For(a,0,1) For(b,0,1) if(qr[i][a][b])
                {
                    Add(i+a*m,s1[l][b]),Add(s2[l][b^1],i+(!a)*m);
                    Add(i+a*m,p1[r][b]),Add(p2[r][b^1],i+(!a)*m);
                }
            }
        }
    }
    rt=0,mx=n+5,sum=siz[X[id]],GetRt(X[id],0),dfs(rt);
    rt=0,mx=n+5,sum=siz[Y[id]],GetRt(Y[id],0),dfs(rt);
}

int main()
{
    

    Init();
    rt=0,mx=n+5,sum=n,GetRt(1,0),dfs(rt);
    For(i,1,G.n) if(!G.dfn[i]) G.Tarjan(i);
    For(i,1,m) if(G.col[i]==G.col[i+m]) {puts("NO"); return 0;}
    puts("YES");
    return 0;
}