#include <stdio.h>
#define N 3000001
long long arr[N];
int main(void)
{
	size_t n, p;
	scanf("%zu %zu", &n, &p);
	printf("1\n");
	arr[1] = 1;
	for (size_t i = 2; i <= n; ++i) {
		arr[i] = p - (p / i) * arr[p % i] % p;
		printf("%lld\n", arr[i]);
	}
	return 0;
}