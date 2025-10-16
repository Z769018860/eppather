#include <cstdio>
#include <algorithm>
#include <vector>
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)

int T;
long long n;

int main()
{
#ifndef ONLINE_JUDGE
	file(cpp);
#endif
	for (std::scanf("%d", &T); T--; )
	{
		std::scanf("%lld", &n);
		puts(n >= 4 ? "Yes" : "No");
		puts(n >= 4 && !(n & 1) ? "Yes" : "No");
	}
	return 0;
}
