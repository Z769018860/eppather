#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

char S[2002000];

bool
check_same_str(const char *s, int f, int t, int b, int e)
{
    assert(f <= t);
    assert(b <= e);
    assert((t - f) == (e - b));
    int i = f;
    int j = b;
    while (i <= t && j <= e) {
        if (s[i] != s[j]) {
            return false;
        }
        i++;
        j++;
    }
    return true;
}

int
lyndon_split(const char *s)
{
    int ans = 0;
    int i = 0;
    int n = strlen(s);
    while (i < n) {
        int j = i + 1;
        int k = i;

        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) {
                k = i;
            } else {
                k++;
            }
            j++;
        }

        int start = i;
        int end = i + j - k;
        while (i <= k) {
            
            
            
            
            
            printf("%d ", i + (j - k) - 1 + 1);
            
            i += (j - k);
        }
    }
    return 0;
}

int main(void)
{
    while (scanf("%s", S) != EOF) {
        lyndon_split(S);
    }
    return 0;
}