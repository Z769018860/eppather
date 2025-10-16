#include <iostream>
#include <vector>
#include <algorithm>

#define int long long

using namespace std;

const int MAXN = 1000001;
int N, M, R;
vector<int> graph[MAXN];
int value[MAXN], start[MAXN], finish[MAXN], dfsOrder[MAXN], timer;

class SegmentTree {
private:
    vector<long long> tree;
    int size;

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] += val;
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(node * 2, start, mid, idx, val);
        else update(node * 2 + 1, mid + 1, end, idx, val);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    long long query(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return query(node * 2, start, mid, l, r) +
               query(node * 2 + 1, mid + 1, end, l, r);
    }

public:
    SegmentTree(int n): tree(4 * n + 1, 0), size(n)  {}

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = value[dfsOrder[start]];
            return;
        }
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    void update(int idx, int val) {
        update(1, 1, size, idx, val);
    }

    long long query(int l, int r) {
        return query(1, 1, size, l, r);
    }
};

void dfs(int node, int parent) {
    start[node] = ++timer;
    dfsOrder[timer] = node;
    for (int child : graph[node]) {
        if (child != parent) {
            dfs(child, node);
        }
    }
    finish[node] = timer;
}

signed main() {
    cin >> N >> M >> R;
    for (int i = 1; i <= N; ++i) cin >> value[i];
    for (int i = 1; i < N; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    timer = 0;
    dfs(R, -1);

    SegmentTree segTree(N);
    segTree.build(1, 1, N);

    while (M--) {
        int op, x, val;
        cin >> op;
        if (op == 1) {
            cin >> x >> val;
            segTree.update(start[x], val);
        } else {
            cin >> x;
            cout << segTree.query(start[x], finish[x]) << endl;
        }
    }
    return 0;
}