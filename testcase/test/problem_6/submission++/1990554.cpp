#include <bits/stdc++.h>
using uint = unsigned int;
using namespace std;
constexpr char GE[] = "get_num", GU[] = "guess", SU[] = "submit";
constexpr uint lim = 1000000;
uint n, ans[105];
bool fail(uint i, uint x) {
    static uint ret;
    cout << GU << ' ' << i - 1 << ' ' << x << endl;
    cin >> ret;
    return ret == 1;
}
int main() {

    cout << GE << endl;
    cin >> n;

    for (uint i = 1; i <= n; i++) {
        uint l = 0, r = lim;

        while (l <= r) {
            uint mid = (l + r) / 2;

            if (fail(i, mid))
                r = mid - 1;
            else
                ans[i] = mid, l = mid + 1;
        }
    }

    cout << SU;

    for (uint i = 1; i <= n; i++)
        cout << ' ' << ans[i];

    cout << endl;
    return 0;
}