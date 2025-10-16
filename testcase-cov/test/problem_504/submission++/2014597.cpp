#include <queue>
#include <iostream>

#define endl '\n'

using namespace std;
using PII = pair<int, int>;

const int N = 5e5 + 5;
const int INF = 1e9 + 1;

int n, m, a[N];

struct SegTree {
    struct {
        int l, r;
        int rmin, rmin_pos, tag_max;
    } node[N << 2];

    void pushup(int u) {
        auto &rt = node[u];
        auto &lc = node[u << 1];
        auto &rc = node[u << 1 | 1];

        rt.rmin = min(lc.rmin, rc.rmin);
        rt.rmin_pos = lc.rmin <= rc.rmin ? lc.rmin_pos : rc.rmin_pos;
    }

    void pushdown(int u) {
        auto &rt = node[u];
        auto &lc = node[u << 1];
        auto &rc = node[u << 1 | 1];

        if (rt.tag_max != -1) {
            lc.rmin = max(lc.rmin, rt.tag_max);
            rc.rmin = max(rc.rmin, rt.tag_max);
            lc.tag_max = max(lc.tag_max, rt.tag_max);
            rc.tag_max = max(rc.tag_max, rt.tag_max);
            rt.tag_max = -1;
        }
    }

    void build(int l = 1, int r = n, int u = 1) {
        node[u].l = l;
        node[u].r = r;
        node[u].tag_max = -1;

        if (l == r)
            return (void)(node[u].rmin = a[l], node[u].rmin_pos = l);

        int mid = (l + r) >> 1;

        build(l, mid, u << 1);
        build(mid + 1, r, u << 1 | 1);

        pushup(u);
    }

    void maximize(int l, int r, int x, int u = 1) {
        int nl = node[u].l, nr = node[u].r;

        if (nl >= l && nr <= r) {
            node[u].tag_max = max(node[u].tag_max, x);
            node[u].rmin = max(node[u].rmin, node[u].tag_max);
            return;
        }

        pushdown(u);

        int mid = (nl + nr) >> 1;

        if (l <= mid) maximize(l, r, x, u << 1);
        if (r > mid) maximize(l, r, x, u << 1 | 1);

        pushup(u);
    }

    void increment(int x, int v, int u = 1) {
        int nl = node[u].l, nr = node[u].r;

        if (nl == nr) {
            node[u].rmin += v;
            node[u].rmin_pos = nl;
            return;
        }

        pushdown(u);

        int mid = (nl + nr) >> 1;

        if (x <= mid) increment(x, v, u << 1);
        else increment(x, v, u << 1 | 1);

        pushup(u);
    }

    PII query_min(int l, int r, int u = 1) {
        int nl = node[u].l, nr = node[u].r;

        if (nl >= l && nr <= r)
            return PII(node[u].rmin, node[u].rmin_pos);

        pushdown(u);

        int mid = (nl + nr) >> 1;
        PII ret(INF, 0);

        if (l <= mid) {
            PII lsub = query_min(l, r, u << 1);
            if (lsub.first < ret.first)
                ret = lsub;
        }

        if (r > mid) {
            PII rsub = query_min(l, r, u << 1 | 1);
            if (rsub.first < ret.first)
                ret = rsub;
        }

        return ret;
    }
} SGT;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    SGT.build();

    cin >> m;
    while (m--) {
        int type, l, r, k, x;
        cin >> type >> l >> r >> k;

        if (type == 1)
            SGT.maximize(l, r, k);
        else {
            cin >> x;
            int t = x;
            queue<PII> popped;

            while (t--) {
                auto [val, pos] = SGT.query_min(l, r);
                if (val >= k) break;
                popped.emplace(val, pos);
                SGT.increment(pos, INF);
            }

            if (popped.size() < (size_t)x) {
                cout << -1 << endl;
                while (!popped.empty()) {
                    auto [val, pos] = popped.front();
                    popped.pop();
                    SGT.increment(pos, -INF);
                }
            } else {
                while (!popped.empty()) {
                    auto [val, pos] = popped.front();
                    popped.pop();
                    cout << val << ' ';
                    SGT.increment(pos, -INF);
                }
                cout << endl;
            }
        }
    }

    return fflush(stdout), 0;
}
