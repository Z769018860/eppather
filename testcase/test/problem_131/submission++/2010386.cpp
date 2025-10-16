#include <iostream>
using namespace std;

const int maxn = 1e6 + 10;
int n;
long long diff[maxn], diff_i[maxn];

void add0(int pos, long long val) {
    long long val2 = val * pos;
    while (pos <= n) {
        diff[pos] += val;
        diff_i[pos] += val2;
        pos += pos & -pos;
    }
}

long long query0(const long long *c, int pos) {
    long long ans = 0;
    while (pos) {
        ans += c[pos];
        pos -= pos & -pos;
    }
    return ans;
}

void add(int l, int r, long long val) {
    add0(l, val);
    add0(r + 1, -val);
}

long long query(int l, int r) {
    return query0(diff, r) * (r + 1) - query0(diff_i, r) -
            query0(diff, l - 1) * l + query0(diff_i, l - 1);
}

int main() {
    int q, tmp;
    cin >> n >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> tmp;
        add(i, i, tmp);
    }
    while (q--) {
        int op, a, b, c;
        cin >> op;
        if (op == 1) {
            cin >> a >> b >> c;
            add(a, b, c);
        } else {
            cin >> a;
            cout << query(a, a) << endl;
        }
    }
    return 0;
}