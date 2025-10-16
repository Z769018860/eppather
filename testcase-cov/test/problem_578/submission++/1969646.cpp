#include<bits/stdc++.h>
#define ll long long
#define db double
#define ull unsigned long long
#define pb push_back
#define pii pair<int, int>
#define FR first
#define SE second
#define int long long
using namespace std;
inline int read() {
  int x = 0; bool op = false;
  char c = getchar();
  while(!isdigit(c))op |= (c == '-'), c = getchar();
  while(isdigit(c))x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
  return op ? -x : x;
}
const int N = 2e5 + 10;
const int INF = 1e9;
int n, Q;
int a[N], cnt[N];
struct Node {
  int rp, ls;
  int psum, ssum, mx, tg;
}nd[N << 2];
void mark(int k, int w) {nd[k].mx += w; nd[k].tg += w;}
void pushdown(int k) {
  if(!nd[k].tg)return ;
  mark(k << 1, nd[k].tg);
  mark(k << 1 | 1, nd[k].tg);
  nd[k].tg = 0;
  return ;
}
int find1(int k, int l, int r, int v) {
  if(l == r)return min(cnt[l], max(0ll, nd[k].mx - v + 1)) * l;
  int mid = l + r >> 1; pushdown(k);
  if(nd[k << 1].mx < v)return find1(k << 1 | 1, mid + 1, r, v);
  else return find1(k << 1, l, mid, v) + nd[k].rp;
}
int find2(int k, int l, int r, int v) {
  if(l == r)return (nd[k].mx >= v) * (l + 1);
  int mid = l + r >> 1; pushdown(k);
  
  if(nd[k << 1 | 1].mx < v)return find2(k << 1, l, mid, v);
  else return nd[k].ls + find2(k << 1 | 1, mid + 1, r, v);
}
void pushup(int k, int l, int r) {
  int mid = l + r >> 1;
  nd[k].mx = max(nd[k << 1].mx, nd[k << 1 | 1].mx);
  nd[k].rp = find1(k << 1 | 1, mid + 1, r, nd[k << 1].mx + 1);
  nd[k].psum = nd[k << 1].psum + nd[k].rp;
  nd[k].ls = find2(k << 1, l, mid, nd[k << 1 | 1].mx + 1);
  nd[k].ssum = nd[k].ls + nd[k << 1 | 1].ssum;
  return ;
}
void update(int k, int l, int r, int qx, int qy, int w) {
  if(l >= qx && r <= qy)return mark(k, w), void();
  int mid = l + r >> 1; pushdown(k);
  if(qx <= mid)update(k << 1, l, mid, qx, qy, w);
  if(qy > mid)update(k << 1 | 1, mid + 1, r, qx, qy, w);
  pushup(k, l, r);
  return ;
}
int qmax(int k, int l, int r, int qx, int qy) {
  if(l >= qx && r <= qy)return nd[k].mx;
  int mid = l + r >> 1, res = -INF; pushdown(k);
  if(qx <= mid)res = max(res, qmax(k << 1, l, mid, qx, qy));
  if(qy > mid)res = max(res, qmax(k << 1 | 1, mid + 1, r, qx, qy));
  return res;
}
int qry1(int k, int l, int r, int qx, int qy, int &v) {
  if(l >= qx && r <= qy) {
    int res = find1(k, l, r, v);
    v = max(v, nd[k].mx + 1);
    return res;
  }
  int mid = l + r >> 1, res = 0; pushdown(k);
  if(qx <= mid)res += qry1(k << 1, l, mid, qx, qy, v);
  if(qy > mid)res += qry1(k << 1 | 1, mid + 1, r, qx, qy, v);
  return res;
}
int qry2(int k, int l, int r, int qx, int qy, int &v) {
  if(l >= qx && r <= qy) {
    int res = find2(k, l, r, v);
    
    v = max(v, nd[k].mx + 1);
    return res;
  }
  int mid = l + r >> 1, res = 0; pushdown(k);
  if(qy > mid)res += qry2(k << 1 | 1, mid + 1, r, qx, qy, v);
  if(qx <= mid)res += qry2(k << 1, l, mid, qx, qy, v);
  return res;
}
void build(int k, int l, int r) {
  if(l == r)return nd[k] = {0, 0, l, l + 1, -l, 0}, void();
  int mid = l + r >> 1;
  build(k << 1, l, mid); build(k << 1 | 1, mid + 1, r);
  pushup(k, l, r);
  return ;
}
signed main() {
  n = read(); Q = read();
  build(1, 0, n * 2);
  for(int i = 1; i <= n; i++) {
    a[i] = read(); cnt[a[i]]++;
    update(1, 0, n * 2, a[i], n * 2, 1);
  }
  while(Q--) {
    int op = read();
    if(op == 1) {
      int i = read(), v = read();
      cnt[a[i]]--; 
      update(1, 0, n * 2, a[i], n * 2, -1);
      a[i] = v; cnt[a[i]]++;
      update(1, 0, n * 2, a[i], n * 2, 1);
    }
    else {
      int l = read(), r = read(), ans = 0;
      int tv = (l < r ? qmax(1, 0, n * 2, l, r - 1) : -INF) + 1, v;
      v = tv; ans += qry1(1, 0, n * 2, r, n * 2, v); 
      v = tv; ans += qry2(1, 0, n * 2, 0, l - 1, v); 
      tv = qmax(1, 0, n * 2, l, n * 2) + 1;
      
      v = tv; ans -= qry1(1, 0, n * 2, r, n * 2, v); 
      v = tv; ans -= qry2(1, 0, n * 2, 0, l - 1, v); 
      printf("%lld\n", ans);
    }
  }
  return 0;
}