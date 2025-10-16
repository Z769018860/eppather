#include <cstdio>
using namespace std;
int t;
long long n, m, a, b, x, y, k;
int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%lld%lld%lld", &n, &m, &k);
        a = n >> 1;
        b = m >> 1;
        x = n - a;
        y = m - b;
        printf("%lld\n", a * y * (b + x) + b * x * (a + y));
    }

    return 0;
}