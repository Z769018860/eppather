#include <algorithm>
#include <cstdio>
#include <functional>
#include <numeric>

int n, k, a[100005], b[100005];
double l, r = 1, c[100005];

bool check(double mid) {
  for (int i = 0; i < n; ++i) c[i] = a[i] - mid * b[i];
  std::sort(c, c + n, std::greater<double>{});
  return std::accumulate(c, c + k, 0.) > 0.;
}

int main() {
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i) scanf("%d", a + i);
  for (int i = 0; i < n; ++i) scanf("%d", b + i);
  while (r - l > 1e-6) {
    double mid = l + (r - l) / 2;
    (check(mid) ? l : r) = mid;
  }
  printf("%.10lf", l);
}