
#include <iostream>
#include <cstdio>
#include <cstring>
#define Debug(x) cout << #x << "=" << x << endl
typedef long long ll;
using namespace std;

const int MAXN = 1e7 + 5;
const int N = 1e7;
typedef int arr[MAXN];

const int MOD = 311021;
int add(int a, int b) {return (a + b) % MOD;}
int sub(int a, int b) {return (a - b + MOD) % MOD;}
int mul(int a, int b) {return (ll)a *  b % MOD;}

arr p, phi, pf2, tot, pw2, dif, f, sum;
bool vis[MAXN];

void pre()
{
	phi[1] = 1;
	for (int i = 2; i <= N; i++)
	{
		if (!vis[i])
		{
			p[++p[0]] = i;
			phi[i] = i - 1;
			if (i == 2)
			{
				pf2[i] = 1;
			}
			else
			{
				tot[i] = 1;
			}
		}
		for (int j = 1; j <= p[0] && i * p[j] <= N; j++)
		{
			int k = i * p[j];
			vis[k] = true;
			if (i % p[j] == 0)
			{
				phi[k] = phi[i] * p[j];
				if (p[j] == 2)
				{
					pf2[k] = pf2[i] + 1;
					tot[k] = tot[i];
				}
				else
				{
					pf2[k] = pf2[i];
					tot[k] = tot[i];
				}
				break;
			}
			phi[k] = phi[i] * phi[p[j]];
			if (p[j] == 2)
			{
				pf2[k] = 1;
				tot[k] = tot[i];
			}
			else
			{
				tot[k] = tot[i] + 1;
			}
		}
	}
	
	pw2[0] = 1;
	for (int i = 1; i <= N; i++)
	{
		pw2[i] = mul(pw2[i - 1], 2);
	}
	
	for (int i = 1; i <= N; i++)
	{
		dif[i] = pw2[tot[i]];
		if (pf2[i] == 2)
		{
			dif[i] <<= 1;
		}
		else if (pf2[i] >= 3)
		{
			dif[i] <<= 2;
		}
		f[i] = pw2[(phi[i] - dif[i]) >> 1];
		sum[i] = add(sum[i - 1], f[i]);
	}
}

int main()
{
	pre();
	int q;
	scanf("%d", &q);
	while (q--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		printf("%d\n", sub(sum[r], sum[l - 1]));
	}
	return 0;
}