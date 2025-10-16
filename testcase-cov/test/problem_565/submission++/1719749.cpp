#include <bits/stdc++.h>
#define For(i, a, b) for (int i = a; i <= b; ++i)
#define Rep(i, a, b) for (int i = a; i >= b; --i)
using namespace std;
const int maxN = 6e5 + 5;
const int mod = 998244353;
int n, m, wn[maxN];
inline int qp(int x, int a) {
  int ans = 1; while (a) {
    if (a & 1) ans = 1ll * ans * x % mod;
    x = 1ll * x * x % mod; a >>= 1;
  }
  return ans;
}
void init() {
  int len = 1; while (len <= max(n, m) << 1) len <<= 1;
  for (int w = 2; w <= len; w <<= 1) {
    int wi = qp(3, (mod - 1) / w), ii = 1;
    for (int k = w >> 1, j = 0; j < k; ++j) {
      wn[k | j] = ii; ii = 1ll * ii * wi % mod;
    }
  }
}
int A[maxN], B[maxN], rev[maxN];
inline int prew(int x) {
  int len = 1; while (len <= x) len <<= 1;
  For (i, 0, len - 1) {
    rev[i] = rev[i >> 1] >> 1; A[i] = B[i] = 0;
    if (i & 1) rev[i] |= len >> 1;
  }
  return len;
}
inline int Md(int x) { return x >= mod ? x - mod : x; }
void NTT(int *a, int len, int on) {
  For (i, 0, len - 1) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int w = 2; w <= len; w <<= 1) 
    for (int k = w >> 1, i = 0; i < len; i += w) {
      For (j, 0, k - 1) {
        int u = a[i + j], v = 1ll * a[i + j + k] * wn[j | k] % mod;
        a[i + j] = Md(u + v); a[i + j + k] = Md(u + mod - v);
      }
    }
  if (on == -1) {
    int inv = qp(len, mod - 2); reverse(a + 1, a + len);
    For (i, 0, len - 1) a[i] = 1ll * a[i] * inv % mod;
  }
}
vector<int> Ad[maxN >> 1], S;
vector<int> solve(vector<int> &a, int l, int r) {
  vector<int> L, R, C;
  if (l == r) {
    C.emplace_back(1 + mod - a[l]); C.emplace_back(a[l]); return C;
  }
  int mid = l + r >> 1;
  L = solve(a, l, mid); R = solve(a, mid + 1, r);
  C.resize(L.size() + R.size());
  int len = prew(C.size()); 
  For (i, 1, L.size()) A[i - 1] = L[i - 1];
  For (i, 1, R.size()) B[i - 1] = R[i - 1];
  NTT(A, len, 1); NTT(B, len, 1);
  For (i, 0, len - 1) A[i] = 1ll * A[i] * B[i] % mod;
  NTT(A, len, -1);
  For (i, 1, C.size()) C[i - 1] = A[i - 1];
  return C;
}
int f[maxN];
int main() {
  scanf("%d%d", &n, &m); n += 20; init();
  For (i, 1, m) {
    int v, x, y; scanf("%d%d%d", &v, &x, &y);
    x = 1ll * x * qp(y, mod - 2) % mod;
    Ad[v].emplace_back(x); S.emplace_back(x);
  }
  vector<int> tmp = solve(S, 0, m - 1);
  int ans = 0;
  For (i, 1, tmp.size()) ans = (ans + 1ll * (i - 1) * tmp[i - 1]) % mod;
  ans = Md(ans << 1);
  f[0] = 1; int top = 0;
  For (i, 0, n) {
    if (Ad[i].size()) {
      tmp = solve(Ad[i], 0, Ad[i].size() - 1);
      int len = prew(tmp.size() + top + 1);
      For (j, 0, top) A[j] = f[j];
      For (j, 0, tmp.size() - 1) B[j] = tmp[j];
      NTT(A, len, 1); NTT(B, len, 1);
      For (j, 0, len - 1) A[j] = 1ll * A[j] * B[j] % mod;       
      NTT(A, len, -1);
      top += tmp.size();
      For (j, 0, top) f[j] = A[j];
      
    }
    For (j, 1, top) {
      f[j >> 1] = Md(f[j >> 1] + f[j]);
      if (j & 1) ans = Md(ans + mod - f[j]);
      f[j] = 0;
    }
    top = top >> 1;
  }
  printf("%d", ans);
  return 0;
}