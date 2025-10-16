
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <string>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define pb push_back
#define el << '\n'
#define spe << ' '
#define sp spe <<
#define umap unordered_map
#define uset unordered_set
#define prqu priority_queue
#define gt(type) type, vector<type>, greater<type>
#define forr(i, j, n) for (int i = j; i < n; i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define for1(i, n) for (int i = 1; i <= n; i++)
#define forb(i, j, n) for (int i = n - 1; i >= j; i--)
#define forB(i, n) for (int i = n - 1; i >= 0; i--)
#define foro(i, n) for (i = n; i > 0; i--)
#define rety cout << "YES\n"; return 0;
#define retn cout << "NO\n"; return 0;
#define conty cout << "YES\n"; continue;
#define contn cout << "NO\n"; continue;
#define all(x) x.begin(), x.end()
#define mp make_pair
#define pb push_back
#define fs first
#define sc second
const ll IMX = 2e9 + 5, LMX = 4e18 + 10, MOD = 1e9 + 7, MOD2 = 998244353;

const int MAXN = 1e6 + 2;

int a[MAXN], kx[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    

    int t, n, k, cnt = 0;
    cin >> t >> n >> k;

    for (int i = 0, e; i < n; i++) {
        cin >> e;
        if (e % k == 0) {
            a[i] = 1;
            kx[cnt++] = i;
        }
    }

    if (cnt < 2 * k || kx[0] != 0 || kx[cnt - 1] != n - 1 || n % k != 0 || n < (ll)k * k) {
        cout << "No\n";
        return 0;
    }

    for (int i = k; i + k < cnt; i++) a[kx[i]] = 0;

    int idx = 0;
    bool valid = 1;
    for (int i = 0; i < k && valid; i++) {
        int l = kx[i], r = kx[cnt - k + i], num = 2;
        while ((idx < kx[i + 1] || num % k != 0) && idx < r) {
            if (a[idx] == 0) num++;
            idx++;
        }
        if (num % k != 0) valid = 0;
    }

    if (valid) {
        cout << "Yes\n" << k << endl;
        idx = 0;
        for (int i = 0; i < k; i++) {
            vector<int> cur;
            int l = kx[i], r = kx[cnt - k + i], num = 2;
            while ((idx < kx[i + 1] || num % k != 0 || i + 1 == k) && idx < r) {
                if (a[idx] == 0) {
                    num++;
                    cur.pb(idx);
                }
                idx++;
            }
            cout << num << ' ' << l + 1 << ' ';
            for (int i = 0; i < num - 2; i++) cout << cur[i] + 1 << ' ';
            cout << r + 1 << endl;
        }
        return 0;
    }

    idx = kx[1];
    valid = 1;
    int num = idx + n - kx[cnt - 2] - 1;
    while (num % k != 0 && idx < kx[cnt - 2]) {
        if (a[idx] == 0) num++;
        idx++;
    }
    int bidx = idx;
    if (num % k != 0) valid = 0;
    for (int i = 1; i < k && valid; i++) {
        int l = kx[i], r = kx[cnt - k + i - 1], num = 2;
        while ((idx < kx[i + 1] || num % k != 0) && idx < r) {
            if (a[idx] == 0) num++;
            idx++;
        }
        if (num % k != 0 || r < idx) valid = 0;
    }

    if (valid) {
        cout << "Yes\n" << k << endl;
        idx = bidx;
        for (int i = 1; i < k; i++) {
            vector<int> cur;
            int l = kx[i], r = kx[cnt - k + i - 1], num = 2;
            while ((idx < kx[i + 1] || num % k != 0) && idx < r) {
                if (a[idx] == 0) {
                    num++;
                    cur.pb(idx);
                }
                idx++;
            }
            cout << num << ' ' << l + 1 << ' ';
            for (int i = 0; i < num - 2; i++) cout << cur[i] + 1 << ' ';
            cout << r + 1 << endl;
        }
        {
            idx = 1;
            vector<int> cur(1, 1);
            while (idx < kx[1]) {
                idx++;
                cur.pb(idx);
            }
            for (int i = n - 2; a[i] == 0; i--) {
                cur.pb(i + 1);
            }
            num = idx + n - kx[cnt - 2] - 1;
            while (num % k != 0 && idx < kx[cnt - 2]) {
                if (a[idx] == 0) {
                    num++;
                    cur.pb(idx + 1);
                }
                idx++;
            }
            sort(all(cur));
            cout << cur.size() + 1 << ' ';
            for (int i = 0; i < cur.size(); i++) cout << cur[i] << ' ';
            cout << n << endl;
        }
        return 0;
    }

    cout << "No\n";
    return 0;
}
