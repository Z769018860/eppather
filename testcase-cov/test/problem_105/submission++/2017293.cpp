#include <bits/stdc++.h>
#define _rep(i, x, y) for(int i = x; i <= y; ++i)
#define _req(i, x, y) for(int i = x; i >= y; --i)
#define _rev(i, u) for(int i = head[u]; i; i = e[i].nxt)
#define pb push_back
#define fi first
#define se second
#define mst(f, i) memset(f, i, sizeof f)
using namespace std;
#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif
typedef long long ll;
typedef pair<int, int> PII;
namespace fastio{
    char ibuf[50007],*p1 = ibuf, *p2 = ibuf;
    #ifdef ONLINE_JUDGE
    #define get() p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 50007, stdin), p1 == p2) ? EOF : *p1++
    #else
    #define get() getchar()
    #endif
    template<typename T> inline void read(T &t){
        T x = 0, f = 1;
        char c = getchar();
        while(!isdigit(c)){
            if(c == '-') f = -f;
            c = getchar();
        }
        while(isdigit(c)) x = x * 10 + c - '0', c = getchar();
        t = x * f;
    }
    template<typename T, typename ... Args> inline void read(T &t, Args&... args){
        read(t);
        read(args...);
    }
    template<typename T> void write(T t){
        if(t < 0) putchar('-'), t = -t;
        if(t >= 10) write(t / 10);
        putchar(t % 10 + '0');
    }
    template<typename T, typename ... Args> void write(T t, Args... args){
        write(t), putchar(' '), write(args...);
    }
    template<typename T> void writeln(T t){
        write(t);
        puts("");
    }
    template<typename T> void writes(T t){
        write(t), putchar(' ');
    }
    #undef get
};
using namespace fastio;
#define multitest() int T; read(T); _rep(tCase, 1, T)
namespace Calculation{
    const ll mod = 998244353;
    ll ksm(ll p, ll h){ll base = p % mod, res = 1; while(h){if(h & 1ll) res = res * base % mod; base = base * base % mod, h >>= 1ll;} return res;}
    void dec(ll &x, ll y){x = ((x - y) % mod + mod) % mod;}
    void add(ll &x, ll y){x = (x + y) % mod;}
    void mul(ll &x, ll y){x = x * y % mod;}
    ll sub(ll x, ll y){return ((x - y) % mod + mod) % mod;}
    ll pls(ll x, ll y){return ((x + y) % mod + mod) % mod;}
    ll mult(ll x, ll y){return x * y % mod;}
}
using namespace Calculation;
const int N = 2e5 + 5, inf = 0x3f3f3f3f;
int n, m, cnt;
struct node{
    int fa, val, rev, siz, son[2];
}a[N];
#define ls a[x].son[0]
#define rs a[x].son[1]
int New(int fa, int val){
    a[++cnt] = {fa, val, 0, 1, {0, 0}};
    return cnt;
}
void pushr(int x){
    swap(ls, rs), a[x].rev ^= 1;
}
void pushdown(int x){
    if(!a[x].rev) return;
    if(ls) pushr(ls);
    if(rs) pushr(rs);
    a[x].rev = 0;
}
void update(int x){a[x].siz = a[ls].siz + a[rs].siz + 1;}
void rotate(int x){
    int y = a[x].fa, z = a[y].fa, k = a[y].son[1] == x;
    pushdown(x);
    if(z) a[z].son[a[z].son[1] == y] = x; a[x].fa = z;
    a[y].son[k] = a[x].son[k ^ 1]; if(a[x].son[k ^ 1]) a[a[x].son[k ^ 1]].fa = y;
    a[x].son[k ^ 1] = y; if(y) a[y].fa = x;
    update(y), update(x);
}
int rt;
void splay(int x, int goal){
    while(a[x].fa != goal){
        int y = a[x].fa, z = a[y].fa;
        if(z != goal) rotate((a[z].son[1] == y) ^ (a[y].son[1] == x) ? x : y);
        rotate(x);
    }
    if(!goal) rt = x;
}
int getk(int x, int k){
    while(x){
        pushdown(x);
        if(a[ls].siz >= k) x = ls;
        else if(a[ls].siz + 1 >= k) return splay(x, 0), x;
        else k -= a[ls].siz + 1, x = rs;
    }
    return -1;
}
void modifyr(int l, int r){
    int x = getk(rt, l), y = getk(rt, r + 2);
    splay(x, 0), splay(y, x);
    pushr(a[y].son[0]);
}
void build(int &x, int l, int r, int fa){
    if(l > r) return;
    int mid = l + r >> 1;
    x = New(fa, mid);
    build(ls, l, mid - 1, x), build(rs, mid + 1, r, x);
    update(x);
}
void init(){
    rt = New(0, -inf);
    a[rt].son[1] = New(rt, inf);
    build(a[a[rt].son[1]].son[0], 1, n, a[rt].son[1]);
    update(a[rt].son[1]), update(rt);
}
void out(int x){
    pushdown(x);
    if(ls) out(ls);
    if(x > 2) writes(a[x].val);
    if(rs) out(rs);
}
int main(){
    read(n, m);
    init();
    _rep(i, 1, m){
        int l, r; read(l, r);
        modifyr(l, r);
    }
    out(rt);
    puts("");
    return 0;
}
