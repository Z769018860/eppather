#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 100;

int n, k, a[maxn], ans[maxn ];
char s[maxn];

int main() {
    scanf("%d%d%s", &n, &k, s + 1);

    for (int i = n, j = 0; i >= 1; --i) {
        if (s[i] == '*')
            j++;
        else
            a[j]++;
    }

    n += 30;
    for(int i=0;i<=n;++i){
        int k = (a[i] - 1) / 2;
        a[i] -= k * 2, a[i + 1] += k;
    }
    int p = k - 1;

    while (n >= 0) {
        while (n >= 0 && !a[n])
            n--;

        if (n < 0)
            break;

        if (n >= p)
            ans[p--] = 1;
        else {

            for(int i=0;i<=p-1;++i) if (a[i] >= 2)
                a[i] -= 2, a[i + 1]++;

            for(int i=0;i<=p;++i) ans[i] = a[i];
            break;
        }

        n--;
    }

    p = k - 1;

    while (p >= 0 && !ans[p])
        p--;

    if (p < 0)
        puts("0");
    else {
        for(int i=p;i>=0;--i) putchar(ans[i] + '0');
        putchar('\n');
    }

    return 0;
}