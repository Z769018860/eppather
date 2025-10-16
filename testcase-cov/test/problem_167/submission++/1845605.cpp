

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

constexpr int mod = 998244353, N = 1e6 + 5;
int fac[N];
void main_init(){
    fac[0] = 1;
    for(int i = 1; i < N; ++ i) fac[i] = (fac[i - 1] * i) % mod;
}
void solve_init(){}
int lowbit(int x) {return x & -x;}
class Tree_array{
private:
    int n;
public:
    std::vector<int> tr;
    void init(int nn){
        n = nn;
        tr.resize(nn + 2);
    }
    void change(int u, int x){
        for(int i = u; i <= n; i += lowbit(i)) tr[i] += x;
    }
    int sum(int u){
        int ans = 0;
        for(int i = u; i; i -= lowbit(i)) ans += tr[i];
        return ans;
    }
}tr;

void slove(){
    int n;
    std::cin >> n;
    tr.init(n + 2);
    std::vector<int> v(n + 1);
    for(int i = 1; i <= n; ++ i) std::cin >> v[i], tr.change(v[i], 1);
    int ans = 1;
    for(int i = 1; i <= n; ++ i) {
        ans += tr.sum(v[i] - 1) * fac[n - i] % mod;
        tr.change(v[i], -1);
        ans %= mod;
    }
    std::cout << ans << '\n';
}
