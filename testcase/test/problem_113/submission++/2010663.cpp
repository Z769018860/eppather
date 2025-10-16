#include <iostream>

const int N = 51;

int n;
long long a[N];

void insert(long long x)
{
    for (int k = 50; k >= 0; -- k)
    {
        if (!(x & (1ll << k)))
            continue;
    
        if (!a[k])
        {
            a[k] = x;
            break;
        }

        x ^= a[k];
    }
}

int main()
{
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++ i)
    {
        long long x;
        scanf("%lld", &x);
        insert(x);
    }

    long long ans = 0;

    for (int k = 50; k >= 0; -- k)
    {
        if (ans < (ans ^ a[k]))
            ans ^= a[k];
    }

    printf("%lld\n", ans);
    
    return 0;
}