#include <bits/stdc++.h>
#define L long long
using namespace std;
int t;
L n;
int main() {
    
    
    scanf("%d", &t);

    while (t--) {
        scanf("%lld", &n);

        if (n >= 4)
            printf("Yes\n");
        else
            printf("No\n");

        if (n >= 4 && !(n & 1))
            printf("Yes\n");
        else
            printf("No\n");
    }

    return 0;
}