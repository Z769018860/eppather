#include <bits/stdc++.h>
using namespace std;
#define int long long
int read()
{
	int d = 0, w = 1;
	char ch = getchar();
	while (ch != '-' && (ch < '0' || ch > '9'))
		ch = getchar();
	if (ch == '-')
		w = -1, ch = getchar();
	while (ch >= '0' && ch <= '9')
		d = d * 10 + ch - '0', ch = getchar();
	return d * w;
}
void write_(int x)
{
	if (x < 0)
		x = -x, putchar('-');
	if (x > 9)
		write_(x / 10);
	putchar(x % 10 + '0');
}
void writeln(int x)
{
	write_(x);
	putchar('\n');
}
void writesp(int x)
{
	write_(x);
	putchar(' ');
}
const int mod = 998244353;
const int modG = 3;
using poly = vector<int>;
int power(int a, int b)
{
	int ans = 1;
	for(; b; b >>= 1, a = a * a % mod)
		if(b & 1)
			ans = ans * a % mod;
	return ans;
}
int exgcd(int a, int b, int &x, int &y)
{
	if(b == 0)
	{
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, x, y);
	int t = y;
	y = x - t * (a / b);
	x = t;
	return d;
}
int getinv(int a)
{
    return power(a, mod - 2);
}
int BSGS(int a, int b)
{
    a %= mod, b %= mod;
    map<int, int> mp;
    int m = ceil(sqrt(mod)), t = 1;
    for (int i = 0; i < m; ++i, t = t * a % mod)
        if (!mp.count(t))
            mp[t] = i;
    a = getinv(t), t = b;
    if (a == 0)
        return t == 0 ? 1 : -1;
    for (int i = 0; i < m; ++i, t = t * a % mod)
        if (mp.count(t))
            return i * m + mp[t];
    return -1;
}
int getKthRemaining(int a, int k)
{
	int t = BSGS(modG, a);
	int x, y;
	int d = exgcd(k, mod - 1, x, y);
	if(d != 1)
		return -1;
	x = (x % (mod - 1) + (mod - 1)) % (mod - 1);
	return power(modG, t * x % (mod - 1));
}
void print(const poly &a, int len = -1)
{
	if(len == -1)
		len = a.size();
	for(int i = 0; i < len; ++i)
		writesp(a[i]);
}
void NTT(poly &A, const vector<int> &r, int op)
{
	int n = A.size();
	for(int i = 0; i < n; ++i)
		if(i < r[i])
			swap(A[i], A[r[i]]);
	for(int i = 1; i < n; i <<= 1)
	{
		int buf = power(modG, (mod - 1) / (i << 1));
		for(int j = 0; j < n; j += i << 1)
		{
			int w = 1;
			for(int k = 0; k < i; ++k, w = w * buf % mod)
			{
				int p = A[j + k], q = w * A[i + j + k] % mod;
				A[j + k] = (p + q) % mod;
				A[i + j + k] = (p - q + mod) % mod;
			}
		}
	}
	if(op == -1)
	{
		reverse(A.begin() + 1, A.begin() + n);
		int inv = getinv(n);
		for(int i = 0; i < n; ++i)
			A[i] = A[i] * inv % mod;
	}
}
vector<int> getr(int n)
{
	int len = 1, l = 0;
	while(len < n)
		len <<= 1, ++l;
	vector<int> r(len);
	for(int i = 0; i < len; ++i)
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	return r;
}
poly operator+(const poly &a, int b)
{
	b %= mod;
	poly ret = a;
	for(int i = 0; i < ret.size(); ++i)
		ret[i] = (ret[i] + b + mod) % mod;
	return ret;
}
poly operator-(const poly &a, int b)
{
	b %= mod;
	poly ret = a;
	for(int i = 0; i < ret.size(); ++i)
		ret[i] = (ret[i] - b + mod) % mod;
	return ret;
}
poly operator*(const poly &a, int b)
{
	b %= mod;
	poly ret = a;
	for(int i = 0; i < ret.size(); ++i)
		ret[i] = (ret[i] * b % mod + mod) % mod;
	return ret;
}
poly operator+(const poly &a, const poly &b)
{
	poly ret = a;
	ret.resize(max(a.size(), b.size()));
	for(int i = 0; i < b.size(); ++i)
		ret[i] = (ret[i] + b[i]) % mod;
	return ret;
}
poly operator-(const poly &a, const poly &b)
{
	poly ret = a;
	ret.resize(max(a.size(), b.size()));
	for(int i = 0; i < b.size(); ++i)
		ret[i] = (ret[i] - b[i] + mod) % mod;
	return ret;
}
poly operator*(const poly &a, const poly &b)
{
	poly A = a, B = b;
	int n = A.size(), m = B.size();
	vector<int> r = getr(n + m);
	int len = r.size();
	A.resize(len), B.resize(len);
	NTT(A, r, 1), NTT(B, r, 1);
	for (int i = 0; i < len; ++i)
		A[i] = A[i] * B[i] % mod;
	NTT(A, r, -1);
	A.resize(n + m - 1);
	return A;
}

