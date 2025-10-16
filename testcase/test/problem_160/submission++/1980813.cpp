#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define fore(i, l, r) for (int i = int(l); i <= int(r); ++i)
#define all(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define ve vector

using namespace std;
using ll = long long;
using pii = pair<int,int>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using vpi = vector<vector<pii>>;

const int inf = 0x3f3f3f3f;
const int mod = 998244353;
const int N = 2e5+10;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

#define FIO 
struct IO { 
    #ifdef FIO 
        const static int BUFSIZE = 1 << 20; char buf[BUFSIZE], obuf[BUFSIZE], *p1, *p2, *pp; inline char getchar() { return (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUFSIZE, stdin), p1 == p2) ? EOF : *p1++); } inline void putchar(char x) { ((pp - obuf == BUFSIZE && (fwrite(obuf, 1, BUFSIZE, stdout), pp = obuf)), *pp = x, pp++); } inline IO &flush() { fwrite(obuf, 1, pp - obuf, stdout); fflush(stdout); return *this; } IO() { p1 = buf, p2 = buf, pp = obuf; } ~IO() { flush(); } 
    #else 
        int (*getchar)() = &::getchar; int (*putchar)(int) = &::putchar; inline IO &flush() { fflush(stdout); return *this; }; 
    #endif 
        string sep = " "; int k = 2; template <typename T, typename std::enable_if<std::is_integral<T>::value || std::is_same<T, __int128_t>::value>::type * = nullptr> inline int r(T &s) { int f = 1; char ch = getchar(); s = 0; while (!isdigit(ch) && ch != EOF) f = (ch == '-' ? -1 : 1), ch = getchar(); while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar(); s *= f; return ch != EOF; } template <typename T> inline bool r(vector<T> &v) { bool f = true; for(auto &x: v) f &= r(x); return f; } template <typename T> inline bool rv(vector<T> &v, int x = 1) { bool f = true; for (int i = x; i < v.size(); ++i) f &= r(v[i]); return f; } template <typename T, typename enable_if<is_floating_point<T>::value>::type * = nullptr> inline int r(T &s) { int f = 1; char ch = getchar(); s = 0; while (!isdigit(ch) && ch != EOF && ch != '.') f = (ch == '-' ? -1 : 1), ch = getchar(); while (isdigit(ch)) s = s * 10 + (ch ^ 48), ch = getchar(); if (ch == EOF) return false; if (ch == '.') { T eps = 0.1; ch = getchar(); while (isdigit(ch)) s = s + (ch ^ 48) * eps, ch = getchar(), eps /= 10; } s *= f; return ch != EOF; } inline int r(char &c) { char ch = getchar(); c = EOF; while (isspace(ch) && ch != EOF) ch = getchar(); if (ch != EOF) c = ch; return c != EOF; } inline int r(char *c) { char ch = getchar(), *s = c; while (isspace(ch) && ch != EOF) ch = getchar(); while (!isspace(ch) && ch != EOF) *(c++) = ch, ch = getchar(); *c = '\0'; return s != c; } inline int r(string &s) { s.clear(); char ch = getchar(); while (isspace(ch) && ch != EOF) ch = getchar(); while (!isspace(ch) && ch != EOF) s += ch, ch = getchar(); return s.size() > 0; } inline int getline(char *c, const char &ed = '\n') { char ch = getchar(), *s = c; while (ch != ed && ch != EOF) *(c++) = ch, ch = getchar(); *c = '\0'; return s != c; } inline int getline(string &s, const char &ed = '\n') { s.clear(); char ch = getchar(); while (ch != ed && ch != EOF) s += ch, ch = getchar(); return s.size() > 0; } template <typename T = int> inline T r() { T x; r(x); return x; } template <typename T, typename... Ts> int r(T &x, Ts &...val) { return r(x) && r(val...); } template <typename T, typename enable_if<is_integral<T>::value>::type * = nullptr> IO &w(T x) { if (x < 0) putchar('-'), x = -x; static char sta[20]; int top = 0; do sta[top++] = x % 10 + '0', x /= 10; while (x); while (top) putchar(sta[--top]); return *this; } inline IO &w(const string &str) { for (char ch : str) putchar(ch); return *this; } inline IO &w(const char *str) { while (*str != '\0') putchar(*(str++)); return *this; } inline IO &w(char *str) { return w((const char *)str); } inline IO &w(const char &ch) { return putchar(ch), *this; } template <typename T, typename enable_if<is_floating_point<T>::value>::type * = nullptr> inline IO &w(T x) { if (x > 1e18 || x < -1e18) { w("[Floating point overflow]"); throw; } if (x < 0) putchar('-'), x = -x; const static long long pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000, 100000000000000, 1000000000000000, 10000000000000000, 100000000000000000, 100000000000000000, 100000000000000000}; const auto &n = pow10[k]; long long whole = (int)x; double tmp = (x - whole) * n; long long frac = tmp; double diff = tmp - frac; if (diff > 0.5) { ++frac; if (frac >= n) frac = 0, ++whole; } else if (diff == 0.5 && ((frac == 0U) || (frac & 1U))) ++frac; w(whole); if (k == 0U) { diff = x - (double)whole; if ((!(diff < 0.5) || (diff > 0.5)) && (whole & 1)) ++whole; } else { putchar('.'); static char sta[20]; int count = k, top = 0; while (frac) { sta[top++] = frac % 10 + '0'; frac /= 10, count--; } while (count--) putchar('0'); while (top) putchar(sta[--top]); } return *this; } template <typename T> inline IO &w(vector<T> &v) { bool f = true; for(auto x: v) { if (f) f = false; else w(sep); w(x); }; return *this; } template <typename T> inline IO &wv(vector<T> &v,int x = 1) { bool f = true; for (int i = x; i < v.size(); ++i) { if (f) f = false; else w(sep); w(v[i]); }; wl(); return *this; } template <typename T, typename... Ts> inline IO &w(T x, Ts... val) { w(x); w(sep); w(val...); return *this; } template <typename... Ts> inline IO &wl(Ts... val) { w(val...); putchar('\n'); return *this; } inline IO &wl(void) { putchar('\n'); return *this; } template <typename T> inline IO &ww(T x, const string &s = " ") { w(x), w(s); return *this; } inline IO &ss(const string &s) { return sep = s, *this; } inline IO &sp(const int &K) { return k = K, *this; } 
} io;

