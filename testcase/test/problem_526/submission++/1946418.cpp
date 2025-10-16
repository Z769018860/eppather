#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
#define endl '\n'
#define db double
#define pb push_back

typedef long long ll;
typedef pair<int,int> PII;

const int N = 510, M = 1e5 + 10;

int n, m;
ll a[N];
ll e[M], ne[M];
int h[M], idx;
int match[M];
bool st[M];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

bool find(int u)
{
    for (int i = h[u]; ~i; i = ne[i])
    {
        int j = e[i];
        if (!st[j])
        {
            st[j] = true;
            if (match[j] == 0 || find(match[j]))
            {
                match[j] = u;
                return true;
            }
        }
    }
    return false;
}

void solve()    
{
    memset(h, -1, sizeof h);
    cin >> n;
    for (int i = 1; i <= n; i ++ ) cin >> a[i];

    for (int i = 1; i <= n; i ++ )
    {
        if (a[i] & 1) continue;
        for (int j = 1; j <= n; j ++ )
        {
            if (!(a[j] & 1)) continue;
            if (__gcd(a[i], a[j]) * __gcd(a[i] + 1, a[j] + 1) == 1)
                add(i, j);
        }
    }

    int cnt = 0;
    for (int i = 1; i <= n; i ++ )
    {
        memset(st, false, sizeof st);
        if (find(i)) cnt ++ ;
    }

    cout << n - cnt << endl;
}

int main()  
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    
    
    solve();

    return 0;
}
