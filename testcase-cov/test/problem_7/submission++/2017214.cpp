#include <bits/stdc++.h>

using namespace std;

constexpr int N = 3000000;
long long p, ans;

int main()
{
    ios::sync_with_stdio(false); cin.tie(nullptr);
    for (int i = 1; i <= N; ++i)
    {
        cin >> p;
        ans ^= p;
    }
    cout << ans << "\n";
    return 0;
}