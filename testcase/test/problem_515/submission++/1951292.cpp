#include <cstdio>
#include <bitset>

typedef long long ll;

const int MAX = 1e6 + 5;
const int N = 105;

int n, a[N], b[N];
std::bitset < MAX > dp[N];

int main()
{
	scanf("%d", &n);
	int i, j, k;
	for (i = 1; i <= n; i++)
		scanf("%d %d", &a[i], &b[i]);
	dp[0][0] = 1;
	for (i = 1; i <= n; i++)
		for (j = a[i]; j <= b[i]; j++)
			dp[i] |= (dp[i - 1] << (j * j));
	printf("%d\n", dp[n].count());
	return 0;
}