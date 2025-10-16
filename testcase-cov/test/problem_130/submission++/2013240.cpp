#include <iostream>

using namespace std;
typedef long long ll;
const int N=1000005;
ll n,m,a,b,op,s[N];
ll lowbit(ll x)
{
    return x&(-x);
}
void change(ll x,ll y)
{
    while(x<=n)
    {
        s[x]+=y;
        x+=lowbit(x);
    }
}
ll query(ll x)
{
    ll a=0;
    while (x)
    {
        a+=s[x];
        x-=lowbit(x);
    }
    return a;
}
int main()
{
    cin >> n >> m;
    for (ll i=1;i<=n;i++)
    {
        cin >> a;
        change(i,a);
    }
    for (ll i=1;i<=m;i++)
    {
        cin >> op >> a >> b;
        if (op==1) change(a,b);
        else if (op==2) cout << query(b)-query(a-1) << endl;
    }
    return 0;
}