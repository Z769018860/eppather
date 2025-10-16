#include<bits/stdc++.h>
using namespace std;

#define endl '\n'
#define hh cout<<endl;
#define No cout<<"No"<<endl;
#define Yes cout<<"Yes"<<endl;
#define NO cout<<"NO"<<endl;
#define YES cout<<"YES"<<endl;

namespace Fread{const int SIZE=1<<21;char buf[SIZE],*S,*T;inline char getchar(){if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return'\n';}return*S++;}}namespace Fwrite{const int SIZE=1<<21;char buf[SIZE],*S=buf,*T=buf+SIZE;inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}inline void putchar(char c){*S++=c;if(S==T)flush();}struct NTR{~NTR(){flush();}}ztr;}namespace fastIO1{struct Reader{template<typename T>Reader&operator>>(T&x){char c=getchar();T f=1;while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}x=0;while(c>='0'&&c<='9'){x=x*10+(c-'0');c=getchar();}x*=f;return*this;}Reader&operator>>(char&c){c=getchar();while(c==' '||c=='\n')c=getchar();return*this;}Reader&operator>>(char*str){int len=0;char c=getchar();while(c==' '||c=='\n')c=getchar();while(c!=' '&&c!='\n'&&c!='\r'){str[len++]=c;c=getchar();}str[len]='\0';return*this;}Reader(){}}fin;struct Writer{template<typename T>Writer&operator<<(T x){if(x==0){putchar('0');return*this;}if(x<0){putchar('-');x=-x;}static int sta[45];int top=0;while(x){sta[++top]=x%10;x/=10;}while(top){putchar(sta[top]+'0');--top;}return*this;}Writer&operator<<(char c){putchar(c);return*this;}Writer&operator<<(char*str){int cur=0;while(str[cur])putchar(str[cur++]);return*this;}Writer&operator<<(const char*str){int cur=0;while(str[cur])putchar(str[cur++]);return*this;}Writer(){}}fout;}using fastIO1::Reader;using fastIO1::Writer;using fastIO1::fin;using fastIO1::fout;
#define cin fin
#define cout fout
using namespace fastIO1;

namespace fastIO2{template<typename T>void read(T&x){x=0;char ch;cin>>ch;T fl=1;while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;cin>>ch;};while(ch>='0'&&ch<='9'){x=x*10+ch-'0';cin>>ch;};x=x*fl;}template<typename T,typename...T1>void read(T&x,T1&...x1){read(x);read(x1...);}template<typename T>void print(T x){if(x<0){x=-x;cout<<'-';}if(x/10)print(x/10);cout<<x%10;}template<typename T>void printsp(T x){print(x);cout<<' ';}template<typename T,typename...T1>void printsp(T&x,T1&...x1){printsp(x);printsp(x1...);}template<typename T>void printen(T x){print(x);cout<<endl;}template<typename T,typename...T1>void printen(T&x,T1&...x1){printen(x);printen(x1...);}}
using namespace fastIO2;

typedef long long ll;

mt19937 rnd(time(0));

ll ksm(ll a,ll b)
{
    if(!b)
        return 1;
    ll ans = 1;
    while(b)
    {
        if(b&1)
            ans *= a;
        a *= a;
        b /= 2;
    }
    return ans;
}



