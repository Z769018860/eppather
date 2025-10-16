#include <bits/stdc++.h>

#if defined(LOCAL)
#define DBG_MACRO_NO_WARNING
#include <dbg.hpp>
#else
#define dbg(x...) (0)
#endif

using namespace std;

using ll = long long;


#define rep(i, f, t) for (int i = (f), ed##i = (t); i <= ed##i; ++i)
#define re(i, t) rep (i, 1, t)
#define per(i, t, f) for (int i = (t), ed##i = (f); i >= ed##i; --i)
#define ste(i, f, t, s) for (int i = (f), ed##i = (t); i <= ed##i; i += s)
#define nxt(i, f, g) for (int i = g.h[f]; i; i = g.e[i].n)
#define umod(x) ((x) >= mo && ((x) -= mo))
#define dmod(x) ((x) < 0 && ((x) += mo))
#define y1 y1__
#define fio(x) (freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout))

template <class T, class E>
__attribute__((always_inline)) inline void up(T &x, E &&y) {
  if (x < y) x = y;
}
template <class T, class E>
__attribute__((always_inline)) inline void down(T &x, E &&y) {
  if (y < x) x = y;
}

const int N = 1e6 + 9;
const ll inf = 1e18;

struct G {
  int tot = 1, h[N];
  struct E {
    int t, n;
    ll ca, fl;
  } e[N << 1];

  inline void Add(int f, int t, ll ca, ll fl) { e[++tot] = {t, h[f], ca, fl}, h[f] = tot; }
} g;

int n, cur[N], m, dep[N];
ll du[N];
bool vis[N];

inline void Add(int f, int t, ll ca) {
  
  g.Add(f, t, ca, 0), g.Add(t, f, 0, 0);
}

inline bool Bfs(int S, int T, int n) {
  re (i, n) dep[i] = 0;
  dep[S] = 1;
  queue<int> q;
  q.push(S);
  while (q.size()) {
    int f = q.front();
    q.pop();
    nxt (i, f, g) {
      int t = g.e[i].t;
      if (g.e[i].fl >= g.e[i].ca) continue;
      if (!dep[t]) {
        dep[t] = dep[f] + 1;
        q.push(t);
      }
    }
  }
  return dep[T];
}

inline ll Dfs(int f, ll fl, int T) {
  if (!fl || f == T) return fl;
  vis[f] = 1;
  ll ou = 0, tmp;
  for (int &i = cur[f]; i; i = g.e[i].n) {
    int t = g.e[i].t;
    if (!vis[t] && dep[t] == dep[f] + 1 && (tmp = Dfs(t, min(fl, g.e[i].ca - g.e[i].fl), T)))
      ou += tmp, fl -= tmp, g.e[i].fl += tmp, g.e[i ^ 1].fl -= tmp;
    if (!fl) break;
  }
  if (!ou) dep[f] = 0;
  vis[f] = 0;
  return ou;
}

inline ll Dinic(int S, int T, int n) {
  ll fl = 0;
  while (Bfs(S, T, n)) {
    re (i, n) cur[i] = g.h[i];
    ll tmp;
    while ((tmp = Dfs(S, inf, T))) {
      fl += tmp;
    }
  }
  return fl;
}

struct E {
  int f, t, l, r;
} e[N];

signed main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int S, T, SS, TT;
  cin >> n >> m >> SS >> TT, S = n + 1, T = n + 2;
  re (i, m) {
    cin >> e[i].f >> e[i].t >> e[i].l >> e[i].r;
    Add(e[i].f, e[i].t, e[i].r - e[i].l);
    du[e[i].f] -= e[i].l, du[e[i].t] += e[i].l;
  }
  re (i, n)
    if (du[i] > 0)
      Add(S, i, du[i]);
    else if (du[i] < 0)
      Add(i, T, -du[i]);
  int id = g.tot + 1;
  Add(TT, SS, inf);
  Dinic(S, T, T);
  nxt (i, S, g) {
    if (g.e[i].ca > 0 && g.e[i].ca != g.e[i].fl) cout << "please go home to sleep\n", exit(0);
  }
  g.e[id].fl = g.e[id].ca = g.e[id ^ 1].fl = g.e[id ^ 1].ca = 0;
  Dinic(TT, SS, T);
  ll ans = 0;
  re (i, m) {
    if (e[i].f == SS) ans += e[i].l, ans += g.e[i << 1].fl;
  }
  cout << ans << '\n';
  return 0;
}
