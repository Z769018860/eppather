#include <bits/extc++.h>
#define ALL(v) begin(v), end(v)
using i64 = int64_t;
using std::cin;
using std::cout;
constexpr int N = 2e7 + 5;

int cnt;
i64 n, m, ans;
std::array<int, N> p, mu, sum_mu, sum_mu2;
std::array<bool, N> vis;
__gnu_pbds::cc_hash_table<i64, i64> sum_mu_map, sum_mu2_map;

auto euler_sieve() {
   vis[1] = mu[1] = sum_mu2[1] = 1;
   for (auto i = 2; i < N; ++i) {
      if (!vis[i]) p[++cnt] = i, mu[i] = -1, sum_mu2[i] = 1;
      for (auto j = 1; j <= cnt && (i64)i * p[j] < N; ++j) {
         vis[i * p[j]] = 1;
         if (i % p[j]) mu[i * p[j]] = -mu[i], sum_mu2[i * p[j]] = sum_mu2[i];
         else { mu[i * p[j]] = sum_mu2[i * p[j]] = 0; break;}
      }
   }
   for (auto i = 1; i < N; ++i)
      sum_mu[i] = sum_mu[i - 1] + mu[i], sum_mu2[i] += sum_mu2[i - 1];
   return ;
}

auto get_sum_mu(i64 n) -> i64 {
   if (n < N) return sum_mu[n];
   if (sum_mu_map.find(n) != sum_mu_map.end()) return sum_mu_map[n];
   auto ret = i64{1}, l = i64{2}, r = i64{0}; 
   while (l <= n) {
      auto x = n / l; r = n / x;
      ret -= (r - l + 1) * get_sum_mu(x);
      l = r + 1;
   }
   return sum_mu_map[n] = ret;
}

auto get_sum_mu2(i64 n) -> i64{
   if (n < N) return sum_mu2[n];
   if (sum_mu2_map.find(n) != sum_mu2_map.end()) return sum_mu2_map[n];
   auto ret = i64{0}, m = i64{1};
   for (m = 1; m * m * m <= n; ++m) ret += (i64)mu[m] * (n / (m * m));
   m--;
   for (auto i = m; i; --i) ret += get_sum_mu(sqrt(n / i)) - sum_mu[m];
   return sum_mu2_map[n] = ret;
}

auto main() -> int {
   std::ios::sync_with_stdio(false);
   cin.tie(nullptr), cout.tie(nullptr);

   cin >> n >> m;
   if (n > m) std::swap(n, m);
   euler_sieve();
   auto l = i64{1}, r = i64{0}, lst = i64{0};
   while (l <= n) {
      auto a = (i64)sqrt(n / l), b = (i64)sqrt(m / l);
      r = std::min(n / (a * a), m / (b * b));
      auto cur = get_sum_mu2(r);
      ans += a * b * (cur - lst), lst = cur, l = r + 1;
   }
   cout << ans << "\n";
   return 0;
}