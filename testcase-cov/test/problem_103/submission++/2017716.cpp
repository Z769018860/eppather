#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <cstring>

using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using db = double;
using ld = long double;
using pii = std::pair<int, int>;

constexpr int N = 1000000 + 10;

char s[N], t[N];
int nxt[N];

int KMP(char *s, char *t) {
    int res = 0;

    nxt[0] = -1;
    int n = strlen(s + 1), m = strlen(t + 1);

    for (int i = 1, j = -1; i <= m; i++) {
        while (j != -1 && t[j + 1] != t[i]) {
            j = nxt[j];
        }
        nxt[i] = ++j;
    }

    for (int i = 1, j = 0; i <= n; i++) {
        while (j != -1 && s[i] != t[j + 1]) {
            j = nxt[j];
        }
        ++j;
        if (j == m) {
            res += 1;
        }
    }

    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> (s + 1) >> (t + 1);
    std::cout << KMP(s, t);

    return 0;
}
