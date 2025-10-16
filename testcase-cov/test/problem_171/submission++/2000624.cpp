#include <iostream>

using namespace std;

const int N = 2e5 + 20;

char s[N];

int n, last = 1, idx = 1, ans[N], now[N];

struct Node
{
    int len, fa;
    int ch[26];
} node[N];

void extend(int c)
{
    int p = last, np = last = ++ idx;
    node[np].len = node[p].len + 1;
    for (; p && !node[p].ch[c]; p = node[p].fa) node[p].ch[c] = np;
    if (!p) node[np].fa = 1;
    else
    {
        int q = node[p].ch[c];
        if (node[q].len == node[p].len + 1) node[np].fa = q;
        else
        {
            int nq = ++ idx;
            node[nq] = node[q], node[nq].len = node[p].len + 1;
            node[q].fa = node[np].fa = nq;
            for (; p && node[p].ch[c] == q; p = node[p].fa) node[p].ch[c] = nq;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> s;
    for (int i = 0; s[i]; ++ i) extend(s[i] - 'a');
    fill(ans + 1, ans + idx + 1, 0x3f3f3f3f);
    for (int i = 1; i < n; ++ i)
    {
        cin >> s;
        fill(now + 1, now + idx + 1, 0);
        int p = 1, t = 0;
        for (int j = 0; s[j]; ++ j)
        {
            int tmp = s[j] - 'a';
            while (p > 1 && !node[p].ch[tmp]) p = node[p].fa, t = node[p].len;
            if (node[p].ch[tmp]) p = node[p].ch[tmp], ++ t;
            now[p] = max(now[p], t);
        }
        for (int j = 1; j <= idx; ++ j) ans[j] = min(ans[j], now[j]);
    }

    int res = 0;
    for (int i = 1; i <= idx; ++ i) res = max(res, ans[i]);
    cout << res << '\n';
    return 0;
}