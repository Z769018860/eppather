#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;
int n, A[N][2], pre[2] = {0, 0};

mt19937 Rand(time(0));

struct Treap {
    struct node {int lc, rc, val, siz, key; } C[N * 30];
    int cnt, root;
    Treap() {cnt = 0, root = 0; C[root].lc = C[root].rc = C[root].val = C[root].siz = 0; C[root].key = Rand(); }
    inline int New(int val = 0) {
        ++cnt; C[cnt].lc = C[cnt].rc = 0, C[cnt].val = val, C[cnt].siz = 1, C[cnt].key = Rand();
        return cnt;
    }
    inline void Maintain(int u) {C[u].siz = 1 + C[C[u].lc].siz + C[C[u].rc].siz; }
    int Merge(int a, int b) {
        if(!a || !b) return (a + b);
        if(C[a].key >= C[b].key) {C[a].rc = Merge(C[a].rc, b); Maintain(a); return a; }
        else {C[b].lc = Merge(a, C[b].lc); Maintain(b); return b; }
    }
    void Split_val(int u, int val, int &x, int &y) {
        if(!u) {x = 0, y = 0; return; }
        if(C[u].val < val) {x = u; Split_val(C[u].rc, val, C[u].rc, y); Maintain(x); }
        else {y = u; Split_val(C[u].lc, val, x, C[u].lc); Maintain(y); }
    }
    inline void Delete(int val) {
        int x, y, z; Split_val(root, val, x, y), Split_val(y, val + 1, y, z);
        assert(y); y = Merge(C[y].lc, C[y].rc); root = Merge(x, Merge(y, z));
    }
    inline void Insert(int val) {
        int u = New(val), x, y; Split_val(root, val, x, y);
        root = Merge(Merge(x, u), y);
    }
    inline int Ask_More(int val) {
        int x, y; Split_val(root, val + 1, x, y);
        int ans = C[y].siz; root = Merge(x, y);
        return ans;
    }
    inline int Ask_Less(int val) {
        int x, y; Split_val(root, val, x, y);
        int ans = C[x].siz; root = Merge(x, y);
        return ans;
    }
} MaxX, MaxY, MinX, MinY;

int ans[2] = {0, 0}, delta[2] = {0, 0}; int pos = 1;

inline void MoveL() {
    if(pos == 1) return;
    if(min(pre[0], pre[0] - A[pos][0]) < 0 && max(pre[0], pre[0] - A[pos][0]) > 0) ans[0] --;
    if(min(pre[1], pre[1] - A[pos][1]) < 0 && max(pre[1], pre[1] - A[pos][1]) > 0) ans[1] --;
    pre[0] -= A[pos][0], pre[1] -= A[pos][1]; pos --;
    MaxX.Insert(max(0, A[pos + 1][0]) + pre[0] - delta[0]), MinX.Insert(min(0, A[pos + 1][0]) + pre[0] - delta[0]);
    MaxY.Insert(max(0, A[pos + 1][1]) + pre[1] - delta[1]), MinY.Insert(min(0, A[pos + 1][1]) + pre[1] - delta[1]);
}
inline void MoveR() {
    if(pos == n) return;
    MaxX.Delete(max(0, A[pos + 1][0]) + pre[0] - delta[0]), MinX.Delete(min(0, A[pos + 1][0]) + pre[0] - delta[0]);
    MaxY.Delete(max(0, A[pos + 1][1]) + pre[1] - delta[1]), MinY.Delete(min(0, A[pos + 1][1]) + pre[1] - delta[1]);
    if(min(pre[0], pre[0] + A[pos + 1][0]) < 0 && max(pre[0], pre[0] + A[pos + 1][0]) > 0) ans[0] ++;
    if(min(pre[1], pre[1] + A[pos + 1][1]) < 0 && max(pre[1], pre[1] + A[pos + 1][1]) > 0) ans[1] ++;
    pos ++; pre[0] += A[pos][0], pre[1] += A[pos][1];
}
inline void Modify(int x, int y) {
    if(min(pre[0], pre[0] - A[pos][0]) < 0 && max(pre[0], pre[0] - A[pos][0]) > 0) ans[0] --;
    if(min(pre[1], pre[1] - A[pos][1]) < 0 && max(pre[1], pre[1] - A[pos][1]) > 0) ans[1] --;
    pre[0] -= A[pos][0], pre[1] -= A[pos][1], delta[0] -= A[pos][0], delta[1] -= A[pos][1];
    A[pos][0] = x, A[pos][1] = y;
    pre[0] += x, pre[1] += y, delta[0] += x, delta[1] += y;
    if(min(pre[0], pre[0] - A[pos][0]) < 0 && max(pre[0], pre[0] - A[pos][0]) > 0) ans[0] ++;
    if(min(pre[1], pre[1] - A[pos][1]) < 0 && max(pre[1], pre[1] - A[pos][1]) > 0) ans[1] ++;
}
inline int Get_Ans() {
    return ans[0] + ans[1] + 2 * (n - pos) - (MinX.Ask_More(-delta[0]) + MaxX.Ask_Less(-delta[0])) - (MinY.Ask_More(-delta[1]) + MaxY.Ask_Less(-delta[1]));
}

int main() {
    ios::sync_with_stdio(false), cin.tie(0);

    cin >> n;
    for(int i = 1; i <= n; i ++)
        cin >> A[i][0] >> A[i][1];
    A[0][0] = A[0][1] = 1;

    int S[2] = {1 + A[1][0], 1 + A[1][1]};
    pre[0] = A[0][0] + A[1][0], pre[1] = A[0][1] + A[1][1], delta[0] = delta[1] = 0;
    if(1 + A[1][0] < 0) ans[0] ++;
    if(1 + A[1][1] < 0) ans[1] ++;

    for(int i = 2; i <= n; i ++) {
        MaxX.Insert(max(S[0], S[0] + A[i][0]));
        MaxY.Insert(max(S[1], S[1] + A[i][1]));
        MinX.Insert(min(S[0], S[0] + A[i][0]));
        MinY.Insert(min(S[1], S[1] + A[i][1]));
        S[0] += A[i][0], S[1] += A[i][1];
    }

    int Q; char op[2]; cin >> Q;
    while(Q --) {
        cin >> op;
        if(*op == 'B') MoveL();
        else if(*op == 'F') MoveR();
        else if(*op == 'Q') cout << Get_Ans() << '\n';
        else if(*op == 'C') {
            int x, y; cin >> x >> y;
            Modify(x, y);
        } else assert(false);
    }

    return 0;
}