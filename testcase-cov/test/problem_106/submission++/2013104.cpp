#include <bits/stdc++.h>
using namespace std;
namespace io {
template<typename T>inline void read(T &x) {
  char ch, f = 0; x = 0;
  while (!isdigit(ch = getchar())) f |= ch == '-';
  while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  x = f? -x: x;
}
char ch[40];
template<typename T>inline void write(T x) {
  (x < 0) && (putchar('-'), x = -x);
  x || putchar('0');
  int i = 0;
  while (x) ch[i++] = x % 10 ^ 48, x /= 10;
  while (i) putchar(ch[--i]);
}
}
#define rd io::read
#define wt io::write
const int maxN = 100100;
const int inf = 2147483647;
const double alpha = 0.32;
const double beta = (1 - 2 * alpha) / (1 - alpha);
struct SBT {
  int ch[2], siz, v;
}t[maxN * 20];
int cnt;
stack<int> st;
inline int create() { 
  if (st.empty()) return ++cnt;
  int f = st.top(); st.pop();
  return f;
}
inline void trash(int x) { t[x] = {0, 0, 0, 0}; st.push(x); }
struct Leafy {
  int root;
  inline void pushup(int x) { t[x].siz = t[t[x].ch[0]].siz + t[t[x].ch[1]].siz; t[x].v = t[t[x].ch[1]].v; }
inline void rotate(int x, bool op) {
  if (!t[x].ch[0]) return;
  int b = t[x].ch[op], c = t[x].ch[op ^ 1];
  t[x].ch[op ^ 1] = b;
  t[x].ch[op] = t[b].ch[op];
  t[b].ch[op] = t[b].ch[op ^ 1];
  t[b].ch[op ^ 1] = c;
  pushup(b); pushup(x);
}
  inline void maintain(int x) {
    if (!t[x].ch[0]) return;
    int p;
    if (t[t[x].ch[0]].siz < t[x].siz * alpha) p = 1;
    else if (t[t[x].ch[1]].siz < t[x].siz * alpha) p = 0;
    else return;
    (t[t[t[x].ch[p]].ch[p ^ 1]].siz > t[t[x].ch[p]].siz * beta) && (rotate(t[x].ch[p], p ^ 1), 0);
    rotate(x, p);
  }
  void insert(int x, int k) {
    if (!k) { t[root = k = create()] = {0, 0, 1, x}; return; }
    if (!t[k].ch[0]) {
      int a = create(), b = create();
      (x > t[k].v) && (swap(x, t[k].v), 0);
      t[a] = {0, 0, 1, x}; t[b] = {0, 0, 1, t[k].v};
      t[k].ch[0] = a; t[k].ch[1] = b;
      pushup(k);
      return;
    }
    insert(x, t[k].ch[x > t[t[k].ch[0]].v]);
    pushup(k); maintain(k);
  }
  void erase(int x, int k) {
    int w = x > t[t[k].ch[0]].v;
    if (!t[t[k].ch[w]].ch[0]) {
      trash(t[k].ch[w]);
      int a = t[k].ch[w ^ 1];
      t[k] = t[a];
      trash(a);
      return;
    }
    erase(x, t[k].ch[x > t[t[k].ch[0]].v]);
    pushup(k); maintain(k);
  }
  int qrank(int x, int k) {
    if (!t[k].ch[0]) return 1;
    int w = x > t[t[k].ch[0]].v;
    return w * t[t[k].ch[0]].siz + qrank(x, t[k].ch[w]);
  }
  int atrank(int x, int k) {
    if (!t[k].ch[0]) return t[k].v;
    int w = x > t[t[k].ch[0]].siz;
    return atrank(x - w * t[t[k].ch[0]].siz, t[k].ch[w]);
  }
  inline int pre(int x) { return atrank(qrank(x, root) - 1, root); }
  inline int nxt(int x) { return atrank(qrank(x + 1, root), root); }
}sbt[maxN << 1];
int n, a[maxN], m;
void build(int k = 1, int l = 1, int r = n) {
  sbt[k].insert(inf, sbt[k].root); sbt[k].insert(-inf , sbt[k].root);
  for (int i = l; i <= r; ++i)
    sbt[k].insert(a[i], sbt[k].root);
  if (l == r) return;
  int mid = l + r >> 1;
  build(k << 1, l, mid);
  build(k << 1|1, mid + 1, r);
}
void update(int x, int v, int k = 1, int l = 1, int r = n) {
  sbt[k].erase(a[x], sbt[k].root);
  sbt[k].insert(v, sbt[k].root);
  if (l == r) {
    a[x] = v;
    return;
  }
  int mid = l + r >> 1;
  if (x <= mid) update(x, v, k << 1, l, mid);
  else update(x, v, k << 1|1, mid + 1, r);
}
int query1(int x, int y, int v, int k = 1, int l = 1, int r = n) {
  if (x <= l && r <= y) return sbt[k].qrank(v, sbt[k].root) - 2;
  int mid = l + r >> 1, s = 0;
  if (x <= mid) s += query1(x, y, v, k << 1, l, mid);
  if (y > mid) s += query1(x, y, v, k << 1|1, mid + 1, r);
  return s;
}
inline int qval(int x, int y, int v) {
  int l = 0, r = 1e8, ans = 0, mid;
  while (l <= r) {
    mid = l + r >> 1;
    if (query1(x, y, mid) + 1 > v)  r = mid - 1;
    else ans = mid, l = mid + 1;
  }
  return ans;
}
int query3(int x, int y, int v, int k = 1, int l = 1, int r = n) {
  if (x <= l && r <= y) return sbt[k].pre(v);
  int mid = l + r >> 1, s = -inf;
  if (x <= mid) s = max(s, query3(x, y, v, k << 1, l, mid));
  if (y > mid) s = max(s, query3(x, y, v, k << 1|1, mid + 1, r));
  return s;
}
int query4(int x, int y, int v, int k = 1, int l = 1, int r = n) {
  if (x <= l && r <= y) return sbt[k].nxt(v);
  int mid = l + r >> 1, s = inf;
  if (x <= mid) s = min(s, query4(x, y, v, k << 1, l, mid));
  if (y > mid) s = min(s, query4(x, y, v, k << 1|1, mid + 1, r));
  return s;
}
int main() {
#ifdef LOCAL
  clock_t startTime = clock();
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
#endif
  
  rd(n); rd(m);
  for (int i = 1; i <= n; ++i) rd(a[i]);
  build();
  for (int i = 1, opt, x, y, v; i <= m; ++i) {
    rd(opt);
    if (opt == 3) {
      rd(x); rd(v);
      update(x, v);
    } else {
      rd(x); rd(y); rd(v);
      if (opt == 1) wt(query1(x, y, v) + 1);
      else if (opt == 2) wt(qval(x, y, v));
      else if (opt == 4) wt(query3(x, y, v));
      else wt(query4(x, y, v));
      putchar('\n');
    }
  }
  
#ifdef LOCAL
  cerr << "Times: " << clock() - startTime << "ms" << endl;
#endif
  return 0;
}