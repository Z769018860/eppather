#include <bits/stdc++.h>
#define all(x) x.begin(), x.end()
using namespace std;
using ll = long long;
using ull = unsigned long long;
using db = double;
constexpr int inf = 1e9 + 7;
constexpr ll INF = 1e18 + 14;
constexpr int mod = 998244353;
constexpr int maxn = 3e5 + 100;
constexpr int maxm = 1e6 + 100;

ll inv2, inv3;

inline char get(void) {
    static char buf[1 << 19], *p1 = buf, *p2 = buf;
    if (p1 == p2) {
        p2 = (p1 = buf) + fread(buf, 1, 1 << 19, stdin);
        if (p1 == p2) return EOF;
    }
    return *p1++;
}

template<typename T>
inline void read(T &x) {
    x = 0; static char c; bool minus = false;
    for (; !(c >= '0' && c <= '9'); c = get()) if (c == '-') minus = true;
    for (; c >= '0' && c <= '9'; x = x * 10 + c - '0', c = get()); if (minus) x = -x;
}

template<typename T>
void add(T& x, const T& y) {if((x += y) >= mod) x -= mod;}
template<typename T>
void dec(T& x, const T& y) {if((x -= y) < 0) x += mod;}
template<typename T>
void cmax(T& x, const T& y) {if(y > x) x = y;}
template<typename T>
void cmin(T& x, const T& y) {if(y < x) x = y;}

ll qpow(ll x, ll a){
    ll base = x, rt = 1;
    while(a){
        if(a & 1) rt *= base, rt %= mod;
        base *= base, base %= mod;
        a >>= 1;
    }
    return rt;
}

ll inv(ll a){
    if(a < 0) a += mod;
    return qpow(a, mod - 2);
}

int lowbit(int x){
    return x & (-x);
}

ll lcm(ll a, ll b){
    ll g = __gcd(a, b);
    return a / g * b;
}

struct custom_hash {
   static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


vector<ll> fac, ifac;
 
void init_fac(){
    fac.resize(maxn), ifac.resize(maxn);
    fac[0] = fac[1] = 1;
    for(int i = 2; i < maxn; i++) fac[i] = fac[i - 1] * i % mod;
    ifac[maxn - 1] = inv(fac[maxn - 1]);
    for(int i = maxn - 2; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1) % mod;
}
 
ll C(int n, int m){
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

vector<int> prime, np, divi;

void init_prime(){
    np.resize(maxn); divi.resize(maxn);
    for(int i = 2; i < maxn; i++){
        if(!np[i]) {prime.push_back(i); divi[i] = i;}
        for(auto v: prime){
            if(v * i >= maxn) break;
            np[v * i] = 1; divi[v * i] = v;
            if(i % v == 0) break;
        }
    }
}

void init(){

}

bitset<maxm> bs[2];

void solve(){
    int n, now = 1; cin >> n;
    bs[0][0] = 1;
    for (int i = 0; i < n; i++) {
        bs[now].reset();
        int a, b; cin >> a >> b;
        for (int j = a; j <= b; j++) bs[now] |= bs[now ^ 1] << j * j;
        now ^= 1;
    }
    cout << bs[now ^ 1].count() << endl;
}

int main(){
    
    
    
    
    
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    init();
    int t = 1;
    cout << setprecision(15) << fixed;
    cerr << setprecision(2) << fixed;
    
    
    while(t--){
        solve();
    }
    
    
    
    
    return 0;
}