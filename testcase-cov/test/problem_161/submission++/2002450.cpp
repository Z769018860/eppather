#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;
typedef long long ll;
#define endl '\n'
const int mod=1e9+7;
const int N = 5e6 + 5;
const ll llmax=0x3f3f3f3f3f3f3f3f;
ll mo[N],preji[N],preni[N];
ll modp = 998244353;
ll p=mod;
ll qmi(ll m, ll k, ll p)
{
    ll res = 1 % p, t = m;
    while (k)
    {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}
void slove()
{
	int n;
    cin >> n;
    ll a[n + 5];
    preji[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        preji[i] = preji[i - 1] * a[i]%p;
        
    }

    preni[n] = qmi(preji[n], p - 2, p);
    for (int i = n; i >= 2; i--)
    {
        preni[i - 1] = preni[i] * a[i] % p;
    }

    mo[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        mo[i] = mo[i-1]*modp%p;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++)
    {
        ans += preni[i] * preji[i - 1]%p * mo[n-i]%p;
        ans %= p;
    }
    cout << ans%p << endl;
    
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	int t=1;
	
	while(t--){
		
		slove();	
	}
	return 0;
}





