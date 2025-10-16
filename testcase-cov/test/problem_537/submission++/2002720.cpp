#include<bits/stdc++.h>
using namespace std;
const int mod = 1e6 + 7;
const int base = 233;
const int N = 5e6 + 5;
char s[N];
int is_fixed[mod + 5];
int mx,n,k;
signed main()
{
	scanf("%s",s + 1);
	n = strlen(s + 1); 
	scanf("%d",&k);
	for(int i = 1;i <= n - k + 1;i++)
	{
		long long x = 0;
		for(int j = i;j <= i + k - 1;j++) x = (x * base + s[j]) % mod;
		is_fixed[x]++;
		mx = max(mx,is_fixed[x]);
	}
	printf("%d ",mx);
	return 0;
}