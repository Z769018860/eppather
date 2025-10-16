
#include <bits/stdc++.h>
#define int long long
typedef long long ll;
typedef unsigned long long ull;
std::mt19937_64 myRound64(time(nullptr));
std::mt19937 myRound32(time(nullptr));
void slove();
void main_init();
void solve_init();


int32_t main(){
    std::cout << (std::setiosflags(std::ios::fixed)) << std::setprecision(12);
#ifdef ONLINE_JUDGE
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr), std::cout.tie(nullptr);
#else
    freopen("XiuDu.in", "r", stdin);
    freopen("XiuDu.out", "w", stdout);
#endif
    int T = 1;

    main_init();
    while(T --){solve_init(), slove();}
    return 0;
}


void main_init(){}
void solve_init(){}
constexpr int N = 105, M = 1e3 + 5, S = (1 << 10) + 5;

namespace Steiner_Tree
{
    
    
    
    
    
    constexpr int inf = 0x3f3f3f3f;
    int n, m, k;
    int e[M], ne[M], w[M], h[N], idx;
    int dist[N];
    bool st[N];
    int q[N];
    int dp[N][S]; 

    void init()
    {
        memset(h, -1, sizeof h);
        memset(dp, 0x3f, sizeof dp);
    }

    void add(int a, int b, int c)
    {
        e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
        e[idx] = a, w[idx] = c, ne[idx] = h[b], h[b] = idx ++;
    }

    void spfa(int s)
    {
        memset(st, false, sizeof st);
        int tt = 0, hh = 0;
        for(int i = 1; i <= n; ++ i)
        {
            dist[i] = dp[i][s];
            if(dist[i] != inf) q[tt ++] = i, st[i] = true;
        }

        while (tt != hh)
        {
            int now = q[hh ++];
            if(hh == N) hh = 0;
            st[now] = false;
            for(int i = h[now]; ~i; i = ne[i])
            {
                int j = e[i];
                if(dist[j] > dist[now] + w[i])
                {
                    dist[j] = dist[now] + w[i];
                    if(!st[j])
                    {
                        st[j] = true;
                        q[tt ++] = j;
                        if(tt == N) tt = 0;
                    }
                }
            }
        }
        for(int i = 1; i <= n; ++ i) dp[i][s] = dist[i];
    }

    void S_point()
    {
        int x;
        for(int i = 1; i <= k; ++ i)
        {
            std::cin >> x;
            dp[x][1 << (i - 1)] = 0;
        }
    }

    void work()
    {
        for(int i = 1; i <= n; ++ i) dp[i][0] = 0;
        for(int s = 0; s < (1 << k); ++ s)
        {
            for(int i = 1; i <= n; ++ i)
            {
                for(int t = s & (s - 1); t; t = (t - 1) & s)
                {
                    dp[i][s] = std::min(dp[i][s], dp[i][t] + dp[i][t ^ s]);
                }
            }
            spfa(s);
        }
    }

    void print()
    {
        int ans = inf;
        for(int i = 1; i <= n; ++ i) ans = std::min(ans, dp[i][(1 << k) - 1]);
        std::cout << ans << '\n';
    }

}
using Steiner_Tree::n; 
using Steiner_Tree::m; 
using Steiner_Tree::k; 

void slove(){
    std::cin >> n >> m >> k;
    Steiner_Tree::init();
    for(int i = 0; i < m; ++ i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        Steiner_Tree::add(a, b, c);
    }
    Steiner_Tree::S_point();
    Steiner_Tree::work();
    Steiner_Tree::print();
}
