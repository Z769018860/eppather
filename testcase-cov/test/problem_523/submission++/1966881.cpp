#include <bits/stdc++.h>
#define pb push_back
using namespace std;
const int N = 5e5 + 50;
int m, n, T, a[N], b[N], ver[N * 2], edge[N * 2], nxt[N * 2], head[N], tot, dfn[N], rr[N], cnt, rt[N], pre[N], R, fan[N * 2], d[N], fll[N * 2], ans, S[N][3];
bool fl[N];
vector<int> vv;
void add(int x, int y)
{
    ver[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}
void dfs(int x)
{
    for (int i = head[x], y; i; i = nxt[i])
    {
        if (!d[y = ver[i]])
            pre[y] = i, d[y] = d[x] + 1, dfs(y);
        else if (d[y] >= d[x])
        {
            int j = pre[y];
            while (j && ver[j] != x)
                vv.pb(j), j = pre[ver[fan[j]]];
            vv.pb(fan[i]);
        }
    }
}
void dfs2(int x)
{
    rt[x] = R;
    dfn[x] = ++cnt;
    for (int i = head[x], y; i; i = nxt[i])
        if (!dfn[y = ver[i]])
            dfs2(y);
    rr[x] = cnt;
}
int read()
{
    int x = 0, c;
    while (!isdigit(c = getchar()))
        ;
    while (isdigit(c))
        x = x * 10 + c - 48, c = getchar();
    return x;
}
int mx[N * 4], laz[N * 4];
void push(int x, int d)
{
    mx[x] += d;
    laz[x] += d;
}
void down(int x)
{
    if (laz[x])
        push(x << 1, laz[x]), push(x << 1 | 1, laz[x]), laz[x] = 0;
}
void change(int x, int l, int r, int ql, int qr, int d)
{
    if (l > qr || r < ql || ql > qr)
        return;
    if (l >= ql && r <= qr)
    {
        push(x, d);
        return;
    }
    int mid = (l + r) >> 1;
    down(x);
    change(x << 1, l, mid, ql, qr, d);
    change(x << 1 | 1, mid + 1, r, ql, qr, d);
    mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
}
int query(int x, int l, int r, int ql, int qr)
{
    if (l > qr || r < ql || ql > qr)
        return 0;
    if (l >= ql && r <= qr)
        return mx[x];
    int mid = (l + r) >> 1;
    down(x);
    return max(query(x << 1, l, mid, ql, qr), query(x << 1 | 1, mid + 1, r, ql, qr));
}
void change(int x, int d)
{
    int D = d - edge[x], xx = rt[ver[x]];
    edge[x] = d;
    if (fl[xx])
    {
        ans -= S[xx][0] + max(S[xx][1], S[xx][2]);
        if (fll[x] || dfn[ver[x]] > dfn[ver[fan[x]]])
            S[xx][fll[x]] += D;
        ans += S[xx][0] + max(S[xx][1], S[xx][2]);
    }
    else
    {
        ans -= query(1, 1, n, dfn[xx], rr[xx]);
        if (dfn[ver[x]] > dfn[ver[fan[x]]])
            change(1, 1, n, dfn[xx], dfn[ver[x]] - 1, D),
                change(1, 1, n, rr[ver[x]] + 1, rr[xx], D);
        else
            change(1, 1, n, dfn[ver[fan[x]]], rr[ver[fan[x]]], D);
        ans += query(1, 1, n, dfn[xx], rr[xx]);
    }
}
int main()
{
    scanf("%d%d%d", &m, &n, &T);
    for (int i = 1; i <= m; i++)
        a[i] = read();
    for (int i = 1; i <= m; i++)
        b[i] = read();
    for (int i = 1; i <= m; i++)
    {
        int x = (a[i] - b[i] + n) % n, y = (a[i] + b[i]) % n;
        if (x > y)
            swap(x, y);
        x++;
        y++;
        add(y, x);
        x ^ y ? fan[tot] = tot + 1, add(x, y), fan[tot] = tot - 1 : fan[tot] = tot;
    }
    for (int i = 1; i <= n; i++)
        if (!rt[i])
        {
            vv.clear();
            R = i;
            d[i] = 1, dfs(i);
            fl[i] = vv.size();
            if (fl[i])
            {
                for (int j = 0; j < vv.size(); j++)
                    fll[vv[j]] = 1, fll[fan[vv[j]]] = 2;
                dfs2(ver[vv[0]]);
            }
            else
                dfs2(i);
        }
    for (int i = 1; i <= tot; i++)
        change(i, read());
    cout << ans << endl;
    int q = read();
    for (int i = 1, x, y; i <= q; i++)
    {
        scanf("%d%d", &x, &y);
        x -= T * ans;
        y -= T * ans;
        change(x, y);
        printf("%d\n", ans);
    }
    return 0;
}