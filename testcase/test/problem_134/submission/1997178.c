#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include <string.h>
#define ll  long long 
ll n, m;
ll a[4100][4100];
ll b[4100][4100];
long long lowbit(long long x) {
	return x & -x;
}
void add(ll x, ll y, ll p)
{
	while (x <= n)
	{
		ll yi = y;
		while (yi <= m)
		{
			b[x][yi] += p;
			yi += lowbit(yi);
		}
		x += lowbit(x);
	}
}
ll ask(ll x, ll y)
{
	ll ans = 0;
	while (x)
	{
		ll yi = y;
		while (yi)
		{
			ans += b[x][yi];
			yi -= lowbit(yi);
		}
		x -= lowbit(x);
	}return ans;
}
void add1(ll x1, ll y1, ll x2, ll y2, ll k)
{
	add(x1, y1, k);
	add(x2 + 1, y2 + 1, k);
	add(x2 + 1, y1, -k);
	add(x1, y2 + 1, -k);
}
int main()
{
	ll i, j, x, a1, b1, c, d, k, y;
	ll flag;
	scanf("%d %d", &n, &m);
	while (scanf("%lld", &flag) != EOF)
	if (flag == 1)
	{
		scanf("%lld %lld %lld %lld %lld", &a1, &b1, &c, &d, &k);
		add1(a1, b1, c, d, k);
	}
	else if (flag == 2)
	{
		scanf("%lld %lld", &x, &y);
		printf("%lld\n",ask(x, y));
	}
	return 0;
}