#include<bits/stdc++.h>
#define LL long long
#define DB double
#define MOD 1000000007
#define ls(x) x << 1
#define rs(x) x << 1 | 1
#define lowbit(x) x & (-x)
#define PII pair<int, int>
#define MP make_pair
#define VI vector<int>
#define VII vector<int>::iterator
#define EB emplace_back
#define SI set<int>
#define SII set<int>::iterator
#define QI queue<int>
using namespace std;
template<typename T> void chkmn(T &a, const T &b) { (a > b) && (a = b); }
template<typename T> void chkmx(T &a, const T &b) { (a < b) && (a = b); }
int inc(const int &a, const int &b) { return a + b >= MOD ? a + b - MOD : a + b; }
int dec(const int &a, const int &b) { return a - b < 0 ? a - b + MOD : a - b; }
int mul(const int &a, const int &b) { return 1LL * a * b % MOD; }
void Inc(int &a, const int &b) { ((a += b) >= MOD) && (a -= MOD); }
void Dec(int &a, const int &b) { ((a -= b) < 0) && (a += MOD); }
void Mul(int &a, const int &b) { a = 1LL * a * b % MOD; }
void Sqr(int &a) { a = 1LL * a * a % MOD; }
int qwqmi(int x, int k = MOD - 2)
{
	int res = 1;
	while(k)
	{
		if(k & 1) Mul(res, x);
		Sqr(x), k >>= 1;
	}
	return res;
}
int T;
LL n, m, k;
void work()
{
	scanf("%lld %lld %lld", &n, &m, &k);
	LL w1 = n * (m / 2) * (m / 2);
	LL w2 = m * (n / 2) * (n / 2);
	if(m & 1) w1 += n * (m / 2);
	if(n & 1) w2 += m * (n / 2);
	printf("%lld\n", w1 + w2);
}
int main()
{
	scanf("%d", &T);
	while(T--)
		work();
	return 0;
}