#include <bits/stdc++.h>
#define db double
#define il inline
#define re register
#define ll long long
#define ui unsigned
#define ull ui ll
#define pii pair<int, int>
#define fi first
#define se second
#define eb emplace_back
#define SZ(v) (int)v.size()
#define ALL(v) v.begin(), v.end()
using namespace std;
#define N 1000005
int L, R, v[N]; ll ans;
int cnt, Lst, Rst, len[N], lnk[N], to[N][26], d[N];
il void insL(int c) {
  v[--L] = c; int p = Lst;
  while(v[L] != v[L + len[p] + 1]) p = lnk[p];
  if(!to[p][c]) {
    int cur = ++cnt, q = lnk[p]; len[cur] = len[p] + 2;
    while(v[L] != v[L + len[q] + 1]) q = lnk[q];
    lnk[cur] = to[q][c], to[p][c] = cur, d[cur] = d[lnk[cur]] + 1;
  }
  Lst = to[p][c], ans += d[Lst];
  if(len[Lst] == R - L + 1) Rst = Lst;
}
il void insR(int c) {
  v[++R] = c; int p = Rst;
  while(v[R] != v[R - len[p] - 1]) p = lnk[p];
  if(!to[p][c]) {
    int cur = ++cnt, q = lnk[p]; len[cur] = len[p] + 2;
    while(v[R] != v[R - len[q] - 1]) q = lnk[q];
    lnk[cur] = to[q][c], to[p][c] = cur, d[cur] = d[lnk[cur]] + 1;
  }
  Rst = to[p][c], ans += d[Rst];
  if(len[Rst] == R - L + 1) Lst = Rst;
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  memset(v, -1, sizeof(v));
  lnk[0] = cnt = 1, len[1] = -1;
  string s; cin >> s; L = N / 2, R = L - 1;
  for(auto c : s) insR(c - 'a');
  int T; cin >> T; while(T--) {
    int op; cin >> op;
    if(op == 3) {cout << ans << "\n"; continue;} cin >> s;
    for(auto c : s) op == 2 ? insL(c - 'a') : insR(c - 'a');
  }
  cerr << 1.0 * clock() / CLOCKS_PER_SEC;
  return 0;
}