#include<bits/stdc++.h>
#define lb(u) (u&(-u))
using namespace std;
const int N = 1.2e6 + 5;
int read(int t = 0, bool f = 1, char c = 0) {
	while(!isdigit(c = getchar())) f = c^45;
	while(isdigit(c)) t = (t << 1) + (t << 3) + (c ^ 48), c = getchar();
	return f ? t: -t;
}
int n, m, k, mn;
array<int, N> p, q;
map<int, int> mp, b;
signed main() {
	
  
  n = read();
  for (int i = 1; i <= n; ++i) p[i] = read();
  m = read();
  for (int i = 1; i <= m; ++i) q[i] = read(), mp[q[i]]++, b[lb(q[i])]++;
  sort(p.begin() + 1, p.begin() + n + 1, [](int a, int b) { return lb(a) > lb(b); });
  long long ans = 0;
  k = min({read(), n, m});
  for (int i = 1; i <= n && k > 0; ) {
    int j = i;
    while (j <= n && lb(p[j]) == lb(p[i])) ++j;--j;
    for (int w = i; w <= j; ++w) 
      if (k > 0 && mp[p[w]] > 0 && b[lb(p[w])] > 0) mp[p[w]]--, b[lb(p[w])]--, p[w] = 0, --k; 
    for (; i <= j; ++i) {
      if (p[i]) {
        while (!b[1ll << mn]) ++mn, cerr << mn << endl;
        if (k && (1ll << mn) < lb(p[i])) b[1ll << mn]--, --k, ans += (1ll << mn), p[i] = 0;
      }    
    }
  } for (int i = 1; i <= n; ++i) if (p[i]) ans += lb(p[i]);
  cout << ans << '\n';
  return 0;
}  