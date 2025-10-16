#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

typedef std::vector<int> vic;
typedef std::set<int> sit;

const int maxN = 1e5;
const int maxM = 1e5;

int n, m;
int a[maxN + 10];
int x[maxM + 10], y[maxM + 10];
int ans = 2147483647;
vic raw;
sit pos[maxN + 2 * maxM + 10];

void merge(int x, int y) {
    if (x == y) return;
    sit &a = pos[x];
    sit &b = pos[y];
    if (a.size() > b.size()) std::swap(a, b);
    for (auto i : a) {
        auto j = b.lower_bound(i);
        if (j != b.end()) ans = std::min(ans, *j - i);
        if (j != b.begin()) ans = std::min(ans, i - *(--j));
        b.insert(i);
    }
    a.clear();
    return;
}

int main() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) std::cin >> a[i];
    for (int i = 1; i <= m; i++) std::cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++) raw.push_back(a[i]);
    for (int i = 1; i <= m; i++) raw.push_back(x[i]);
    for (int i = 1; i <= m; i++) raw.push_back(y[i]);
    std::sort(raw.begin(), raw.end());
    raw.erase(std::unique(raw.begin(), raw.end()), raw.end());
    for (int i = 1; i <= n; i++) a[i] = std::lower_bound(raw.begin(), raw.end(), a[i]) - raw.begin() + 1;
    for (int i = 1; i <= m; i++) x[i] = std::lower_bound(raw.begin(), raw.end(), x[i]) - raw.begin() + 1;
    for (int i = 1; i <= m; i++) y[i] = std::lower_bound(raw.begin(), raw.end(), y[i]) - raw.begin() + 1;
    for (int i = 1; i <= n; i++) {
        if (pos[a[i]].size()) ans = std::min(ans, i - *pos[a[i]].rbegin());
        pos[a[i]].insert(i);
    }
    for (int i = 1; i <= m; i++) {
        merge(x[i], y[i]);
        std::cout << ans << '\n';
    }
    return 0;
}