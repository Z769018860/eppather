#include<cstdio>
int main()
{
    freopen("copycat.in", "r", stdin), freopen("copycat.out", "w", stdout);
    long long t;
    char s[1001];
    scanf("%lld", &t);
    while (t--)
    {
        scanf("%s", s);
        printf("%s\n", s);
    }
    return 0;
}