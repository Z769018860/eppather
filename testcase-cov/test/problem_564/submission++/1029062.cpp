#include <bits/stdc++.h>
#define MP std::make_pair
#define PB push_back
#define FI first
#define SE second
typedef long long ll;
const int max_N = 105;
typedef std::pair <int, int> pii;
int n;
bool flag[max_N][max_N][max_N];
int read() {
    char c = getchar();
    int ans = 0;

    while (c < '0' || c > '9')
        c = getchar();

    while (c >= '0' && c <= '9')
        ans = ans * 10 + c - '0', c = getchar();

    return ans;
}
void Write(int x) {
    if (x < 10)
        putchar(x + '0');
    else
        Write(x / 10), putchar(x % 10 + '0');
}
void output(int x, int y, int z) {
    Write(x), putchar(' '), Write(y), putchar(' '), Write(z), putchar('\n');
}
int main() {
    n = read(), Write((n * n + 1) / 2), putchar('\n');

    for (int i = 1; i <= n / 2; i++)
        for (int j = 1; j <= n / 2; j++)
            output(i, j, j + i - (j + i > n / 2) * (n / 2));

    for (int i = n / 2 + 1; i <= n; i++)
        for (int j = n / 2 + 1; j <= n; j++)
            output(i, j, j + i - n / 2 - (j + i - n / 2 > n) * ((n + 1) / 2));

    return 0;
}