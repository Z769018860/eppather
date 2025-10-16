#include <cstdio>
#include <cstring>

const int N = 1e4 + 5;

inline int read()
{
    int res(0), ch(getchar()), f(1);
    while (ch < '0' || ch > '9')
    {
        f = (ch == '-') ? -1 : 1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        res = res * 10 + (ch ^ '0');
        ch = getchar();
    }
    return res * f;
}
inline int max(int x, int y) { return x < y ? y : x; }

int n, m, pre[N], ans[N];

int main()
{
    std::memset(ans, -0x3f, sizeof ans);
    n = read(), m = read();
    int i, j;
    for (i = 1; i <= n; i++)
        pre[i] = pre[i - 1] + read();
    for (i = 1; i <= n; ++i)
        for (j = i; j <= n; ++j)
            ans[j - i + 1] = max(ans[j - i + 1], pre[j] - pre[i - 1]);
    for (i = n - 1; i >= 1; i--)
        ans[i] = max(ans[i + 1], ans[i]);
    while (m--)
        printf("%d\n", ans[read()]);
    return 0;
}