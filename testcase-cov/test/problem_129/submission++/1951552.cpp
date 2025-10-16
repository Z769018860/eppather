#include <bits/stdc++.h>

using namespace std;

char S[(1<<20) + 10];

int
lyndon_split(const char *s)
{
    int i = 0;
    int ans = 0;

    while (s[i]) {
        int k = i;
        int j = i + 1;
        while (s[j] && s[k] <= s[j]) {
            if (s[k] < s[j]) {
                k = i;
            } else {
                k++;
            }
            j++;
        }

        while (i <= k) {
            printf("%d ", i + (j - k));
            i += j - k;
        }
    }

    return 0;
}

int main()
{
    while (scanf("%s", S) != EOF) {
        lyndon_split(S);
    }
    return 0;
}