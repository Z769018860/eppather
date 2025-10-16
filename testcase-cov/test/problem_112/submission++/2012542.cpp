#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5 + 10;

template<typename T, size_t k, size_t size>
struct KD_PartialOrder {
    static constexpr int B = int(sqrt(size)) + 1;
    KD_PartialOrder() {}
    virtual bool cmp(int d, int x, int y) {
        return val[d][x] < val[d][y];
    }
    T val[k][size];
    int rk[k][size], ord[k][size];
    bitset<size> f[k][B + 1];
    void init(int n) {
        for (int i = 0; i < int(k); ++i) {
            iota(ord[i], ord[i] + n, 0);
            sort(ord[i], ord[i] + n, [&](int x, int y) { return cmp(i, x, y); });
            for (int j = 0; j < n; ++j) rk[i][ord[i][j]] = j;
            for (int j = 1; j <= B; ++j) {
                for (int l = 0; l < n; ++l) {
                    f[i][j][l] = rk[i][l] < B * j;
                }
            }
        }
    }
    int query(int n, int p) {
        static bitset<size> ans, tmp;
        ans.set();
        for (int i = 0; i < int(k); ++i) {
            tmp.reset();
            int pos = rk[i][p] / B;
            tmp |= f[i][pos];
            int r = upper_bound(ord[i], ord[i] + n, p, [&](int x, int y) { return cmp(i, x, y); }) - ord[i];
            for (int j = pos * B; j < r; ++j) {
                tmp[ord[i][j]] = true;
            }
            ans &= tmp;
        }
        return ans.count();
    }
};

KD_PartialOrder<int, 3, MAXN> d;
int n, k, cnt[MAXN];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 0; i < n; ++i) cin >> d.val[0][i] >> d.val[1][i] >> d.val[2][i];
    d.init(n);
    for (int i = 0; i < n; ++i) ++cnt[d.query(n, i)];
    for (int i = 1; i <= n; ++i) cout << cnt[i] << "\n";

    return 0;
}