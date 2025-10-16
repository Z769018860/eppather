#include <bits/stdc++.h>

signed main() {
  std::istream &fin = std::cin;
  std::ostream &fout = std::cout;

  int n, m;
  fin >> n >> m;

  std::vector<int> a(n), val;

  for (int i = 0; i < n; ++i) {
    fin >> a[i];
    val.emplace_back(a[i]);
  }

  std::vector<int> x(m), y(m);

  for (int i = 0; i < m; ++i) {
    fin >> x[i] >> y[i];
    val.emplace_back(x[i]);
    val.emplace_back(y[i]);
  }

  std::sort(val.begin(), val.end());
  val.erase(std::unique(val.begin(), val.end()), val.end());

  int t = val.size();
  std::vector<std::set<int>> S(t);
  std::vector<int> col(t);
  int res = std::numeric_limits<int>::max();

  auto getid = [&](int x) {
    return std::lower_bound(val.begin(), val.end(), x) - val.begin();
  };

  auto insert = [&](auto &S, int x) {
    auto [it, tmp] = S.emplace(x);

    if (it != S.begin()) {
      res = std::min(res, x - *prev(it));
    }

    if (next(it) != S.end()) {
      res = std::min(res, *next(it) - x);
    }
  };

  std::iota(col.begin(), col.end(), 0);

  for (int i = 0; i < n; ++i) {
    a[i] = getid(a[i]);
    insert(S[a[i]], i);
  }

  for (int i = 0; i < m; ++i) {
    x[i] = getid(x[i]);
    y[i] = getid(y[i]);

    auto merge = [&](int x, int y) {
      if (S[x].size() > S[y].size()) {
        S[x].swap(S[y]);
      }
      
      for (int i : S[x]) {
        insert(S[y], i);
      }

      S[x].clear();
      col[x] = y;
    };

    merge(x[i], y[i]);
    fout << res << '\n';
  }
}