#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=3e6+10;
ll a[N],n,p;

void solve()
{
    a[1]=1;
    for (int i=2;i<=n;++i)
    {
        a[i]=((p-p/i)*a[p%i])%p;
    }
}

int main()
{
    cin>>n>>p;
    solve();
    for (int i=1;i<=n;++i)
        cout<<a[i]<<"\n";
    return 0;
}