#define ls (p<<1)
#define rs (p<<1|1)
#define int long long
int n,m,MOD;
const int N = 100005;
int a[N];
struct point
{
	int l,r;
	int sum,lazy;
}t[N*4];
void push_up(int p)
{
	t[p].sum = t[ls].sum+t[rs].sum;
}
void push_down(int p)
{
	if(t[p].lazy)
	{
		t[ls].sum += t[p].lazy*(t[ls].r-t[ls].l+1);
		t[rs].sum += t[p].lazy*(t[rs].r-t[rs].l+1);
		t[ls].lazy += t[p].lazy;
		t[rs].lazy += t[p].lazy;
		t[p].lazy = 0;
		return;
	}
}
void build(int p,int l,int r)
{
	t[p].l = l;
	t[p].r = r;
	if(l==r)
	{
		t[p].sum = a[l];
		return;
	}
	int mid = (t[p].l+t[p].r)/2;
	build(ls,l,mid);
	build(rs,mid+1,r);
	push_up(p);
}
void add(int p,int l,int r,int d)
{
	if(t[p].l>=l&&t[p].r<=r)
	{
		t[p].sum += (t[p].r-t[p].l+1)*d;
		t[p].lazy += d;
		return;
	}
	push_down(p);
	int mid = (t[p].l+t[p].r)/2;
	if(l<=mid)
		add(ls,l,r,d);
	if(mid<r)
		add(rs,l,r,d);
	push_up(p);
}
int get(int p,int l,int r)
{
	if(l<=t[p].l&&t[p].r<=r)
		return t[p].sum;
	push_down(p);
	int ans = 0;
	int mid = (t[p].l+t[p].r)/2;
	if(l<=mid)
		ans += get(ls,l,r);
	if(mid<r)
		ans += get(rs,l,r);
	return ans;
}
vector<int> g[500001];
int root;
int fa[500001],size[500001],son[500001],top[500001],dep[500001];
int dfn[500001];
int b[500001];
int cnt;
void dfs1(int u)
{
    int ma = INT_MIN;
    size[u] = 1;
    dep[u] = dep[fa[u]]+1;
    int i;
    for(i=0;i<g[u].size();i++)
    {
        int v = g[u][i];
        if(v==fa[u])
            continue;
        fa[v] = u;
        dfs1(v);
        size[u] += size[v];
        if(size[v]>ma)
            ma = size[v],son[u] = v;
    }
    return;
}
void dfs2(int u,int f)
{
    dfn[u] = ++cnt;
    top[u] = f;
    a[cnt] = b[u];
    if(!son[u])
        return;
    dfs2(son[u],f);
    int i;
    for(i=0;i<g[u].size();i++)
    {
        int v = g[u][i];
        if(v==fa[u]||v==son[u])
            continue;
        dfs2(v,v);
    }
    return;
}
int lca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        x = fa[top[x]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    return x;
}
int q;
void update1(int x,int y,int z)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        add(1,dfn[top[x]],dfn[x],z);
        x = fa[top[x]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    add(1,dfn[x],dfn[y],z);
    return;
}
int find_son(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(fa[top[y]]==x)
            return top[y];
        y = fa[top[y]];
    }
    return son[x];
}
void update2(int x,int z)
{
    if(lca(x,root)!=x)
        add(1,dfn[x],dfn[x]+size[x]-1,z);
    else if(x==root)
        add(1,1,n,z);
    else
    {
        int son = find_son(x,root);
        add(1,1,dfn[son]-1,z);
        if(dfn[son]+size[son]<=n)
            add(1,dfn[son]+size[son],n,z);
    }
    return;
}
int ask1(int x,int y)
{
    int ans = 0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        ans += get(1,dfn[top[x]],dfn[x]);
        x = fa[top[x]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    ans += get(1,dfn[x],dfn[y]);
    return ans;
}
int ask2(int x)
{
    if(lca(x,root)!=x)
        return get(1,dfn[x],dfn[x]+size[x]-1);
    else if(x==root)
        return get(1,1,n);
    else
    {
        int son = find_son(x,root);
        int ans = 0;
        ans += get(1,1,dfn[son]-1);
        if(dfn[son]+size[son]<=n)
            ans += get(1,dfn[son]+size[son],n);
        return ans;
    }
}
signed main()
{
	cin>>n;
    int i;
    for(i=1;i<=n;i++)
        cin>>b[i];
    for(i=2;i<=n;i++)
    {
        int x;
        cin>>x;
        g[x].push_back(i);
        g[i].push_back(x);
    }
    dfs1(1);
    dfs2(1,1);
    build(1,1,n);
    cin>>q;
    while(q--)
    {
        int op;
        int x,y,z;
        cin>>op;
        if(op==1)
            cin>>root;
        if(op==2)
        {
            cin>>x>>y>>z;
            update1(x,y,z);
        }
        if(op==3)
        {
            cin>>x>>y;
            update2(x,y);
        }
        if(op==4)
        {
            cin>>x>>y;
            cout<<ask1(x,y)<<endl;
        }
        if(op==5)
        {
            cin>>x;
            cout<<ask2(x)<<endl;
        }
    }
	return 0;
}