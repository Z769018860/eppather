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

int
lyndon_split(const char *s)
{
    int ans = 0;
    int i = 0;
    while (s[i]) {
        int j = i + 1;
        int k = i;

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