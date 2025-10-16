#include <bits/stdc++.h>
using namespace std;
long long b[100], sum = 1LL, cnt = 0LL;
bool tmp = false;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    while (n--) {
        long long a;
        cin >> a;
        for (long long i = 60LL; i >= 0LL; i--) {
            if (a & (1LL << i)) {
                if (b[i]) {
                    (a ^= b[i]);
                } else {
                    b[i] = a;
                    cnt++;
                    (sum <<= 1LL);
                    break;
                }
            }
            if (i == 0LL) {
                tmp = true;
            }
        }
    }
    int m;
    cin >> m;
    while (m--) {
        long long k;
        cin >> k;
        if (tmp) {
            k--;
        }
        if (k >= sum) {
            cout << -1;
        } else {
            long long a = 0LL;
            long long c = cnt;
            for (long long i = 60LL; i >= 0LL; i--) {
                if (b[i]) {
                    if ((!(!(k & (1LL << (c - 1))))) ^ (!(!(a & (1LL << i))))) {
                        (a ^= b[i]);
                    }
                    c--;
                }
            }
            cout << a;
        }
        if (m) cout << '\n';
    }
    cout << endl;
    return 0;
}