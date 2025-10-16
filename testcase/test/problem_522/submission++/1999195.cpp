
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using db = double;
using PII = pair<ll, ll>;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;

ll read()
{
    ll x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + (ch ^ '0');
        ch = getchar();
    }
    return x * f;
}

const int N = 1e6 + 10, mod = 998244353;
ll f[N];
int ch[N][2];
int stk[N], tt;
ll a[N], b[N], c[N], d[N], w[N];
int n;
int rt;

void dp(int u)
{
    if(!u) return;
    ll v = ((c[u] ^ c[rt]) + c[u] * c[rt]) % mod;
    if(u != rt) f[rt] = max(f[rt], f[u] + v);
    dp(ch[u][0]);
    dp(ch[u][1]);
}

int main()
{
    #ifdef LOCAL
        freopen("/home/crimson000/OI/in_and_out/in.in", "r", stdin);
        freopen("/home/crimson000/OI/in_and_out/out.out", "w", stdout);
    #endif

    n = read();
    for(int i = 1; i <= n; i ++ ) a[i] = read();
    for(int i = 1; i <= n; i ++ ) b[i] = read();
    for(int i = 1; i <= n; i ++ ) c[i] = read();
    for(int i = 1; i <= n; i ++ ) d[i] = i;

    sort(d + 1, d + n + 1, [](int x, int y){
        return a[x] < a[y];
    });

    for(int i = 1; i <= n; i ++ ) w[i] = a[i] + b[i];
    for(int i = 1; i <= n; i ++ )
    {
        int x = d[i];
        int l = 1, r = tt, t = 0;
        while(l <= r)
        {
            int mid = l + r >> 1;
            if(w[stk[mid]] >= a[x]) l = mid + 1, t = stk[mid];
            else r = mid - 1;
        }
        ch[x][0] = t;
        while(tt && w[stk[tt]] <= w[x]) tt --;
        stk[++ tt] = x;
    }

    tt = 0;
    for(int i = 1; i <= n; i ++ ) w[i] = a[i] - b[i];
    for(int i = n; i; i -- )
    {
        int x = d[i];
        int l = 1, r = tt, t = 0;
        while(l <= r)
        {
            int mid = l + r >> 1;
            if(w[stk[mid]] <= a[x]) l = mid + 1, t = stk[mid];
            else r = mid - 1;
        }
        ch[x][1] = t;
        while(tt && w[stk[tt]] >= w[x]) tt --;
        stk[++ tt] = x;
    }

    sort(d + 1, d + n + 1, [](int x, int y){
        return b[x] > b[y];
    });

    for(int i = 1; i <= n; i ++ )
        rt = d[i], dp(rt);

    for(int i = 1; i <= n; i ++ )
        cout << f[i] << '\n';

    return 0;
}


