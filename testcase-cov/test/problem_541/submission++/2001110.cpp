#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

const int N = 1e6 + 10, mod = 998244353;
int n, Type;
int p[N], que[N];
bool st[N * 2], vis[N * 2];
queue<int> q, q1;

unsigned int rando(unsigned int &seed) {
    seed ^= (seed << 13);
    seed ^= (seed >> 17);
    seed ^= (seed << 5);
    return seed;
}

void clear() {
    while (q.size()) q.pop();
    while (q1.size()) q1.pop();
}

void getin() {
    unsigned int seed;
    int X1, X2, Mod;
    scanf("%d%u%d%d%d%d", &n, &seed, &X1, &X2, &Mod, &Type);
    clear();
    for (int i = 1; i <= n; i ++ ) {
        if (rando(seed) % Mod == 0) p[i] = -1;
        else p[i] = rando(seed) % X2;
    }
    
    for (int i = 0; i <= max(X1, X2) + 10; i ++ ) st[i] = vis[i] = (i <= X1);
    for (int i = X1 + 1; i <= max(X1, X2) + 10; i ++ ) q.push(i);
}



int do3(int &hh, int tt) {
    if (!q1.size()) return -1;
    int t = q1.front(); q1.pop();
    if (hh <= tt && que[hh] == t) hh ++;
    st[t] = true;
    return 0;
}

void getans(int &res, int i, int hh, int tt) {
    while (q.size() && st[q.front()]) q.pop();
    int ans = q.front();
    if (hh <= tt) ans = min(ans, que[hh]);
    ans = 1ll * (1ll * i * i % mod + 7ll * i % mod) % mod * ans % mod;
    res ^= ans;
}

void solve() {
    getin();
    int hh = 0, tt = -1, res = 0;
    for (int i = 1; i <= n; i ++ ) {
        if (p[i] == -1) {
            if (Type) continue;
            int x = do3(hh, tt);
            if (x == -1) continue;
        }
        else if (!vis[p[i]]) vis[p[i]] = st[p[i]] = 1;
        else if (st[p[i]]) {
            if (Type) continue;
            st[p[i]] = false;
            while (hh <= tt && que[tt] >= p[i]) tt --;
            que[ ++ tt] = p[i];
            q1.push(p[i]);
        }
        else {
            if (Type) continue;
            int x = do3(hh, tt);
            if (x == -1) continue;
        }
        getans(res, i, hh, tt);
    }
    printf("%d\n", res);
    return;
}

int main() {
    int T;
    cin >> T;
    while (T -- ) solve();
    return 0;
}