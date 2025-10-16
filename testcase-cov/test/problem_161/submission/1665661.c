#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define M 998244353
#define P 1000000007
long long int quickpow(long long int x, long long int b, long long int mod);
long long int inv[5000001],sv[5000001],a[5000001],s[5000001];
int main()
{
    int n,t;
    scanf("%d",&n);
    t=n;
    for (int i = 1; i <= n; ++i)
        scanf("%lld",&a[i]);
   s[0] = 1;
for (int i = 1; i <= n; ++i) s[i] = s[i - 1] * a[i] % P;
sv[n] = quickpow(s[n], P - 2,P);
for (int i = n-1; i >= 1; --i) sv[i ] = sv[i+1] * a[i+1] % P;
for (int i = 1; i <= n; ++i) inv[i] = sv[i] * s[i - 1] % P;
	long long int c=0;
	for(int i=1;i<=n;i++)
		c=(c*M%P+inv[i])%P;
	printf("%lld\n",c);
	return 0;
} 
long long int quickpow(long long int x, long long int b, long long int mod){
if(b == 0) return 1;
if(b == 1) return x % mod;
long long int tmp = quickpow(x, b / 2, mod);
tmp = tmp * tmp % mod;
if(b % 2 == 0) return tmp;
else return tmp * x % mod;
}