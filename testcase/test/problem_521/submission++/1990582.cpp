#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pii pair<int, int>
#define mp make_pair
#define db double
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

namespace IO {
void openfile() {
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
    freopen("out.out", "w", stdout);
#endif
}
void Min(int& x, int y) {
    x = (x < y) ? x : y;
}
void Max(int& x, int y) {
    x = (x > y) ? x : y;
}
int add(int x, int y) {
    return (x + y) >= mod ? (x + y - mod) : (x + y);
}
int sub(int x, int y) {
    return (x < y) ? (x + mod - y) : (x - y);
}
void Add(int& x, int y) {
    x = (x + y) >= mod ? (x + y - mod) : (x + y);
}
void Sub(int& x, int y) {
    x = (x < y) ? (x - y + mod) : (x - y);
}
int mul(int x, int y) {
    return 1ll * x * y % mod;
}
void Mul(int& x, int y) {
    x = 1ll * x * y % mod;
}
int qpow(int x, int y = mod - 2) {
    int ans = 1;
    while (y) {
        if (y & 1)
            ans = 1ll * x * ans % mod;
        x = 1ll * x * x % mod, y >>= 1;
    }
    return ans;
}
inline int read() {
    int x = 0, f = 0;
    char c = getchar();
    while (!isdigit(c))
        f |= c == '-', c = getchar();
    while (isdigit(c))
        x = x * 10 + c - '0', c = getchar();
    if (f)
        x = -x;
    return x;
}
}  
using namespace IO;

int n, a[maxn], d[maxn], cnt, ans[maxn];
vector<int> e[maxn], e2[maxn];

void topo() {
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 1; i <= n; i++)
        if (!d[i])
            q.push(i);
    cnt = 0;
    while (!q.empty()) {
        int x = q.top();
        q.pop(), ans[++cnt] = x;
        for (int v : e2[x]) {
            d[v]--;
            if (!d[v])
                q.push(v);
        }
    }
    if (cnt != n)
        return puts("-1"), void();
    for (int i = 1; i <= n; i++)
        printf("%d ", ans[i]);
}

signed main() {
    openfile();
    n = read();
    for (int i = 1; i < n; i++) {
        int x = read(), y = read();
        e[x].push_back(y), e[y].push_back(x);
        a[x]++, a[y]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (a[i] == 1)
            q.push(i);
    while (!q.empty()) {
        int x = q.front(), t = 0;
        q.pop();
        for (int v : e[x])
            if (a[v] > 0)
                t = v, a[v] = 0;
        if (!t)
            continue;
        for (int v : e[x])
            if (v ^ t)
                e2[t].push_back(v), d[v]++;
        for (int v : e[t])
            if (v ^ x)
                e2[x].push_back(v), d[v]++;
        for (int v : e[t]) {
            a[v]--;
            if (a[v] == 1)
                q.push(v);
        }
        ++cnt;
    }
    if (cnt < (n / 2) || (n & 1))
        puts("-1");
    else
        topo();
    return 0;
}
