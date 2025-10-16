#include <iostream>
#include <random>

using namespace std;
using Pr = pair<int, int>; 

const int N = 3e5 + 5; 

int n;

namespace Treap {
  const int T = N * 54;
  int lc[T], rc[T]; 
  int dat[T], siz[T]; 
  int val[T], tot;
  mt19937 R(0);

  int node (int x) {
    val[++tot] = x; 
    siz[tot] = 1; 
    dat[tot] = R();
    return tot; 
  }

  void copy (int k, int p) {
    lc[k] = lc[p], rc[k] = rc[p];
    dat[k] = dat[p], siz[k] = siz[p];
    val[k] = val[p];
  }

  void pushup (int k) {
    siz[k] = siz[lc[k]] + siz[rc[k]] + 1; 
  }

  Pr split (int k, int x) {
    if (!k) return {0, 0};
    int _k = ++tot;
    copy(_k, k);
    if (x <= siz[lc[k]]) {
      Pr t = split(lc[k], x);
      lc[_k] = t.second;
      pushup(_k);
      return {t.first, _k};
    }
    else {
      Pr t = split(rc[k], x - siz[lc[k]] - 1);
      rc[_k] = t.first;
      pushup(_k);
      return {_k, t.second};
    }
  }

  int merge (int u, int v) {
    if (!u || !v) return u | v; 
    int r = ++tot;
    if (dat[u] < dat[v]) {
      copy(r, u);
      rc[r] = merge(rc[u], v);
    }    
    else {
      copy(r, v);
      lc[r] = merge(u, lc[v]);
    }
    pushup(r);
    return r; 
  }

  struct treap {
    int rt[N], now;

    void insert (int v, int p, int x) {
      Pr t = split(rt[v], p - 1);
      rt[++now] = merge(merge(t.first, node(x)), t.second);
    }

    void erase (int v, int p) {
      Pr tr = split(rt[v], p);
      Pr tl = split(tr.first, p - 1);
      rt[++now] = merge(tl.first, tr.second);
    } 

    int query (int v, int p) {
      Pr t = split(rt[v], p);  
      int k = t.first; 
      while (rc[k]) k = rc[k];
      return val[k]; 
    }
  };
} 
Treap::treap t;

int main () {
  ios::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cin >> n;
  for (int o, v, p, x; n--; ) {
    cin >> o >> v >> p; 
    if (o == 1) {
      cin >> x;
      t.insert(v, p, x);
    } 
    else if (o == 2) {
      t.erase(v, p);
    }
    else if (o == 3) {
      cout << t.query(v, p) << '\n';
    }
  }
  return 0; 
}