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
int dfn[kmax * 300], low[kmax * 300], idx;
int stk[kmax * 300], tp, scc[kmax * 300], scc_cnt;
bool instk[kmax * 300];
vector<int> e[kmax], ee[kmax * 300];

void Addedge(int x, int y, bool ox, bool oy) {
  if(!x || !y) return;
  ee[x * 2 - ox].push_back(y * 2 - oy);
  ox ^= 1, oy ^= 1;
  ee[y * 2 - oy].push_back(x * 2 - ox);
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
    Addedge(tr[x].d, k, 0, 1);
    Addedge(tr[x].d, k, 1, 0);
    Addedge(tr[x].dd, k, 0, 0);
    Addedge(tr[x].dd, k, 1, 1);
    if(op & 1) Addedge(k, tr[x].u, 0, 1);
    if((op >> 1) & 1) Addedge(k, tr[x].uu, 0, 1);
    if((op >> 2) & 1) Addedge(k, tr[x].u, 1, 1);
    if((op >> 3) & 1) Addedge(k, tr[x].uu, 1, 1);
    return;
  }
  int mid = (l + r) >> 1;
  if(dep <= mid) {
    Build(tr[x].ls, l, mid, dep, k, op);
    Addedge(tr[x].d, tr[tr[x].ls].d, 1, 1);
    Addedge(tr[x].dd, tr[tr[x].ls].dd, 1, 1);
    Addedge(tr[tr[x].ls].u, tr[x].u, 1, 1);
    Addedge(tr[tr[x].ls].uu, tr[x].uu, 1, 1);
  } else {
    Build(tr[x].rs, mid + 1, r, dep, k, op);
    Addedge(tr[x].d, tr[tr[x].rs].d, 1, 1);
    Addedge(tr[x].dd, tr[tr[x].rs].dd, 1, 1);
    Addedge(tr[tr[x].rs].u, tr[x].u, 1, 1);
    Addedge(tr[tr[x].rs].uu, tr[x].uu, 1, 1);
  }
}

void Modify(int x, int y, int l, int r, int _l, int _r) {
  if(!x) return;
  if(_l <= l && r <= _r) {
    Addedge(tr[x].u, tr[y].d, 1, 1);
    Addedge(tr[x].uu, tr[y].dd, 1, 1);
    Addedge(tr[y].u, tr[x].d, 1, 1);
    Addedge(tr[y].uu, tr[x].dd, 1, 1);
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


  Addedge(tr[z].d, tr[x].d, 1, 1);
  Addedge(tr[z].dd, tr[x].dd, 1, 1);
  Addedge(tr[z].d, tr[y].d, 1, 1);
  Addedge(tr[z].dd, tr[y].dd, 1, 1);
  Addedge(tr[x].u, tr[z].u, 1, 1);
  Addedge(tr[x].uu, tr[z].uu, 1, 1);
  Addedge(tr[y].u, tr[z].u, 1, 1);
  Addedge(tr[y].uu, tr[z].uu, 1, 1);
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

void Tarjan(int x) {
  dfn[x] = low[x] = ++idx;
  stk[++tp] = x, instk[x] = 1;
  for(int y : ee[x]) {
    if(!dfn[y]) {
      Tarjan(y);
      low[x] = min(low[x], low[y]);
    } else if(instk[y]) {
      low[x] = min(low[x], dfn[y]);
    }
  }
  if(dfn[x] == low[x]) {
    for(scc_cnt++; tp && stk[tp] != x; tp--) {
      scc[stk[tp]] = scc_cnt;
      instk[stk[tp]] = 0;
    }
    scc[stk[tp]] = scc_cnt;
    instk[stk[tp]] = 0;
    tp--;
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
  for(int i = 1; i <= dc * 2; i++) {
    if(!dfn[i]) Tarjan(i);
  }
  for(int i = 1; i <= dc; i++) {
    if(scc[i * 2 - 1] == scc[i * 2]) {
      cout << "NO\n";
      return 0;
    }
  }
  cout << "YES\n";
  return 0;
}
