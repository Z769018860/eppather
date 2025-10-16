#include<iostream>
#include<cstring>
#include<algorithm>
#include<map>
#include<vector>
#include<queue>
#include<cmath>
#include<unordered_map>
using namespace std;

char buf[1<<20], *p1=buf, *p2=buf;
#define getchar() (p1==p2&&(p2=buf+fread(p1=buf, 1, 1<<20, stdin), p1==p2)?EOF:*p1++)
template <typename T>
void read(T &x)
{
    x=0;int f=1;char c=getchar();
    while (!isdigit(c)) f=(c=='-')?-1:1, c=getchar();
    while (isdigit(c)) x=(x<<1)+(x<<3)+c-'0', c=getchar();
    x*=f;
}

typedef long long LL;
const int N=3e5+10, inf=2e9;
int n, m, trlen, root, sum[N];
int fa[N], Size[N], val[N], ch[N][2];
int get(int x) {return ch[fa[x]][1]==x;}
void pushup(int x) {Size[x]=Size[ch[x][0]]+Size[ch[x][1]]+sum[x];}

void add(int v, int f)
{
    int x=++trlen;
    ch[f][val[f]<v]=x, sum[x]=1;
    fa[x]=f, Size[x]=1, val[x]=v;
    if (f==0) root=x;
}

void rotate(int x)
{
    int y=fa[x], z=fa[y], w=get(x);
    fa[ch[z][get(y)]=x]=z;
    fa[ch[y][w]=ch[x][!w]]=y;
    fa[ch[x][!w]=y]=x;
    pushup(y), pushup(x);
}

void splay(int x, int rt)
{
    while (fa[x]!=rt)
    {
        int y=fa[x], z=fa[y];
        if (z!=rt) get(x)==get(y)?rotate(y):rotate(x);
        rotate(x);
    }
    if (rt==0) root=x;
}

int find(int v)
{
    int x=root;
    while (x&&val[x]!=v&&ch[x][val[x]<v]) 
        x=ch[x][val[x]<v];
    return x;
}

void insert(int v)
{
    if (!root) add(v, 0);
    else
    {
        int x=find(v);
        if (val[x]==v) sum[x]++, splay(x, 0);
        else add(v, x), splay(trlen, 0);
    }
}

int query(int v, int w)
{
    int x=find(v);
    if (v<val[x]&&w) return x;
    if (val[x]<v&&!w) return x;
    splay(x, 0), x=ch[x][w];
    while (ch[x][!w]) x=ch[x][!w];
    return x;
}

void del(int v)
{
    int pre=query(v, 0), nxt=query(v, 1);
    splay(pre, 0), splay(nxt, pre);
    int x=ch[nxt][0];
    if (sum[x]>1) sum[x]--, splay(x, 0);
    else ch[nxt][0]=0, splay(nxt, 0);
}

int Rank(int v)
{
    insert(v);
    int x=find(v);splay(x, 0);
    return Size[ch[x][0]]-1;
}

int kth(int k)
{
    int x=root;
    while (1)
    {
        if (k<=Size[ch[x][0]]) x=ch[x][0];
        else if (k>Size[ch[x][0]]+sum[x]) k-=Size[ch[x][0]]+sum[x], x=ch[x][1];
        else {splay(x, 0);return val[x];}
    }
}

int main()
{
    read(n);
    root=trlen=0;
    insert(inf), insert(-inf);
    for (int i=1;i<=n;i++)
    {
        int op, x;
        read(op), read(x);
        if (op==0) insert(x);
        else if (op==1) del(x);
        else if (op==2) printf("%d\n", kth(x+1));
        else if (op==3) printf("%d\n", Rank(x)), del(x);
        else if (op==4) insert(x), printf("%d\n", val[query(x, 0)]==-inf?-1:val[query(x, 0)]), del(x);
        else if (op==5) insert(x), printf("%d\n", val[query(x, 1)]==inf?-1:val[query(x, 1)]), del(x);
    }
    return 0;
}