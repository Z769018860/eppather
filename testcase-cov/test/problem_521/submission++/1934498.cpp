#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<queue>
using namespace std;

#define NDEBUG
#include<cassert>

namespace Elaina{
    #define rep(i, l, r) for(int i=(l), i##_end_=(r); i<=i##_end_; ++i)
    #define drep(i, l, r) for(int i=(l), i##_end_=(r); i>=i##_end_; --i)
    #define fi first
    #define se second
    #define mp(a, b) make_pair(a, b)
    #define Endl putchar('\n')
    #define mmset(a, b) memset(a, b, sizeof a)
    
    typedef long long ll;
    typedef unsigned long long ull;
    typedef pair<int, int> pii;
    typedef pair<ll, ll> pll;
    template<class T>inline T fab(T x){ return x<0? -x: x; }
    template<class T>inline void getmin(T& x, const T rhs){ x=min(x, rhs); }
    template<class T>inline void getmax(T& x, const T rhs){ x=max(x, rhs); }
    template<class T>inline T readin(T x){
        x=0; int f=0; char c;
        while((c=getchar())<'0' || '9'<c) if(c=='-') f=1;
        for(x=(c^48); '0'<=(c=getchar()) && c<='9'; x=(x<<1)+(x<<3)+(c^48));
        return f? -x: x;
    }
    template<class T>inline void writc(T x, char s='\n'){
        static int fwri_sta[1005], fwri_ed=0;
        if(x<0) putchar('-'), x=-x;
        do fwri_sta[++fwri_ed]=x%10, x/=10; while(x);
        while(putchar(fwri_sta[fwri_ed--]^48), fwri_ed);
        putchar(s);
    }
}
using namespace Elaina;

const int maxn=5e5;

vector<int>g[maxn+5];
int n;

inline void add_edge(int u, int v){
    g[u].push_back(v), g[v].push_back(u);
}

inline void input(){
    n=readin(1);
    int u, v;
    for(int i=1; i<n; ++i){
        u=readin(1), v=readin(1);
        add_edge(u, v);
    }
}

int match[maxn+5];
void dfs(int u, int par){
    for(int v: g[u]) if(v!=par)
        dfs(v, u);
    if(!match[u]){
        if(par==0 || match[par]){
            writc(-1); exit(0);
        }
        match[u]=par, match[par]=u;
    }
}

vector<int>lim[maxn+5];
int d[maxn+5];
inline void add_cons(int u, int v){
    lim[u].push_back(v); ++d[v];
}
inline void getconstraint(){
    for(int u=1; u<=n; ++u){
        for(int v: g[match[u]]) if(v!=u)
            add_cons(u, v);
    }
}

int a[maxn+5];
priority_queue< int, vector<int>, greater<int> >Q;

inline void Topu(){
    for(int i=1; i<=n; ++i) if(!d[i])
        Q.push(i);
    int cur=0;
    while(!Q.empty()){
        int u=Q.top(); Q.pop();
        a[++cur]=u;
        for(int v: lim[u]) if(!--d[v])
            Q.push(v);
    }
}

signed main(){
    input();
    dfs(1, 0);
    getconstraint();
    Topu();
    for(int i=1; i<=n; ++i)
        printf("%d ", a[i]);
    Endl;
    return 0;
}
