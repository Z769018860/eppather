#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long LL;
LL k, n, all, cnt;
int ans[50];
bool flag;

void dfs(LL now, int t) {
    if (flag) return;
    if (now == 1) {
        cout << n + all + 1 << endl;
        cout << "2 ";
        for (int i = 1; i <= n; i ++ ) cout << "1 ";
        for (int i = 1; i <= cnt; i ++ ) {
            int t = (i & 1 ? 0 : 1);
            for (int j = 1; j <= ans[i]; j ++ ) cout << t << " ";
        }
        flag = true;
        return;
    }
    for (int i = t; i < 60; i ++ ) {
        LL p = (1ll << i) - 1;
        if (now % p) continue;
        ans[ ++ cnt] = i, all += i;
        dfs(now / p, i);
        all -= i, cnt --;
    }
}

int main() {
    cin >> k;
    while (k % 2 == 0)
        k /= 2, n ++;
    if (k == 1) {
        cout << n + 2 << '\n' << "2 ";
        for (int i = 1; i <= n; i ++ ) cout << "1 ";
        cout << "0\n";
    }
    else {
        dfs(k, 2);
        if (!flag) puts("qnq");
    }
    return 0;
}