#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;

const ll inf = 1e18;

int t,n;
int f[1010],pri[110],pricnt;
ll tmp[70],sum[70];

void pre()
{
	for (int i = 2;pricnt < 100;i ++)
	{
		if (!f[i]) pri[++ pricnt] = f[i] = i;
		for (register int j = 1;j <= pricnt;j ++)
		{
			if (f[i] < pri[j]) break;
			if (1ll * i * pri[j] > 600) break;
			f[i * pri[j]] = pri[j];
		}
	}
}

ll cal(int x,ll y)
{
	ll res = 0;
	int i;
	tmp[0] = sum[0] = pri[x] - 1;
	for (i = 1;tmp[i - 1] <= inf / pri[x];i ++)
	{
		tmp[i] = tmp[i - 1] * pri[x] + pri[x] - 1;
		if (tmp[i] + sum[i - 1] > inf)
		{
			i --;
			break;
		}
		sum[i] = tmp[i] + sum[i - 1];

	}
	tmp[0] = 1;
	for (int j = 1;j <= i;j ++) tmp[j] = tmp[j - 1] * pri[x] + 1;
	for (;~i;i --)
	{
		if (!i)
		{
			res = res * pri[x] + max(0ll,y);

			break;
		}
		ll dig = (y - sum[i - 1] - 1) / tmp[i] + 1;
		if (y <= sum[i - 1]) dig = 0;
		res = res * pri[x] + dig;
		y -= dig * tmp[i];

	}
	return res * pri[x];
}

int main()
{
	pre();
	scanf("%d",&t);
	while (t --)
	{
		scanf("%d",&n);
		ll ans = 1;
		for (int i = 1;i <= n;i ++)
		{
			ll x;
			scanf("%lld",&x);
			ans = max(ans,cal(i,x));

		}
		printf("%lld\n",ans);
	}
}