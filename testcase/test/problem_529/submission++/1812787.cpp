#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;
const int MX = 1000011;
int T, n;
char s[MX];
int main() {
    scanf("%d", &T);

    for (int t = 0; t < T; t++) {
        scanf("%s", s);
        n = strlen(s);
        int it = n - 1;
        int flg = 1;

        for (int i = 0; i < n; i++)
            flg &= (s[i] == 'V');

        while (it) {
            if (s[it] == 'V')
                --it;
            else if (it > 1 && s[it - 1] == 'V')
                it -= 2;
            else if (it > 1) {
                flg = 1;
                break;
            } else
                break;
        }

        if (flg) {
            puts("0 0");
            continue;
        }

        if (it == 0)
            printf("%d %d\n", 1, s[0] == 'N');
        else
            printf("%d %d\n", s[0] == 'V', 0);
    }

    return 0;
}