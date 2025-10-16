#include <bits/stdc++.h>
using namespace std;
const int _ = 1e7;
int T, r, c, ls[_], rs[_], cnt[_], t, stk[_];
int ins(int p, int x, int d) {
    if (!p) {
        if (t) {
            p = stk[t--];
        } else {
            p = ++c;
        }
    }
    cnt[p]++;
    if (d != -1) {
        if (x & (1 << d)) {
            rs[p] = ins(rs[p], x, d-1);
        } else {
            ls[p] = ins(ls[p], x, d-1);
        }
    }
    return p;
}
int del(int p, int x, int d) {
    cnt[p]--;
    if (d != -1) {
        if (x & (1 << d)) {
            rs[p] = del(rs[p], x, d-1);
        } else {
            ls[p] = del(ls[p], x, d-1);
        }
    }
    if (!cnt[p]) {
        stk[++t] = p;
        p = 0;
    }
    return p;
}
int kth(int p, int x, int k, int d) {
    if (d == -1) {
        return x;
    } else {
        if (k <= cnt[ls[p]]) {
            return kth(ls[p], x, k, d-1);
        } else {
            return kth(rs[p], (x|(1<<d)), k - cnt[ls[p]], d-1);
        }
    }
}
int rnk(int p, int x, int d) {
    if (!p || d == -1) return 0;
    if (x & (1 << d)) {
        return cnt[ls[p]] + rnk(rs[p], x, d-1);
    } else {
        return rnk(ls[p], x, d-1);
    }
}
inline void I(int x) {
    r = ins(r, x, 30);
}
inline void D(int x) {
    r = del(r, x, 30);
}
inline int K(int x) {
    return kth(r, 0, x, 30);
}
inline int R(int x) {
    return rnk(r, x, 30);
}
inline int P(int x) {
    int k = R(x);
    if (k == 0) {
        return -1;
    } else {
        return K(k);
    }
}
inline int N(int x) {
    int k = R(x+1);
    if (k == cnt[r]) {
        return -1;
    } else {
        return K(k + 1);
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while (T--) {
        int o, x;
        cin >> o >> x;
        switch (o) {
            case 0: {
                I(x);
                break;
            }
            case 1: {
                D(x);
                break;
            }
            case 2: {
                cout << K(x) << endl;
                break;
            }
            case 3: {
                cout << R(x) << endl;
                break;
            }
            case 4: {
                cout << P(x) << endl;
                break;
            }
            case 5: {
                cout << N(x) << endl;
                break;
            }
        }
    }
}