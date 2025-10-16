#include<bits/stdc++.h>
using namespace std;
int t;
long long n;
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld",&n);
        puts(n>=4?"Yes":"No");
        puts(n>=4 && !(n&1)?"Yes":"No");
    }
    return 0;
}