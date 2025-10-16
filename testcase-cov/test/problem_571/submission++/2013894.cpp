#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int kmax = 5e4 + 3;

struct Tree {
  int d, dd, u, uu;
  int ls, rs;
} tr[kmax * 50];

int n, m, depl, depr;
int tc, rt[kmax], dc;
int d[kmax], f[kmax], mxd[kmax], son[kmax];
int opt[kmax];
int dfn[kmax << 3], low[kmax << 3], idx;
int stk[kmax << 3], tp;
bool instk[kmax << 3];
vector<int> e[kmax], ee[kmax << 3];

namespace Two_SAT {
const int M = 50005 * 16 * 16 + 233;
const int N = M * 8;
struct edge {
    int to;
    edge *next;
} *G[M], Pool[N], *allc = Pool;
bool mark[M];
int stk[M];
int top;
void add_edge(int u, int v, int f, int g) {
    if (u == 0 or v == 0)
        return;

    *allc = (edge) {
        v << 1 | g, G[u << 1 | f]
    };
    G[u << 1 | f] = allc++;
    *allc = (edge) {
        u << 1 | (!f), G[v << 1 | (!g)]
    };
    G[v << 1 | (!g)] = allc++;
}
bool dfs(int u) {
    if (mark[u ^ 1])
        return false;

    if (mark[u])
        return true;

    mark[u] = true;
    stk[top++] = u;

    for (edge *e = G[u]; e != nullptr; e = e->next) {
        if (!dfs(e->to))
            return false;
    }

    return true;
}
bool judge(int tot) {
    for (int i = 1; i <= tot; ++i) {
        if (!mark[i << 1] and !mark[i << 1 | 1]) {
            top = 0;

            if (!dfs(i << 1)) {
                while (top)
                    mark[stk[--top]] = false;

                if (!dfs(i << 1 | 1))
                    return false;
            }
        }
    }

    return true;
}
}  

int New() {
  tr[++tc] = {++dc, ++dc, 0, 0, 0, 0};
  return tc;
}

void Build(int &x, int l, int r, int dep, int k, int op) {
  x = New();
  if((op & 1) || ((op >> 2) & 1)) tr[x].u = ++dc;
  if(((op >> 1) & 1) || ((op >> 3) & 1)) tr[x].uu = ++dc;
  if(l == r) {
    Two_SAT::add_edge(tr[x].d, k, 0, 1);
    Two_SAT::add_edge(tr[x].d, k, 1, 0);
    Two_SAT::add_edge(tr[x].dd, k, 0, 0);
    Two_SAT::add_edge(tr[x].dd, k, 1, 1);
    if(op & 1) Two_SAT::add_edge(k, tr[x].u, 0, 1);
    if((op >> 1) & 1) Two_SAT::add_edge(k, tr[x].uu, 0, 1);
    if((op >> 2) & 1) Two_SAT::add_edge(k, tr[x].u, 1, 1);
    if((op >> 3) & 1) Two_SAT::add_edge(k, tr[x].uu, 1, 1);
    return;
  }
  int mid = (l + r) >> 1;
  if(dep <= mid) {
    Build(tr[x].ls, l, mid, dep, k, op);
    Two_SAT::add_edge(tr[x].d, tr[tr[x].ls].d, 1, 1);
    Two_SAT::add_edge(tr[x].dd, tr[tr[x].ls].dd, 1, 1);
    Two_SAT::add_edge(tr[tr[x].ls].u, tr[x].u, 1, 1);
    Two_SAT::add_edge(tr[tr[x].ls].uu, tr[x].uu, 1, 1);
  } else {
    Build(tr[x].rs, mid + 1, r, dep, k, op);
    Two_SAT::add_edge(tr[x].d, tr[tr[x].rs].d, 1, 1);
    Two_SAT::add_edge(tr[x].dd, tr[tr[x].rs].dd, 1, 1);
    Two_SAT::add_edge(tr[tr[x].rs].u, tr[x].u, 1, 1);
    Two_SAT::add_edge(tr[tr[x].rs].uu, tr[x].uu, 1, 1);
  }
}

