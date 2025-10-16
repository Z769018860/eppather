#include <bits/stdc++.h>
using namespace std;
random_device qwq;
mt19937 rnd(qwq());
int mod, x;
struct node {
    int s[3];
    inline node operator * (const node &b) const {
        node ans{0, 0, 0};

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                if (i + j >= 3)
                    ans.s[i + j - 3] = (ans.s[i + j - 3] + 1ll * s[i] * b.s[j] % mod * x) % mod;
                else
                    ans.s[i + j] = (ans.s[i + j] + 1ll * s[i] * b.s[j]) % mod;
            }

        return ans;
    }
};
inline int power(int a, int b) {
    long long res = a, ans = 1;

    for (; b; b >>= 1, res = res * res % mod)
        if (b & 1)
            ans = ans * res % mod;

    return ans;
};
inline node power(node res, int b) {
    node ans = {1, 0, 0};

    for (; b; b >>= 1, res = res * res)
        if (b & 1)
            ans = ans * res;

    return ans;
}
inline int m3rt(int x, int mod) {
    ::x = x, ::mod = mod;

    if (x == 0 || x == 1 || mod == 3)
        return x;

    if (mod % 3 == 2)
        return power(x, mod / 3 * 2 + 1);

    int b = mod / 3;

    if (power(x, b) != 1)
        return 0;

    while (1) {
        node cur = power(node{rnd() % mod, rnd() % mod, rnd() % mod}, b);

        if (cur.s[0] == 0 && cur.s[2] == 0 && cur.s[1] != 0)
            return power(cur.s[1], mod - 2);
    }
}
int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, mod;
        scanf("%d%d", &n, &mod);
        printf("%d\n", m3rt(n, mod));
    }
}