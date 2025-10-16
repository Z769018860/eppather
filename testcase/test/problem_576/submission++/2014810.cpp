#include <bits/stdc++.h>

#define int int64_t

const int kMaxN = 1e5 + 5;

int n, q;
int a[kMaxN];

struct SGT {
  int g[kMaxN * 4];

  void pushup(int x) {
    g[x] = std::__gcd(g[x << 1], g[x << 1 | 1]);
  }

  void build(int x, int l, int r) {
    if (l == r) return void(g[x] = a[l]);
    int mid = (l + r) >> 1;
    build(x << 1, l, mid), build(x << 1 | 1, mid + 1, r);
    pushup(x);
  }

  void update(int x, int l, int r, int ql, int v) {
    if (l == r) return void(g[x] = v);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(x << 1, l, mid, ql, v);
    else update(x << 1 | 1, mid + 1, r, ql, v);
    pushup(x);
  }

  int query(int x, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    else if (l >= ql && r <= qr) return g[x];
    int mid = (l + r) >> 1;
    return std::__gcd(query(x << 1, l, mid, ql, qr), query(x << 1 | 1, mid + 1, r, ql, qr));
  }

  int getpos1(int x, int l, int r, int k) {
    if (g[x] % k == 0) return n + 1;
    else if (l == r) return l;
    int mid = (l + r) >> 1;
    if (g[x << 1] % k) return getpos1(x << 1, l, mid, k);
    else return getpos1(x << 1 | 1, mid + 1, r, k);
  }

  int getpos2(int x, int l, int r, int k) {
    if (g[x] % k == 0) return 0;
    else if (l == r) return l;
    int mid = (l + r) >> 1;
    if (g[x << 1 | 1] % k) return getpos2(x << 1 | 1, mid + 1, r, k);
    else return getpos2(x << 1, l, mid, k);
  }
} sgt;

int getval(auto vec, int p) {
  auto it = std::lower_bound(vec.begin(), vec.end(), std::tuple<int, int, int>{p + 1, 0, 0}) - 1;
  return std::get<2>(*it);
}

int getans() {
  int pos = 1, gcd = a[1];
  std::vector<std::tuple<int, int, int>> vec1, vec2;
  for (; pos <= n;) {
    int nxt = sgt.getpos1(1, 1, n, gcd);
    vec1.emplace_back(pos, nxt - 1, gcd);
    pos = nxt;
    if (pos <= n) gcd = sgt.query(1, 1, n, 1, pos);
  }
  pos = n, gcd = a[n];
  for (; pos;) {
    int nxt = sgt.getpos2(1, 1, n, gcd);
    vec2.emplace_back(nxt + 1, pos, gcd);
    pos = nxt;
    if (pos) gcd = sgt.query(1, 1, n, pos, n);
  }
  std::reverse(vec2.begin(), vec2.end());
  int L = 0, R = n, res = n;
  while (L + 1 < R) {
    int mid = (L + R) >> 1;
    if (getval(vec1, mid) <= getval(vec2, mid + 1)) R = res = mid;
    else L = mid;
  }
  
  int ret = 0;
  for (auto [l, r, v] : vec1) {
    l = std::max(l, res), r = std::min(r, n - 1);
    
    if (l <= r) ret += 1ll * (r - l + 1) * v;
  }
  for (auto [l, r, v] : vec2) {
    l = std::max(l, (int)2), r = std::min(r, res);
    
    if (l <= r) ret += 1ll * (r - l + 1) * v;
  }
  return ret + sgt.query(1, 1, n, 1, n);
}

void dickdreamer() {
  std::cin >> n >> q;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  sgt.build(1, 1, n);
  for (int i = 1; i <= q; ++i) {
    int x, v;
    std::cin >> x >> v;
    a[x] = v, sgt.update(1, 1, n, x, v);
    std::cout << getans() << '\n';
  }
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  std::ios::sync_with_stdio(0), std::cin.tie(0), std::cout.tie(0);
  int T = 1;
  
  while (T--) dickdreamer();
  
  return 0;
}