poly inv(const poly &a)
{
	poly ret = {getinv(a[0])};
	for(int len = 2; len < a.size() << 1; len <<= 1)
	{
		vector<int> r = getr(len << 1);
		int n = r.size();
		poly A = a;
		A.resize(n), ret.resize(n);
		for(int i = len; i < n; ++i)
			A[i] = 0;
		NTT(ret, r, 1), NTT(A, r, 1);
		for(int i = 0; i < n; ++i)
			ret[i] = ret[i] * (2 - A[i] * ret[i] % mod + mod) % mod;
		NTT(ret, r, -1);
		for(int i = len; i < n; ++i)
			ret[i] = 0;
	}
	ret.resize(a.size());
	return ret;
}
poly operator/(const poly &a, const poly &b)
{
	poly A = a, B = b;
	int n = A.size() - B.size() + 1;
	reverse(A.begin(), A.end()), reverse(B.begin(), B.end());
	B.resize(n);
	A = A * inv(B);
	A.resize(n);
	reverse(A.begin(), A.end());
	return A;
}
poly operator%(const poly &a, const poly &b)
{
	poly ret = a - b * (a / b);
	ret.resize(b.size() - 1);
	return ret;
}
int getval(const poly &a, int x)
{
	int ans = 0, now = 1;
	for(int i = 0; i < a.size(); ++i, now = now * x % mod)
		ans = (ans + a[i] * now % mod) % mod;
	return ans;
}
poly getval(const poly &a, const poly &x)
{
	poly ret;
	poly now = {1};
	for(int i = 0; i < a.size(); ++i, now = now * x)
		ret = ret + now * a[i];
	return ret; 
}

poly deri(const poly &a)
{
	poly A(a.size() - 1);
	for(int i = 0; i < A.size(); ++i)
		A[i] = a[i + 1] * (i + 1) % mod;
	return A;
}

poly inte(const poly &a, int C = 0)
{
	poly A(a.size());
	for(int i = 1; i < A.size(); ++i)
		A[i] = a[i - 1] * getinv(i) % mod;
	A[0] = C;
	return A;
}


poly cinv(const poly &a)
{
	poly ret(a.size());
	poly t(a.size() - 1), now = {1};
	for(int i = 0; i < t.size(); ++i)
		t[i] = a[i + 1];
	t = inv(t);
	for(int i = 1; i < a.size(); ++i)
	{
		now = now * t, now.resize(a.size());
		ret[i] = now[i-1] * getinv(i) % mod;
	}
	return ret;
}

poly ln(const poly &a)
{
	poly ret = deri(a) * inv(a);
	ret.resize(a.size());
	return inte(ret);
}

poly exp(const poly &a, int expA0 = 1)
{
	poly ret = {expA0};
	for(int len = 2; len < a.size() << 1; len <<= 1)
	{
		vector<int> r = getr(len << 1);
		int n = r.size();
		poly A = ln(ret);
		A.resize(n), ret.resize(n);
		for(int i = 0; i < min((int)a.size(), len); ++i)
			A[i] = (a[i] - A[i] + mod) % mod;
		for(int i = a.size(); i < len; ++i)
			A[i] = mod - A[i];
		A[0] = (A[0] + 1) % mod;
		NTT(ret, r, 1), NTT(A, r, 1);
		for(int i = 0; i < n; ++i)
			ret[i] = ret[i] * A[i] % mod;
		NTT(ret, r, -1);
		for(int i = len; i < n; ++i)
			ret[i] = 0;
	}
	ret.resize(a.size());
	return ret;
}
poly power(const poly &a, int b)
{
	poly A = a;
	int k = 0;
	while(k < A.size() && !A[k])
		++k;
	if(k == A.size())
		return {0};
	for(int i = k; i < A.size(); ++i)
		A[i - k] = A[i];
	A.resize(A.size() - k);
	A = exp(ln(A) * b, power(a[k], b));
	k *= b;
	poly ret(a.size());
	for(int i = k; i < a.size(); ++i)
		ret[i] = A[i - k];
	return ret;
}
poly sqrt(const poly &a, int b = 2)
{
	poly A = a;
	int k = 0;
	while(k < A.size() && !A[k])
		++k;
	if(k == A.size())
		return {0};
	if(k % b)
		return {};	
	for(int i = k; i < A.size(); ++i)
		A[i - k] = A[i];
	A.resize(A.size() - k);
	int kr = getKthRemaining(A[0], b);
	if(k == -1)
		return {};	
	A = exp(ln(A) * getinv(b), kr);
	k /= b;
	poly ret(a.size());
	for(int i = k; i < a.size(); ++i)
		ret[i] = A[i - k];
	return ret;
}
signed main()
{
#ifdef __clang__
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);
#endif
	int n = read();
	poly a;
	for(int i = 0; i <= n; ++i)
		a.push_back(read());
	print(sqrt(a, 3));
	return 0;
}