typedef long long ll;const ll mod = 998244353,inv2 = 499122177,inv6 = 166374059;ll n,s1,s2,s3;ll calc(ll n){return n*(n+1)%mod*(2*n+1)%mod*inv6%mod;}
int main() {
	scanf("%lld", &n);
	for (ll i = 1, j; i <= n; i = j + 1) {
		j = n / (n / i);
		s1 = (s1 + (calc(j) - calc(i - 1) + mod) % mod * (n / i) % mod) % mod;
		s2 = (s2 + (i + j) * (j - i + 1) % mod * inv2 % mod * (n / i) % mod) % mod;
		s3 = (s3 + (j - i + 1) * (n / i)) % mod;
	}
	printf("%lld", (2 * s1 + 3 * s2 + 5 * s3) % mod);
    return 0;
}