#include <iostream>
#define MAXN 4100 
using namespace std;

long long bit[MAXN][MAXN]; 
int n, m;

int lowbit(int x) {
    return x & -x;
}

void update(int x, int y, int val) {
    for(int i = x; i <= n; i += lowbit(i))
        for(int j = y; j <= m; j += lowbit(j))
            bit[i][j] += val;
}

long long sum(int x, int y) {
    long long ret = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        for(int j = y; j > 0; j -= lowbit(j))
            ret += bit[i][j];
    return ret;
}

long long query(int x1, int y1, int x2, int y2) {
    return sum(x2, y2) - sum(x2, y1-1) - sum(x1-1, y2) + sum(x1-1, y1-1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    int z, x, y, x1, y1, x2, y2, val;
    while(cin >> z) {
        if(z == 1) {
            cin >> x >> y >> val;
            update(x, y, val);
        } else if(z == 2) {
            cin >> x1 >> y1 >> x2 >> y2;
            cout << query(x1, y1, x2, y2) << '\n';
        }
    }

    return 0;
}
