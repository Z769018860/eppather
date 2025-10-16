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
#define debug cout << "ztxakking\n"
#define y0 ztxaknoi
#define y1 ztxakioi
using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
using uint = unsigned;
using pii = pair <int, int>;
using pll = pair <ll, ll>;
using vi = vector <int>;
template <typename T>
using V = vector <T>;
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
const int N = 1e5 + 7;
int n, sum, a[N], d[N], ans, t[N], M;
void add(int x) { for (; x; x -= x & -x) t[x] ^= 1; }
int qry(int x) { int ans = 0; for (; x <= M; x += x & -x) ans ^= t[x]; return ans; }
int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  cin >> n; if (n == 1) return cout << "L\n", 0; For(i, 1, n) { string s; cin >> s; if (s == "X") ++sum; else { int f = 1; if (s[0] == '-') f = -1, s.erase(s.begin()); for (char c : s) a[i] = a[i] * 10 + c - '0'; a[i] *= f; } }
  if (!sum) {
    For(i, 1, n) d[i] = a[i];
    sort(d + 1, d + n + 1), M = unique(d + 1, d + n + 1) - d - 1;
    For(i, 1, n) a[i] = lower_bound(d + 1, d + M + 1, a[i]) - d;
    For(i, 1, n) ans ^= qry(a[i] + 1), add(a[i]);
    if (ans) cout << "W\n"; else cout << "L\n";
  } else if (sum & 1) cout << "W\n"; else cout << "L\n";
  return 0;
}