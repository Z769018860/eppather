


#include <bits/stdc++.h>
#define F first
#define S second
#define pii pair<int, int>
#define ll long long
#define rep(i, s, t) for(int i=s; i<=t; ++i)
#define debug(x) cout<<#x<<":"<<x<<endl;
const int N=1000010;
using namespace std;

int n, k, c[N]; ll f[N], s[N], g[N];
int main()
{
    #ifdef Jerrywang
    freopen("E:/OI/in.txt", "r", stdin);
    #endif
    scanf("%d%d", &n, &k);
    rep(i, 1, n) scanf("%d", c+i);
    rep(i, 1, n) scanf("%lld", s+i), s[i]+=s[i-1];
    memset(g, -0x3f, sizeof f);
    ll res=0;
    rep(i, 1, n)
    {
        f[i]=max(f[i-1], g[c[i]]+s[i]);
        g[c[i]]=max(g[c[i]], f[i-1]-s[i-1]);
    }
    printf("%lld", f[n]);
    
    return 0;
}