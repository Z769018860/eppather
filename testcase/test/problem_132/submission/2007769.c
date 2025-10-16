#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include <string.h>
#define ll long long
ll tree[10000005];
ll mark[10000005];
ll a[1000001];
void bulid(ll l, ll r, ll p)
{
	if (l == r)
	{
		tree[p] = a[l];
	}
	else {
		ll mid = (l + r) / 2;
		bulid(l, mid, p * 2);
		bulid(mid + 1, r, p * 2 + 1);
		tree[p] = tree[2 * p] + tree[2 * p + 1];
	}
}
ll n, q;
void updown(ll l, ll r, ll d, ll p, ll cl, ll cr)
{
	if (cl > r || cr < l)
		return;
	else if (cl >= l && cr <= r)
	{
		tree[p] += (cr - cl + 1) * d;
		if (cr > cl)
		{
			mark[p] += d;
		}
	}
	else {
		ll mid = (cr + cl) / 2;
		mark[2 * p] += mark[p];
		mark[2 * p + 1] += mark[p];
		tree[2 * p] += mark[p] * (mid - cl + 1);
		tree[2 * p + 1] += mark[p] * (cr - mid);
		mark[p] = 0;
		updown(l, r, d, 2 * p, cl, mid);
		updown(l, r, d, 2 * p + 1, mid + 1, cr);
		tree[p] = tree[p * 2] + tree[p * 2 + 1];
	}
}
ll find(ll l, ll r, ll p, ll cl, ll cr)
{
	if (l > cr || r < cl)
	{
		return 0;
	}
	else if (cl >= l && cr <= r)
	{
		return tree[p];
	}
	else {
		ll mid = (cr + cl) / 2;
		mark[2 * p] += mark[p];
		mark[2 * p + 1] += mark[p];
		tree[2 * p] += mark[p] * (mid - cl + 1);
		tree[2 * p + 1] += mark[p] * (cr - mid);
		mark[p] = 0;
		ll ans1 = find(l, r, p * 2, cl, mid);
		ll ans2 = find(l, r, p * 2 + 1, mid + 1, cr);
		ll ans = ans1 + ans2;
		return ans;
	}
}
int main()
{
	int t;
	int fl;
	int I, v, J;
	scanf("%lld %lld", &n, &q);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", a + i);
	}
	bulid(1, n, 1);
	while (q--)
	{
		scanf("%d", &fl);
		if (fl == 1)
		{
			scanf("%d %d %d", &I, &J, &v);
			updown(I, J, v, 1, 1, n);
		}
		else {
			scanf("%d %d", &I, &J);
			printf("%lld\n", find(I, J, 1, 1, n));
		}
	}
	return 0;
}