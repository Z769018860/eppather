#include <bits/stdc++.h>
#define ALL(x) begin(x), end(x)
#define All(x, l, r) &x[l], &x[(r) + 1]
using namespace std;
void file(){
  freopen("1.in", "r", stdin);
  freopen("1.out", "w", stdout);
}
using ll = long long;
const int nMax = (1 << 22) + 5, mod = 1000000007;
int n, m, k;
array<int, nMax> s;
int qpow(int x, int y){
  int b = x, r = 1;
  for(; y; b = (ll)b * b % mod, y /= 2) if(y & 1) r = (ll)r * b % mod;
  return r;
}
int main(){
  
  ios::sync_with_stdio(0); cin.tie(0);
  cin >> n >> m >> k;
  for(int i = 1, x; i <= m; i++){ cin >> x; s[x]++; }
  for(int i = 0; i < n; i++){
    for(int j = (1 << n) - 1; ~j; j--){
      if(!((j >> i) & 1)) (s[j] += s[j ^ (1 << i)]) %= mod;
    }
  }
  int res = 0;
  for(int i = 1; i < (1 << n); i++){
    int ml = (__builtin_popcount(i) & 1) ? 1 : mod - 1;
    (res += (ll)ml * qpow(s[i], k) % mod) %= mod;
  }
  cout << res << "\n";
  return 0;
}