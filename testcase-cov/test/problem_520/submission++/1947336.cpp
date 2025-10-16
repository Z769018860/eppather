

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define sqr(x) ((x)*(x))
int const N = 1e5 + 10;
int n, w[N];
void solve() {
    cin >> n;

    for (int i = 1; i <= n; ++i)
        cin >> w[i];

    sort(w + 1, w + n + 1, greater<>());
    deque<int>q;
    q.push_back(w[1]);

    for (int i = 2; i <= n; ++i)
        if (q.front() < q.back())
            q.push_back(w[i]);
        else
            q.push_front(w[i]);

    int ans = sqr(q.front() - q.back());

    for (int i = 1; i < (int)q.size(); ++i)
        ans += sqr(q[i] - q[i - 1]);

    cout << ans << '\n';
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t = 1;

    
    while (t--)
        solve();

    cerr << "Running Time: " << (double)clock() / CLOCKS_PER_SEC << " s\n";
    return 0;
}