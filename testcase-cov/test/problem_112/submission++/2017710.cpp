#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

const int N = 1e6 + 2;

struct Node
{
    int a, b, c;
    bool operator < (const Node &_) const
    {
        if (a != _.a) return a < _.a;
        if (b != _.b) return b < _.b;
        return c < _.c;
    }
    bool operator == (const Node &_) const
    { return a == _.a && b == _.b && c == _.c; }
} tr[N];

std::map<Node, int> cnt;

int n, m, k, c[N], f[N], ans[N];
void mdf(int x, int v)
{ for (; x <= k; x += x & -x) c[x] += v; }
int qry(int x)
{
    int res = 0;
    for (; x; x -= x & -x) res += c[x];
    return res;
}

void solve(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    std::vector<std::pair<int, std::pair<int, int>>> add, ask; 
    
    for (int i = l; i <= mid; ++ i)
        add.push_back({tr[i].b, {tr[i].c, cnt[tr[i]]}});

    for (int i = mid + 1; i <= r; ++ i)
        ask.push_back({tr[i].b, {tr[i].c, i}});

    std::sort(add.begin(), add.end());
    std::sort(ask.begin(), ask.end());

    int i = 0, j = 0;
    for (; i < ask.size(); ++ i)
    {
        for (; j < add.size() && add[j].first <= ask[i].first; ++ j)
            mdf(add[j].second.first, add[j].second.second);
        f[ask[i].second.second] += qry(ask[i].second.first);
    }
    for (int k = 0; k < j; ++ k)
        mdf(add[k].second.first, -add[k].second.second);
        
    solve(l, mid); solve(mid + 1, r);
}

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++ i)
    {
        scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
        cnt[tr[i]] ++ ;
    }
    std::sort(tr + 1, tr + n + 1);
    m = std::unique(tr + 1, tr + n + 1) - tr - 1;
    solve(1, m);
    for (int i = 1; i <= m; ++ i) ans[f[i] + cnt[tr[i]] - 1] += cnt[tr[i]];
    for (int i = 0; i < n; ++ i) printf("%d\n", ans[i]);
    return 0;
}