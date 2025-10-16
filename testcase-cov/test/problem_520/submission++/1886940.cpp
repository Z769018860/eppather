#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
template <typename T> inline void read(T &x) {
    static char c = getchar();
    bool f = 0;
    x = 0;

    for (; c > 57 || c < 48; c = getchar())
        f |= c == '-';

    for (; c >= 48 && c <= 57; c = getchar())
        x = (x << 1) + (x << 3) + (c ^ 48);

    if (f)
        x = -x;
}
template <typename T, typename ...Args> inline void read(T &x, Args &...args) {
    read(x), read(args...);
}

const int N = 2e5 + 5;
int n;
ll w[N], ans;

signed main() {
    
    

    read(n);

    for (int i = 1; i <= n; i++)
        read(w[i]);

    if (n == 2) {
    	cout << (w[1] - w[2]) * (w[1] - w[2]) * 2;
        return 0;
    }

    sort(w + 1, w + 1 + n);

    for (int i = 1; i < n; i += 2)
        ans += (w[i] - w[min(i + 2, n)]) * (w[i] - w[min(i + 2, n)]);

    for (int i = 2; i < n; i += 2)
        ans += (w[i] - w[min(i + 2, n)]) * (w[i] - w[min(i + 2, n)]);

    ans += (w[1] - w[2]) * (w[1] - w[2]);

    cout << ans << "\n";

    return 0;
}
