#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define mk make_pair
#define pb push_back
#define alls(x) x.begin(), x.end()
#define forn(i, n) for (int i = 0; i < int(n); i++)
#define rep(i, n) for (int i = 1; i <= int(n); i++)
#define sz(x) int(x.size())
#define dbg(x) cerr << #x << " = " << x << endl;
#define cin std::cin
#define cout std::cout
#define pii pair<int, int>
#define pll pair<ll, ll>
const ld eps = 1e-12;
const ll inf = 1e16;
const ll mod = 998244353;
const ll mod1 = 1e9 + 87;
const ll mod2 = 1e9 + 93;
using namespace std;

void IOS(string name = "") {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(false); 
    if (sz(name)) {
        freopen((name + ".in").c_str(), "r", stdin); 
        freopen((name + ".out").c_str(), "w", stdout);
    }
}

const ll p = 1e9 + 7;

ll qpow(ll a, ll b) {
    ll ans = 1ll;
    for (; b; b >>= 1) {
        if (b & 1) {
            ans = (ans * a) % p;
        }
        a = (a * a) % p;
    }
    return ans;
}

const int maxn = 5e6 + 6;
ll s[maxn], sv[maxn], a[maxn], modd[maxn], inv[maxn];

int main() {
    IOS();
    int n;
    cin >> n;
    s[0] = 1ll;
    modd[0] = 1ll;
    rep(i, n) {
        modd[i] = modd[i - 1] * mod % p;
        cin >> a[i];
        s[i] = s[i - 1] * a[i] % p;
    }
    sv[n] = qpow(s[n], p - 2);
    ll ans = 0ll;
    for (int i = n; i >= 1; i--) {
        sv[i - 1] = sv[i] * a[i] % p;
    }
    rep(i, n) {
        inv[i] = sv[i] * s[i - 1] % p;
        ans += inv[i] * modd[n - i] % p;
        ans %= p;
    }
    cout << ans << endl;
    return 0;
}