struct ER { 
    #define debug(x...) cerr << "Line " << __LINE__ << ": " #x " = "; er.wl(x) 
    #define debug_assert(a, x...) if (not(a)) { cerr << "Line " << __LINE__ << ": Assertion `" #a "` failed." << endl; cerr << #x " = "; er.wl(x); exit(0);} 
    string sep = " "; template <typename T, typename enable_if<is_integral<T>::value>::type * = nullptr> ER &w(T x) { cerr << x; return *this; } inline ER &w(const string &str) { cerr << str; return *this; } inline ER &w(const char *str) { cerr << str; return *this; } inline ER &w(char *str) { return w((const char *)str); } inline ER &w(const char &ch) { cerr << ch; return *this; } template <typename T, typename enable_if<is_floating_point<T>::value>::type * = nullptr> inline ER &w(T x) { cerr << x; return *this; } template <typename A, typename B> inline ER &w(pair<A, B> x) { cerr << "("; w(x.fi); cerr << ", "; w(x.se); cerr << ")"; return *this; } template <typename T, size_t N> inline ER &w(array<T, N> &a) { cerr << "["; bool first = true; for (auto &v : a) { cerr << (first ? "" : ", "); w(v); first = 0; } cerr << "]"; return *this; } template <typename T> inline ER &w(vector<T> &x) { cerr << "["; bool first = true; for (auto &v : x) { cerr << (first ? "" : ", "); w(v); first = 0; } cerr << "]"; return *this; } template <typename T, class Cmp> inline ER &w(set<T, Cmp> &x) { cerr << "{"; bool first = true; for (auto &v : x) { cerr << (first ? "" : ", "); w(v); first = 0; } cerr << "}"; return *this; } template <typename T, class Cmp> inline ER &w(multiset<T, Cmp> &x) { cerr << "{"; bool first = true; for (auto &v : x) { cerr << (first ? "" : ", "); w(v); first = 0; } cerr << "}"; return *this; } template <typename A, typename B, class Cmp> inline ER &w(map<A, B, Cmp> &x) { cerr << "{"; bool first = true; for (auto &[a, b] : x) { cerr << (first ? "" : ", "); w(a); cerr << ": "; w(b); first = 0; } cerr << "}"; return *this; } template <typename T, typename... Ts> inline ER &w(T x, Ts... val) { w(x); w(sep); w(val...); return *this; } template <typename... Ts> inline ER &wl(Ts... val) { w(val...); cerr << endl; return *this; } inline ER &wl(void) { cerr << endl; return *this; } template <typename T> inline ER &ww(T x, const string &s = " ") { w(x), w(s); return *this; } inline ER &ss(const string &s) { return sep = s, *this; } inline ER &sp(const int &K) { cerr << fixed << setprecision(K); return *this; } 
} er;

int main() {
    int n,m;
    io.r(n,m);
    vi d(n+1),w(n+1),v(n+1);
    io.rv(d);
    io.rv(w);
    io.rv(v);
    vii e(n+1);
    fore(i,1,n) e[d[i]].pb(i);
    vii dp(n+3,vi(m+1));
    vi l(n+1), r(n+1), id(n+2);
    int tot = 0;
    function<void(int)> dfs = [&](int u) {
        l[u] = ++tot;
        id[tot] = u;
        for(auto v: e[u]) dfs(v);
        r[u] = tot;
    };
    dfs(0);
    for(int i=n+1;i>=1;--i) {
        int u = id[i];
        forn(j,m+1) {
            dp[i][j] = dp[r[u]+1][j];
            if(j>=w[u]) dp[i][j] = max(dp[i][j],dp[i+1][j-w[u]]+v[u]);
        }
    }
    io.wl(dp[1][m]);

    return 0;
}