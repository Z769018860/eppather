#include <cassert>
#include <cstdio>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

const int MOD = 19260817;
const int M = 100005;
std::vector<int> a[M];
int length[M];
int64_t tot = 1;
int n, m;

int64_t ex_gcd(int64_t a, int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    auto res = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return res;
}

int64_t inv(int64_t a) {
    a = (a + MOD) % MOD;
    int64_t x, y;
    ex_gcd(a, MOD, x, y);
    return x;
}


struct A {
    std::set<int> s;
    int64_t count;
    static int64_t f(int l, int r) {
        return ((int64_t) (r - l) * (r - l - 1) >> 1) % MOD;
    }
    A() = default;
    A(int n) {
        s.insert(0);
        s.insert(n + 1);
        count = f(0, n + 1);
    }
    void insert(int i) {
        auto p = s.lower_bound(i);
        auto q = prev(p);
        count = (count - f(*q, *p) + f(*q, i) + f(i, *p)) % MOD;
        s.insert(i);
    }
    void erase(int i) {
        s.erase(i);
        auto p = s.lower_bound(i);
        auto q = prev(p);
        count = (count + f(*q, *p) - f(*q, i) - f(i, *p)) % MOD;
    }
};

struct B {
    std::unordered_map<int, A> lists;
    int64_t count;
    int zero;
    B() = default;
    B(int64_t n) {
        count = n;
        zero = 0;
    }
    void multiply(int x) {
        if (x == 0) {
            ++zero;
        } else {
            count = count * x % MOD;
        }
    }
    void divide(int x) {
        if (x == 0) {
            --zero;
        } else {
            count = count * inv(x) % MOD;
        }
    }
    void insert(int i, int j) {
        if (!lists.count(i)) {
            lists[i] = A(length[i]);
        }
        divide(lists[i].count);
        lists[i].insert(j);
        multiply(lists[i].count);
    }
    void erase(int i, int j) {
        divide(lists[i].count);
        lists[i].erase(j);
        multiply(lists[i].count);
    }
    int getValue() {
        return zero == 0 ? count : 0;
    }
};

std::unordered_map<int, B> s;
int64_t answer;

void insert(int i, int j, int x) {
    if (!s.count(x)) {
        s[x] = B(tot);
    }
    answer = (answer - (tot - s[x].getValue())) % MOD;
    s[x].insert(i, j);
    answer = (answer + (tot - s[x].getValue())) % MOD;
}

void erase(int i, int j, int x) {
    answer = (answer - (tot - s[x].getValue())) % MOD;
    s[x].erase(i, j);
    answer = (answer + (tot - s[x].getValue())) % MOD;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", length + i);
        a[i].resize(length[i] + 1);
        tot = tot * (((int64_t) length[i] * (length[i] + 1) >> 1) % MOD) % MOD;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= length[i]; ++j) {
            scanf("%d", &a[i][j]);
            insert(i, j, a[i][j]);
        }
    }
    printf("%lld\n", (answer + MOD) % MOD);
    for (int i = 0; i < m; ++i) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        erase(x, y, a[x][y]);
        insert(x, y, z);
        a[x][y] = z;
        printf("%lld\n", (answer + MOD) % MOD);
    }
    return 0;
}
