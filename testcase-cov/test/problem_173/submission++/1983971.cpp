#define mmdxmqwq(x) <x>
#include mmdxmqwq(bits/stdc++.h)
#define all(x) x.begin(), x.end()
#define pb push_back
#define eb emplace_back
#define MP make_pair
#define MT make_tuple
#define IT iterator
#define fi first
#define se second
#define For(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
#define Rep(i, a, b) for (int i = (int)(a); i >= (int)(b); --i)
#define CLR(a, v) memset(a, v, sizeof(a))
#define CPY(a, b) memcpy(a, b, sizeof(a))
#define debug cerr << "ztxakking\n"
#define y0 ztxaknoi
#define y1 ztxakioi
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using uint = unsigned int;
using pii = pair <int, int>;
using pll = pair <ll, ll>;
using vi = vector <int>;
template <typename T>
using V = vector <T>;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int N = 1e6 + 7, md = 1e9 + 7, bs = 131;
int n;
string s;
int h[N], inv[N], pw[N];
int add(int x, int y) { if (x + y >= md) return x + y - md; else return x + y; }
int sub(int x, int y) { if (x < y) return x - y + md; else return x - y; }
void Add(int &x, int y) { x = add(x, y); }
void Sub(int &x, int y) { x = sub(x, y); }
int qpow(int x, int p) {
  int ans = 1;
  for (; p; p /= 2, x = 1ll * x * x % md) {
    if (p & 1) ans = 1ll * ans * x % md;
  }
  return ans;
}
int qry(int l, int r) {
  return 1ll * sub(h[r], h[l - 1]) * inv[l - 1] % md;
}
int s1[N], s2[N];
int lcp(int x, int y) {
  int l = 0, r = min(n - x + 1, n - y + 1);
  while (l < r) {
    int mid = (l + r + 1) / 2;
    if (qry(x, x + mid - 1) == qry(y, y + mid - 1)) l = mid;
    else r = mid - 1;
  }
  return l;
}
int lcs(int x, int y) {
  int l = 0, r = min(x, y);
  while (l < r) {
    int mid = (l + r + 1) / 2;
    if (qry(x - mid + 1, x) == qry(y - mid + 1, y)) l = mid;
    else r = mid - 1;
  }
  return l;
}
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> s, n = s.size(), s = ' ' + s;
  pw[0] = 1;
  For(i, 1, n) pw[i] = 1ll * pw[i - 1] * bs % md;
  inv[0] = 1, inv[1] = qpow(bs, md - 2);
  For(i, 2, n) inv[i] = 1ll * inv[i - 1] * inv[1] % md;
  For(i, 1, n) h[i] = add(h[i - 1], 1ll * pw[i] * s[i] % md);
  s1[n + 1] = n + 1;
  Rep(i, n, 1) {
    s1[i] = i;
    for (int j = i + 1; j <= n; j = s1[j] + 1) {
      
      int l = lcp(i, j);
      if (l > s1[i] - i + 1 || l > s1[j] - j + 1) {
        if (s1[i] - i + 1 < s1[j] - j + 1) s1[i] = s1[j];
        else break;
      } else {
        if (s[i + l] < s[j + l]) s1[i] = s1[j];
        else break;
      }
    }
  }
  s2[n + 1] = n + 1;
  Rep(i, n, 1) {
    s2[i] = i;
    for (int j = i + 1; j <= n; j = s2[j] + 1) {
      
      int l = lcp(i, j);
      if (l > s2[i] - i + 1 || l > s2[j] - j + 1) {
        if (s2[i] - i + 1 < s2[j] - j + 1) s2[i] = s2[j];
        else break;
      } else {
        if (s[i + l] > s[j + l]) s2[i] = s2[j];
        else break;
      }
    }
  }
  map<pii, int> mp;
  auto push = [&] (int l, int r, int p) {
    if (!mp.count({l, r})) mp[{l, r}] = p;
    else mp[{l, r}] = min(mp[{l, r}], p);
  };
  For(i, 1, n) {
    int p = s1[i] - i + 1;
    int len1 = lcp(i, s1[i] + 1);
    int len2 = lcs(i - 1, s1[i]);
    int l = i - len2, r = s1[i] + len1;
    if (2 * p <= r - l + 1) push(l, r, p);
  }
  For(i, 1, n) {
    int p = s2[i] - i + 1;
    int len1 = lcp(i, s2[i] + 1);
    int len2 = lcs(i - 1, s2[i]);
    int l = i - len2, r = s2[i] + len1;
    if (2 * p <= r - l + 1) push(l, r, p);
  }
  cout << mp.size() << '\n';
  for (auto [t, p] : mp) {
    auto [l, r] = t;
    cout << l << ' ' << r << ' ' << p << '\n';
  }
  return 0;
}