void Modify(int x, int y, int l, int r, int _l, int _r) {
  if(!x) return;
  if(_l <= l && r <= _r) {
    Two_SAT::add_edge(tr[x].u, tr[y].d, 1, 1);
    Two_SAT::add_edge(tr[x].uu, tr[y].dd, 1, 1);
    Two_SAT::add_edge(tr[y].u, tr[x].d, 1, 1);
    Two_SAT::add_edge(tr[y].uu, tr[x].dd, 1, 1);
    return;
  }
  int mid = (l + r) >> 1;
  if(_l <= mid) Modify(tr[x].ls, y, l, mid, _l, _r);
  if(_r > mid) Modify(tr[x].rs, y, mid + 1, r, _l, _r);
}

void Update(int x, int y, int l, int r, int k) {
  if(!x) return;
  if(l == r) {
    int dl = max(k * 2 - l + depl, 1), dr = min(k * 2 - l + depr, mxd[1]);
    if(dl <= dr) Modify(y, x, 1, mxd[1], dl, dr);
    return;
  }
  int mid = (l + r) >> 1;
  Update(tr[x].ls, y, l, mid, k);
  Update(tr[x].rs, y, mid + 1, r, k);
}

int Merge(int x, int y) {
  if(!x || !y) return x + y;
  int z = New();
  if(tr[x].u || tr[y].u) tr[z].u = ++dc;
  if(tr[x].uu || tr[y].uu) tr[z].uu = ++dc;


  Two_SAT::add_edge(tr[z].d, tr[x].d, 1, 1);
  Two_SAT::add_edge(tr[z].dd, tr[x].dd, 1, 1);
  Two_SAT::add_edge(tr[z].d, tr[y].d, 1, 1);
  Two_SAT::add_edge(tr[z].dd, tr[y].dd, 1, 1);
  Two_SAT::add_edge(tr[x].u, tr[z].u, 1, 1);
  Two_SAT::add_edge(tr[x].uu, tr[z].uu, 1, 1);
  Two_SAT::add_edge(tr[y].u, tr[z].u, 1, 1);
  Two_SAT::add_edge(tr[y].uu, tr[z].uu, 1, 1);
  tr[z].ls = Merge(tr[x].ls, tr[y].ls);
  tr[z].rs = Merge(tr[x].rs, tr[y].rs);
  return z;
}

void Dfs(int x, int fa) {
  mxd[x] = 1, d[x] = d[fa] + 1, f[x] = fa;
  for(int y : e[x]) {
    if(y == fa) continue;
    Dfs(y, x);
    if(mxd[x] < mxd[y] + 1) {
      mxd[x] = mxd[y] + 1;
      son[x] = y;
    }
  }
}

void Dfss(int x, int fa) {
  for(int y : e[x]) {
    if(y == fa || y == son[x]) continue;
    Dfss(y, x);
  }
  Build(rt[x], 1, mxd[1], d[x], x, opt[x]);

  if(son[x]) {
    Dfss(son[x], x);
    Update(rt[x], rt[son[x]], 1, mxd[1], d[x]);
    rt[x] = Merge(rt[x], rt[son[x]]);
  }

  for(int y : e[x]) {
    if(y == fa || y == son[x]) continue;
    Update(rt[y], rt[x], 1, mxd[1], d[x]);
    rt[x] = Merge(rt[x], rt[y]);
  }

}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  cin >> n >> m >> depl >> depr;
  for(int i = 1, x, y; i < n; i++) {
    cin >> x >> y;
    e[x].push_back(y);
    e[y].push_back(x);
  }
  for(int i = 1, x, typ; i <= m; i++) {
    cin >> x >> typ;
    opt[x] |= 1 << typ;
  }
  dc = n;
  Dfs(1, 0);
  Dfss(1, 0);

  cout << (Two_SAT::judge(dc) ? "YES\n" : "NO\n");
  return 0;
}

