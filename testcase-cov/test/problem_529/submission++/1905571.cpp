#include <bits/stdc++.h>
using namespace std;
bitset<2> check(const char* str) {
    for (auto s = str+1; *s; s++) {
        if (*s == 'N' && *(s-1) == 'N') return {0};
    }
    bool flag = false;
    for (auto s = str; *s; s++) flag |= *s == 'N';
    if (!flag) return {0};
    if (str[0] == 'V') return {1};
    else return {3};
}
char s[1000010];
int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        auto ans = check(s);
        printf("%d %d\n", (int)ans[0], (int)ans[1]);
    }
}
