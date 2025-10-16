#include <bits/stdc++.h>
using namespace std;
typedef unsigned ui;
const ui SS = 5, S = 32, B = 1 << 16, P = B - 1, G = 258;
const ui DS = 8, D = 1 << 8;
namespace sqrlog {
    ui qwq[32][32];
    ui mul(ui, ui);
    ui g(ui x, ui y) {
        if (x == 0 || y == 0) return 1 << (x + y);
        if (qwq[x][y]) return qwq[x][y];
        ui a = x ^ y, b = x & y, ans = 1;
        for (int i = 0; i < SS; i++) if ((a >> i) & 1) ans <<= 1 << i;
        for (int i = 0; i < SS; i++) if ((b >> i) & 1) ans = mul(ans, 3 << ((1 << i) - 1));
        return qwq[x][y] = ans;
    }
    ui mul(ui a, ui b) {
        if (a == 0 || b == 0) return 0;
        if (a == 1 || b == 1) return a * b;
        ui ans = 0;
        for (int i = 0; i < S; i++) if ((a >> i) & 1)
            for (int j = 0; j < S; j++) if ((b >> j) & 1) ans ^= g(i, j);
        return ans;
    }
}
namespace table {
    ui qwq[D][D];
    ui f(ui x, ui y, int m) {
        if (x < D && y < D && qwq[x][y]) return qwq[x][y];
        if (x == 0 || y == 0) return 0;
        if (m == 0) return 1;
        int n = 1 << (m - 1), P = (1 << n) - 1;
        ui a = x >> n, b = x & P, c = y >> n, d = y & P;
        ui tmp = f(b, d, m - 1);
        ui ans = f(f(a, c, m - 1), 1 << (n - 1), m - 1) ^ ((f(a ^ b, c ^ d, m - 1) ^ tmp) << n) ^ tmp;
        if (x < D && y < D) qwq[x][y] = ans;
        return ans;
    }
    ui ln[B], pw[B * 2];
    void init() {
        for (ui i = 0, cur = 1; i < P; i++, cur = f(cur, G, 4)) ln[pw[i] = cur] = i;
        for (int i = P; i < 2 * P; i++) pw[i] = pw[i - P];
    }
    inline ui get(ui a, ui b) {
        return a == 0 || b == 0 ? 0 : pw[ln[a] + ln[b]];
    }
    ui mul(ui x, ui y) {
        ui a = x >> 16, b = x & P, c = y >> 16, d = y & P;
        ui tmp = get(b, d);
        ui ans = get(get(a, c), 1 << 15) ^ ((get(a ^ b, c ^ d) ^ tmp) << 16) ^ tmp;
        if (x < D && y < D) qwq[x][y] = ans;
        return ans;
    }
}
ui SA, SB, SC;
ui rng() {
    SA ^= SA << 16;
    SA ^= SA >> 5;
    SA ^= SA << 1;
    ui t = SA;
    SA = SB;
    SB = SC;
    SC ^= t ^ SA;
    return SC;
}
int main() {
    table :: init();
    int T;
    cin >> T >> SA >> SB >> SC;
    ui lst = 0;
    while (T--) {
        ui x = rng() + lst;
        ui y = rng();
        lst = table :: mul(x, y);
    }
    cout << lst << endl;
}